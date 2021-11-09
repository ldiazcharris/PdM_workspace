/*
 * Archivo de prototipos de la función de delay no restrictivo
 * Creado el 08 nov 2021
 * Autor: Luis Diaz Charris
 *
 */

#include <stdInt.h>
#include <stdBool.h>

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




