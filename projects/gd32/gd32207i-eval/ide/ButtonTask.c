#include "gd32f207i_eval.h"

#include "core_mqtt.h"
#include "transport_secure_sockets.h"
#include "aws_clientcredential.h"
#include "core_pkcs11.h"
#include "pkcs11.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "iot_default_root_certificates.h"

/**
 * @brief Milliseconds per second.
 */
#define MILLISECONDS_PER_SECOND                    ( 1000U )

/**
 * @brief Milliseconds per FreeRTOS tick.
 */
#define MILLISECONDS_PER_TICK                      ( MILLISECONDS_PER_SECOND / configTICK_RATE_HZ )

/**
 * @brief Length of the client identifier.
 */
#define TEST_CLIENT_IDENTIFIER_LENGTH              ( sizeof( clientcredentialIOT_THING_NAME ) - 1u )

/**
 * @brief Timeout for receiving CONNACK packet in milli seconds.
 */
#define CONNACK_RECV_TIMEOUT_MS                    ( 20000U )

/**
 * @brief Transport timeout in milliseconds for transport send and receive.
 */
#define TRANSPORT_SEND_RECV_TIMEOUT_MS             ( 200U )

/**
 * @brief Sample topic filter to subscribe to.
 */
#define TEST_MQTT_LWT_TOPIC                        clientcredentialIOT_THING_NAME "/iot/integration/test/lwt"

/**
 * @brief Length of sample topic filter.
 */
#define TEST_MQTT_LWT_TOPIC_LENGTH                 ( sizeof( TEST_MQTT_LWT_TOPIC ) - 1 )

/**
 * @brief The MQTT message published in this example.
 */
#define MQTT_EXAMPLE_MESSAGE                       "Hello World!"

/**
 * @brief Global entry time to use as a reference timestamp in the getTimeMs()
 * function. getTimeMs() function will always return the difference between the
 * current time and the global entry time. This reduces the chances of overflow
 * for the 32 bit unsigned integer used for holding the timestamp.
 */
static uint32_t globalEntryTime;

static uint32_t getTimeMs()
{
    TickType_t tickCount = 0;
    uint32_t timeMs = 0UL;

    /* Get the current tick count. */
    tickCount = xTaskGetTickCount();

    /* Convert the ticks to milliseconds. */
    timeMs = ( uint32_t ) tickCount * MILLISECONDS_PER_TICK;

    /* Reduce globalEntryTime from obtained time so as to always return the
     * elapsed time in the application. */
    timeMs = ( uint32_t ) ( timeMs - globalEntryTime );

    return timeMs;
}


static void prvUpdateSubAckStatus( MQTTPacketInfo_t * pxPacketInfo )
{
    MQTTStatus_t xResult = MQTTSuccess;
    uint8_t * pucPayload = NULL;
    size_t ulSize = 0;
    uint32_t ulTopicCount = 0U;

    xResult = MQTT_GetSubAckStatusCodes( pxPacketInfo, &pucPayload, &ulSize );
		printf("ACK: %d\r\n", ulSize);
}

static void prvMQTTProcessResponse( MQTTPacketInfo_t * pxIncomingPacket,
                                    uint16_t usPacketId )
{
    uint32_t ulTopicCount = 0U;

    switch( pxIncomingPacket->type )
    {
        case MQTT_PACKET_TYPE_PUBACK:
            LogInfo( ( "PUBACK received for packet Id %u.\r\n", usPacketId ) );
            break;

        case MQTT_PACKET_TYPE_SUBACK:

            /* A SUBACK from the broker, containing the server response to our subscription request, has been received.
             * It contains the status code indicating server approval/rejection for the subscription to the single topic
             * requested. The SUBACK will be parsed to obtain the status code, and this status code will be stored in global
             * variable #xTopicFilterContext. */
            prvUpdateSubAckStatus( pxIncomingPacket );
            break;

        case MQTT_PACKET_TYPE_UNSUBACK:
            break;

        case MQTT_PACKET_TYPE_PINGRESP:
            break;

        case MQTT_PACKET_TYPE_PUBREC:
            break;

        case MQTT_PACKET_TYPE_PUBREL:
            break;

        case MQTT_PACKET_TYPE_PUBCOMP:
            break;

        /* Any other packet type is invalid. */
        default:
					break;
    }
}

