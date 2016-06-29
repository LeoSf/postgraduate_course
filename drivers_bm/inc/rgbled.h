/* Copyright 2016, Leandro D. Medus
 * lmedus@bioingenieria.edu.ar
 * Facultad de Ingeniería - UNER
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

#ifndef RGBLED_H
#define RGBLED_H
/** \brief Bare Metal header for leds in EDU-CIAA NXP
 **
 ** This is a driver for:
 ** RGB led
 ** three SMD leds (yellow, red and green)
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Sources_LDM Leandro D. Medus Sources
 ** @{ */
/** \addtogroup Baremetal Bare Metal source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *	LM			Leandro Medus
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160422 v0.1 initials initial version leo.
 * 20160520 v0.2 end of documentation for the rbg driver.
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"
#include "chip.h"
#include "led.h"
#include "timers.h"			/* no debería incluir nada dado que no sabe como funcionan los timers */
#include "interrupts.h"		/* debido a que se emula la funcionalidad de PWM mediante la RSI del timer RTI */

/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

/*==================[typedef]================================================*/

typedef struct
{
	uint8_t red;			/* status of the red led */
	uint8_t red_duty;		/* duty cycle of the red signal */
	uint8_t green;			/* status of the red green */
	uint8_t green_duty;		/* duty cycle of the green signal */
	uint8_t blue;			/* status of the red blue */
	uint8_t blue_duty;		/* duty cycle of the blue signal */
}edu_ciaa_ledRGB;

typedef struct
{
	uint8_t current_state;
	uint8_t next_state ;
	uint16_t current_cycle;
	uint8_t direction;
}fade_sequence_rgb;

/*==================[external data declaration]==============================*/
enum LED_COLOR_RBG {RED_RGB=1, GREEN_RGB=2, BLUE_RGB=4};
enum SFM_STATES {START, BLUE_RED, RED_GREEN, GREEN_BLUE};
//enum LED_STATUS {OFF=0, ON=1};

/*==================[external functions declaration]=========================*/
uint8_t initGPIO_rgbLed_EDUCIAA(void);
uint8_t ledOnRGB(uint8_t leds);
uint8_t ledOffRGB(uint8_t leds);
uint8_t toggleLedsRGB(void);
uint8_t setLedRGB(edu_ciaa_ledRGB *rgb);
void fadeRGB(edu_ciaa_ledRGB *prgb);
void fadeRed(edu_ciaa_ledRGB *prgb);
void fadeGreen(edu_ciaa_ledRGB *prgb);
void fadeBlue(edu_ciaa_ledRGB *prgb);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/*==================[end of file]============================================*/
#endif /* #ifndef MI_NUEVO_PROYECTO_H */

