/* Copyright 2016, Leandro D. Medus
 * lmedus@bioingenieria.edu.ar
 * Faculty of Engineering
 * National University of Entre Ríos
 * Argentina
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef APP_H
#define APP_H

/** \brief Bare Metal application header of the ninth activity present in the activity guide of
 ** the course.
 ** \details
 **	The application has to drive a saw signal using the digital to analog converter in the edu-ciaa
 **	board. This signal has a period equal to 100 [ms] while the voltage value goes from 0 [V] to
 **	3.3 [V].
 **/

/** \addtogroup EDU-CIAA_Course
 ** @{ */
/** \addtogroup Sources_LDM Leandro D. Medus Sources
 ** @{ */
/** \addtogroup Baremetal_App Bare Metal application source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *	LM			Leandro Medus
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160422 v0.1 initials initial version leo
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"
#include "led.h"
#include "teclas.h"
#include "timers.h"
#include "rgbled.h"
#include "teclado.h"

#include "app_interrupts.h"
#include "dac.h"
#include "adc.h"

#include "puertos_lcd_r.h"
#include "lcd_r.h"
#include "uart.h"
//#include "lpc_types.h"


/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
#if (CPU == mk60fx512vlq15)
/* Reset_Handler is defined in startup_MK60F15.S_CPP */
void Reset_Handler( void );

extern uint32_t __StackTop;
#elif (CPU == lpc4337)
/** \brief Reset ISR
 **
 ** ResetISR is defined in cr_startup_lpc43xx.c
 **
 ** \remark the definition is in
 **         externals/drivers/cortexM4/lpc43xx/src/cr_startup_lpc43xx.c
 **/
extern void ResetISR(void);

/** \brief Stack Top address
 **
 ** External declaration for the pointer to the stack top from the Linker Script
 **
 ** \remark only a declaration is needed, there is no definition, the address
 **         is set in the linker script:
 **         externals/base/cortexM4/lpc43xx/linker/ciaa_lpc4337.ld.
 **/
extern void _vStackTop(void);




#else
#endif





/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef BAREMETAL_BLINKING_H */