static void eventCallback( MQTTContext_t * pContext,
                           MQTTPacketInfo_t * pPacketInfo,
                           MQTTDeserializedInfo_t * pDeserializedInfo )
{
    if( ( pPacketInfo->type & 0xF0U ) == MQTT_PACKET_TYPE_PUBLISH )
    {
        printf("Incoming: %.*s\r\n", pDeserializedInfo->pPublishInfo->payloadLength, pDeserializedInfo->pPublishInfo->pPayload);
				if(pDeserializedInfo->pPublishInfo->payloadLength >= 3) {
						switch(((char*)pDeserializedInfo->pPublishInfo->pPayload)[0]) {
							case '0':
								if('0' == ((char*)pDeserializedInfo->pPublishInfo->pPayload)[2]) 
									gd_eval_led_off(LED1);
								else
									gd_eval_led_on(LED1);
								break;
							case '1':
								if('0' == ((char*)pDeserializedInfo->pPublishInfo->pPayload)[2]) 
									gd_eval_led_off(LED2);
								else
									gd_eval_led_on(LED2);
								break;
							case '2':
								if('0' == ((char*)pDeserializedInfo->pPublishInfo->pPayload)[2]) 
									gd_eval_led_off(LED3);
								else
									gd_eval_led_on(LED3);
								break;
							case '3':
								if('0' == ((char*)pDeserializedInfo->pPublishInfo->pPayload)[2]) 
									gd_eval_led_off(LED4);
								else
									gd_eval_led_on(LED4);
								break;
						}
				}
    }
    else
    {
        prvMQTTProcessResponse( pPacketInfo, pDeserializedInfo->packetIdentifier );
    }
}

/**
 * @brief Each compilation unit that consumes the NetworkContext must define it.
 * It should contain a single pointer to the type of your desired transport.
 * When using multiple transports in the same compilation unit, define this pointer as void *.
 *
 * @note Transport stacks are defined in amazon-freertos/libraries/abstractions/transport/secure_sockets/transport_secure_sockets.h.
 */
struct NetworkContext
{
    SecureSocketsTransportParams_t * pParams;
};

