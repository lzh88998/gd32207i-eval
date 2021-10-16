#include "core_mqtt_agent.h"
#include "core_mqtt.h"

void agentTask( void * pvParameters ) {
    xMQTTStatus = prvMQTTAgentInit();

    if( xMQTTStatus == MQTTSuccess )
    {
        /* Create the TCP connection to the broker, then the MQTT connection to the
         * same. */
        xResult = prvConnectToMQTTBroker( true );
    }

    if( xResult == pdPASS )
    {
        xTaskCreate( prvMQTTAgentTask,
                     "MQTT Agent",
                     democonfigSIMPLE_SUB_PUB_TASK_STACK_SIZE,
                     NULL,
                     tskIDLE_PRIORITY + 1,
                     NULL );
		}
}