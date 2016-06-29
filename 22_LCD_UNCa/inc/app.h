/*================================================================
 * Dpto de Electrónica y Laboratorio de Sistemas Embebidos – UNCa
 * Nombre: uso_display.h
 * Autor: Matias L. Ferraro
===============================================================*/
#ifndef uso_display_H
#define uso_display_H
/*==================[inclusions]==============================*/
#include "stdint.h"
#include "chip.h"
#include "puertos_lcd_r.h"
#include "lcd_r.h"
#include "led.h"
#include "teclas.h"
#include "lpc_types.h"
/*==================[macros]==================================*/
#define lpc4337 1
#define mk60fx512vlq15 2

#if (CPU == mk60fx512vlq15)
/* Reset_Handler is defined in startup_MK60F15.S_CPP */
void Reset_Handler( void );
extern uint32_t __StackTop;

#elif (CPU == lpc4337)
extern void ResetISR(void);

extern void _vStackTop(void);

void RIT_IRQHandler(void);
#else
#endif
#endif
