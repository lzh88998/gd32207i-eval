/*
 * FreeRTOS+TCP V2.3.2 LTS Patch 1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#include "string.h"

#include "gd32f207i_eval.h"
#include "gd32f20x_enet_eval.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOSIPConfig.h"
#include "NetworkBufferManagement.h"

#include "list.h"

/* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1, then the Ethernet
 * driver will filter incoming packets and only pass the stack those packets it
 * considers need processing. */
#if ( ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES == 0 )
    #define ipCONSIDER_FRAME_FOR_PROCESSING( pucEthernetBuffer )    eProcessBuffer
#else
    #define ipCONSIDER_FRAME_FOR_PROCESSING( pucEthernetBuffer )    eConsiderFrameForProcessing( ( pucEthernetBuffer ) )
#endif

/* Default the size of the stack used by the EMAC deferred handler task to twice
 * the size of the stack used by the idle task - but allow this to be overridden in
 * FreeRTOSConfig.h as configMINIMAL_STACK_SIZE is a user definable constant. */
#ifndef configEMAC_TASK_STACK_SIZE
    #define configEMAC_TASK_STACK_SIZE    ( 2 * configMINIMAL_STACK_SIZE )
#endif

#ifndef RECV_HANDLER_TASK_PRIORITY
    #define RECV_HANDLER_TASK_PRIORITY    configMAX_PRIORITIES - 1
#endif

/*global transmit and receive descriptors pointers */
extern enet_descriptors_struct  *dma_current_txdesc;
extern enet_descriptors_struct  *dma_current_rxdesc;

/* ENET RxDMA/TxDMA descriptor */
extern enet_descriptors_struct  rxdesc_tab[ENET_RXBUF_NUM], txdesc_tab[ENET_TXBUF_NUM];

/* ENET receive buffer  */
extern uint8_t rx_buff[ENET_RXBUF_NUM][ENET_RXBUF_SIZE]; 

/* ENET transmit buffer */
extern uint8_t tx_buff[ENET_TXBUF_NUM][ENET_TXBUF_SIZE]; 

/* Holds the handle of the task used as a deferred interrupt processor.  The
 * handle is used so direct notifications can be sent to the task for all EMAC/DMA
 * related interrupts. */
static TaskHandle_t xRecvTaskHandle = NULL;

static SemaphoreHandle_t xRXDescriptorSemaphore = NULL;

BaseType_t trng_configuration(void);
static void prvRecvHandlerTask( void * pvParameters );

static uint8_t ucMACAddress[ 6 ] =
{
    configMAC_ADDR0,
    configMAC_ADDR1,
    configMAC_ADDR2,
    configMAC_ADDR3,
    configMAC_ADDR4,
    configMAC_ADDR5
};

BaseType_t xNetworkInterfaceInitialise( void )
{
    uint8_t retry = 0;
	  uint8_t i = 0;
    while((pdFALSE == trng_configuration()) && retry < 3){
        retry++;
    }
		
		// Create Semaphore
		xRXDescriptorSemaphore = xSemaphoreCreateCounting( ENET_TXBUF_NUM, 0 );
		if(NULL == xRXDescriptorSemaphore) {
				return pdFALSE;
		}
			
		if(pdPASS != xTaskCreate( prvRecvHandlerTask, "ReceiveHandler", configEMAC_TASK_STACK_SIZE, NULL, RECV_HANDLER_TASK_PRIORITY, &xRecvTaskHandle )) {
				return pdFALSE;
		}

    enet_system_setup();
		
		enet_mac_address_set(ENET_MAC_ADDRESS0, ucMACAddress);

    /* initialize descriptors list: chain/ring mode */
    enet_descriptors_chain_init(ENET_DMA_TX);
    enet_descriptors_chain_init(ENET_DMA_RX);

    /* enable ethernet Rx interrrupt */
		for(i=0; i<ENET_RXBUF_NUM; i++){ 
			 enet_desc_receive_complete_bit_enable(&rxdesc_tab[i]);
		}

#ifdef CHECKSUM_BY_HARDWARE
    /* enable the TCP, UDP and ICMP checksum insertion for the Tx frames */
    for(i=0; i < ENET_TXBUF_NUM; i++){
        enet_transmit_checksum_config(&txdesc_tab[i], ENET_CHECKSUM_TCPUDPICMP_FULL);
    }
#endif /* CHECKSUM_BY_HARDWARE */

    /* note: TCP, UDP, ICMP checksum checking for received frame are enabled in DMA config */

    /* enable MAC and DMA transmission and reception */
    enet_enable();
		
    return pdTRUE;
}