void ButtonTask( void * pvParameters ) {
	NetworkContext_t networkContext;
	MQTTConnectInfo_t connectInfo;
	MQTTContext_t context;
	TransportInterface_t transport;
	MQTTFixedBuffer_t networkBuffer;
	MQTTPublishInfo_t lwtInfo;
	SecureSocketsTransportParams_t params;
	MQTTSubscribeInfo_t xMQTTSubscription[1];
	MQTTStatus_t xResult;
	
	uint8_t tamper_count = 0;
	uint8_t wakeup_count = 0;
	uint8_t user_count = 0;
	
	ServerInfo_t serverInfo;
	SocketsConfig_t socketsConfig;

	static uint8_t buffer[ 1024 ];
	bool persistent = true;

	TransportSocketStatus_t transportStatus = TRANSPORT_SOCKET_STATUS_SUCCESS;

	networkContext.pParams = &params;
	/* Initializer server information. */
	serverInfo.pHostName = clientcredentialMQTT_BROKER_ENDPOINT;
	serverInfo.hostNameLength = strlen( clientcredentialMQTT_BROKER_ENDPOINT );
	serverInfo.port = clientcredentialMQTT_BROKER_PORT;

	/* Initialize SocketsConfig. */
	socketsConfig.enableTls = true;
	socketsConfig.pAlpnProtos = NULL;
	socketsConfig.maxFragmentLength = 0;
	socketsConfig.disableSni = true;
	socketsConfig.pRootCa = tlsSTARFIELD_ROOT_CERTIFICATE_PEM;
	socketsConfig.rootCaSize = strlen( tlsSTARFIELD_ROOT_CERTIFICATE_PEM ) + 1U;
	socketsConfig.sendTimeoutMs = TRANSPORT_SEND_RECV_TIMEOUT_MS;
	socketsConfig.recvTimeoutMs = TRANSPORT_SEND_RECV_TIMEOUT_MS;

	/* Establish a TCP connection with the server endpoint, then
	 * establish TLS session on top of TCP connection. */
	transportStatus = SecureSocketsTransport_Connect( &networkContext,
																										&serverInfo,
																										&socketsConfig );

	if( transportStatus != TRANSPORT_SOCKET_STATUS_SUCCESS )
		printf("Error connect to server!\r\n");

	transport.pNetworkContext = &networkContext;
	transport.send = SecureSocketsTransport_Send;
	transport.recv = SecureSocketsTransport_Recv;

	networkBuffer.pBuffer = buffer;
	networkBuffer.size = 1024;

	connectInfo.cleanSession = true;
	connectInfo.clientIdentifierLength = TEST_CLIENT_IDENTIFIER_LENGTH;
	connectInfo.pClientIdentifier = clientcredentialIOT_THING_NAME;
	connectInfo.keepAliveSeconds = 60U;
	connectInfo.pUserName = NULL;
	connectInfo.userNameLength = 0U;
	connectInfo.pPassword = NULL;
	connectInfo.passwordLength = 0U;

	lwtInfo.pTopicName = TEST_MQTT_LWT_TOPIC;
	lwtInfo.topicNameLength = TEST_MQTT_LWT_TOPIC_LENGTH;
	lwtInfo.pPayload = MQTT_EXAMPLE_MESSAGE;
	lwtInfo.payloadLength = strlen( MQTT_EXAMPLE_MESSAGE );
	lwtInfo.qos = MQTTQoS0;
	lwtInfo.dup = false;
	lwtInfo.retain = false;
	
	
	xMQTTSubscription[ 0 ].qos = MQTTQoS0;
	xMQTTSubscription[ 0 ].pTopicFilter = "gd32/led";
	xMQTTSubscription[ 0 ].topicFilterLength = ( uint16_t ) strlen( "gd32/led" );

	if(MQTTSuccess != MQTT_Init(&context, &transport, getTimeMs, eventCallback, &networkBuffer))
		printf("Fail to init!\r\n");

	if(MQTTSuccess != MQTT_Connect( &context,
																	&connectInfo,
																	&lwtInfo,
																	CONNACK_RECV_TIMEOUT_MS,
																	&persistent ))
		printf("Fail to connect!\r\n");
	
  if(MQTTSuccess != MQTT_Subscribe( &context,
																		xMQTTSubscription,
																		1,
																		MQTT_GetPacketId( &context ) ))
		printf("Fail to subscribe!\r\n");
									
	xResult = MQTT_ProcessLoop( &context, 100U );
	if(MQTTSuccess != xResult)
		printf("Fail to process 1! 0x%X\r\n", xResult);
	
	lwtInfo.pTopicName = "gd32/button";
	lwtInfo.topicNameLength = strlen("gd32/button");
	lwtInfo.payloadLength = 1;
	lwtInfo.qos = MQTTQoS0;
	lwtInfo.dup = false;
	lwtInfo.retain = false;

	for(;;) {
		if(RESET == gd_eval_key_state_get(KEY_WAKEUP)) {
			if(wakeup_count < 3)
				wakeup_count++;
		}
		else
			wakeup_count = 0;

		if(RESET == gd_eval_key_state_get(KEY_TAMPER)) {
			if(tamper_count < 3)
				tamper_count++;
		}
		else
			tamper_count = 0;

		if(RESET == gd_eval_key_state_get(KEY_USER)) {
			if(user_count < 3)
				user_count++;
		}
		else
			user_count = 0;
		
		if(wakeup_count == 1) {
			wakeup_count = 4;
			printf("0\r\n");
			lwtInfo.pPayload = "0";
			if(MQTTSuccess != MQTT_Publish(&context,
																		&lwtInfo,
																		MQTT_GetPacketId( &context ) ))
				printf("Failed to publish!\r\n");
		}

		if(tamper_count == 1) {
			tamper_count = 4;
			printf("1\r\n");
			lwtInfo.pPayload = "1";
			if(MQTTSuccess != MQTT_Publish(&context,
																		&lwtInfo,
																		MQTT_GetPacketId( &context ) ))
				printf("Failed to publish!\r\n");
		}
		
		if(user_count == 1) {
			user_count = 4;
			printf("2\r\n");
			lwtInfo.pPayload = "2";
			if(MQTTSuccess != MQTT_Publish(&context,
																		&lwtInfo,
																		MQTT_GetPacketId( &context ) ))
				printf("Failed to publish!\r\n");
		}
		
		xResult = MQTT_ProcessLoop( &context, 100U );
		if(MQTTSuccess != xResult) {
//			printf("Fail to process 2! 0x%X\r\n", xResult);
		}
		vTaskDelay(50);
	}
}
