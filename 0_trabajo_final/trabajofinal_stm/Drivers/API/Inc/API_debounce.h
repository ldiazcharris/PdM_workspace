/*
 * API_debouce.h
 *
 *  Created on: 30/11/2021
 *      Author: VIN
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "API_delay.h"
#include "stm32f4xx_hal.h"

typedef bool bool_t;

typedef enum{
	BUTTON_UP = 0,
	BUTTON_RISING,
	BUTTON_DOWN,
	BUTTON_FALLING
} debounce_t;

//GPIO_InitTypeDef GPIO_InitStruct = {0};

bool_t buttonPressed(void);
bool_t buttonReleased(void);

/*PORT: debe ser un puerto GPIO válido ej: GPIOA o GPIOB.
 *PIN: debe ser un pin válido ej: GPIO_PIN_1 o GPIO_PIN_15
 *PULL_MODE: GPIO_PULLDOWN (cuando el botón físcamente está conectado con una resistencia Pull-Up)
 *PULL_MODE: GPIO_PULLUP (cuando el botón físcamente está conectado con una resistencia Pull-Down)
 *PULL_MODE: GPIO_NOPULL
 */

bool_t debounceInit(void);

 debounce_t debounceUpdate(GPIO_PinState pinState);
//void debounceUpdate();

#endif /* API_INC_API_DEBOUNCE_H_ */
