/*
 * API_uart.h
 *
 *  Created on: 30/11/2021
 *      Author: VIN
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"


#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

typedef bool bool_t;

bool_t uartInit();
void uartSendString(uint8_t *mensaje, uint8_t longitud);

//uint8_t longitud(uint8_t string[]); //da problemas al modularizarse tocó usar directamente en el main

void uartSendString_direct(char *mensaje);




#endif /* API_INC_API_UART_H_ */
