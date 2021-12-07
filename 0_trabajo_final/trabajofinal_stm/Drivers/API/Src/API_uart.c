/*
 * API_uart.c
 *
 *  Created on: 30/11/2021
 *      Author: VIN
 */

#include "API_uart.h"
//#include "stm32f4xx_hal.h"


UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

bool_t uartInit()
{
	/**
	* @brief Habilita el control del clok DMA por si el buffer de la UART se llena
	* éste le permita escribir directamente en la memoria sin pasar por el procesador del micro.
	*
	*/
	__HAL_RCC_DMA2_CLK_ENABLE();

	HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

	/**
	* @brief estas líneas configuran la UART a utilizar. En este caso
	* se inicializa la USART6:
	* PIN PC6 como TX y
	* PIN PC7 como RX.
	*/
	__HAL_RCC_GPIOC_CLK_ENABLE();
	huart6.Instance = USART6;
	huart6.Init.BaudRate = 9600;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK)
	{
		return false;
	}
	else
	{
		uartSendString_direct("Instance: USART6\n\r");
		uartSendString_direct("Baud rate: 9600\n\r");
		uartSendString_direct("Word length: 8 bits\n\r");
		uartSendString_direct("Stop bits: 1 bit\n\r");
		uartSendString_direct("Parity: NONE\n\r");
		uartSendString_direct("Mode: Send/Recieve\n\r");
		uartSendString_direct("Flow Control: NONE\n\r");
		uartSendString_direct("Over sampling: 16 bits\n\r");
		return true;
	}

}

void uartSendString(uint8_t *mensaje, uint8_t longitud)
{

	//uint8_t string[] = mensaje;
	HAL_UART_Transmit(&huart6, mensaje, longitud - 1, 0xFFF);
}

void uartSendString_direct(char *mensaje)
{
	uint16_t longitud = strlen(mensaje);
	HAL_UART_Transmit(&huart6, mensaje, longitud , 0xFFF);
}