BaseType_t xNetworkInterfaceOutput( NetworkBufferDescriptor_t * const pxNetworkBuffer,
                                    BaseType_t xReleaseAfterSend )
{
    uint8_t *buffer = NULL;
    
    buffer = (uint8_t *)(enet_desc_information_get(dma_current_txdesc, TXDESC_BUFFER_1_ADDR));
    
    /* copy frame from pbufs to driver buffers */
		memcpy(buffer, pxNetworkBuffer->pucEthernetBuffer, pxNetworkBuffer->xDataLength);
    
    /* transmit descriptors to give to DMA */ 
    ENET_NOCOPY_FRAME_TRANSMIT(pxNetworkBuffer->xDataLength);

    if( xReleaseAfterSend != pdFALSE )
    {
        vReleaseNetworkBufferAndDescriptor( pxNetworkBuffer );
    }

    return pdTRUE;
}


#ifdef USE_ENET_INTERRUPT
/*!
    \brief      this function handles ethernet interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ENET_IRQHandler(void)
{
		static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR( xRXDescriptorSemaphore, &xHigherPriorityTaskWoken);

		/* clear the enet DMA Rx interrupt pending bits */
    enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_RS_CLR);
    enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_NI_CLR);
}
#endif /* USE_ENET_INTERRUPT */


BaseType_t trng_ready_check(void);
BaseType_t xApplicationGetRandomNumber( uint32_t * pulNumber ) {
		if(pdTRUE == trng_ready_check()) {
			*pulNumber = trng_get_true_random_data();
			return pdTRUE;
		}
		else {
			return pdFALSE;
		}
}


/*!
    \brief      check whether the TRNG module is ready
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
BaseType_t trng_ready_check(void)
{
    uint32_t timeout = 0;
    FlagStatus trng_flag = RESET;
    
    /* check wherther the random data is valid */
    do{
        timeout++;
        trng_flag = trng_flag_get(TRNG_FLAG_DRDY);
    }while((RESET == trng_flag) &&(0xFFFF > timeout));
    
    if(RESET == trng_flag){   
        /* ready check timeout */
//        printf("Error: TRNG can't ready \r\n");
        return pdFALSE;
    }
    
    trng_flag = trng_flag_get(TRNG_FLAG_CECS);
    if(SET == trng_flag){
//        printf("Clock error status: %d \r\n", trng_flag);
        return pdFALSE;
    }
        
    trng_flag = trng_flag_get(TRNG_FLAG_SECS);
    if(SET == trng_flag){
//        printf("Seed error status: %d \r\n", trng_flag);      
        return pdFALSE;     
    }
    
    /* return check status */
    return pdTRUE;
}

/*!
    \brief      configure TRNG module
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
BaseType_t trng_configuration(void)
{
    BaseType_t reval = pdTRUE;
    
    /* TRNG module clock enable */
    rcu_periph_clock_enable(RCU_TRNG);
    
    /* TRNG registers reset */
    trng_deinit();
    trng_enable();
    /* check TRNG work status */
    reval = trng_ready_check();
    
    return reval;
}

uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort ) {
		uint32_t ret = 0;
		xApplicationGetRandomNumber(&ret);
		return ret;
}
																						 
static void prvRecvHandlerTask( void * pvParameters ) {
    NetworkBufferDescriptor_t * pxNetworkBuffer = NULL;
		uint32_t len = 0;
		uint8_t* buffer = NULL;
    IPStackEvent_t xRxEvent = { eNetworkRxEvent, NULL };
		
    const TickType_t xBlockTimeTicks = pdMS_TO_TICKS( 50u );

		for(;;) {
				// Wait for semaphore here
			  if(pdPASS != xSemaphoreTake( xRXDescriptorSemaphore, xBlockTimeTicks)) {
						continue;
				}
					
				/* handles all the received frames */
				len = enet_desc_information_get(dma_current_rxdesc, RXDESC_FRAME_LENGTH);
				buffer = (uint8_t *)(enet_desc_information_get(dma_current_rxdesc, RXDESC_BUFFER_1_ADDR));

				pxNetworkBuffer = pxGetNetworkBufferWithDescriptor( len, 0 );

				if( pxNetworkBuffer != NULL )
				{
						memcpy( pxNetworkBuffer->pucEthernetBuffer, buffer, len );
						pxNetworkBuffer->xDataLength = len;	
				}
				
				xRxEvent.pvData = ( void * ) pxNetworkBuffer;

				if( xSendEventStructToIPTask( &xRxEvent, ( TickType_t ) 0 ) == pdFAIL )
				{
						vReleaseNetworkBufferAndDescriptor( pxNetworkBuffer );
				}
				ENET_NOCOPY_FRAME_RECEIVE();
		}
}

int mbedtls_hardware_poll( void *data, unsigned char *output, size_t len, size_t *olen )
{
    uint32_t random_data = 0;

		((void) data);
    *olen = 0;
    random_data = trng_get_true_random_data();

    if ((len < sizeof(uint32_t))){
        return -1;
    }

    memcpy(output, &random_data, sizeof(uint32_t));
    *olen = sizeof(uint32_t);

    return 0;
}
