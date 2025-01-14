/*
 * API_delay.h
 *
 *  Created on: Nov 11, 2021
 *      Author: Luis David Díaz Charris
 */
#include <stdint.h>
#include <stdbool.h>

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/*
 * Archivo de prototipos de la función de delay no restrictivo
 * Creado el 08 nov 2021
 * Autor: Luis Diaz Charris
 *
 */



typedef uint32_t tick_t;
typedef bool bool_t;


typedef struct{
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;


void delayInit(delay_t * delay, tick_t duration);
bool_t delayRead(delay_t * delay);
void delayWrite(delay_t * delay, tick_t duration);

#endif /* API_INC_API_DELAY_H_ */
