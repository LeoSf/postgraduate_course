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

/** \brief Bare Metal driver for leds in the EDU-CIAA board.
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
 * 20160422 v0.1 initials initial version leo
 */

/*==================[inclusions]=============================================*/
#include "led.h"

/*==================[macros and definitions]=================================*/
/** Mapeo de pines Leds RGB
 * P2_0  en GPIO 5[0], LED0R y habilita el pull up.
 * P2_1  en GPIO 5[1], LED0G y habilita el pull up.
 * P2_2  en GPIO 5[2], LED0B y habilita el pull up.
 * */
#define LED_RGB_R_MUX_GROUP 2
#define LED_RGB_R_MUX_PIN 0
#define LED_RGB_R_GPIO_PORT 5
#define LED_RGB_R_GPIO_PIN 0

#define LED_RGB_G_MUX_GROUP 2
#define LED_RGB_G_MUX_PIN 1
#define LED_RGB_G_GPIO_PORT 5
#define LED_RGB_G_GPIO_PIN 1

#define LED_RGB_B_MUX_GROUP 2
#define LED_RGB_B_MUX_PIN 2
#define LED_RGB_B_GPIO_PORT 5
#define LED_RGB_B_GPIO_PIN 2

/** Mapeo de pines Leds 1, 2 y 3
 * P2_10 en GPIO 0[14], LED1 y habilita el pull up
 * P2_11 en GPIO 1[11], LED2 y habilita el pull up
 * P2_12 en GPIO 1[12], LED3 y habilita el pull up
 * */
#define LED1_MUX_GROUP 2
#define LED1_MUX_PIN 10
#define LED1_GPIO_PORT 0
#define LED1_GPIO_PIN 14

#define LED2_MUX_GROUP 2
#define LED2_MUX_PIN 11
#define LED2_GPIO_PORT 1
#define LED2_GPIO_PIN 11

#define LED3_MUX_GROUP 2
#define LED3_MUX_PIN 12
#define LED3_GPIO_PORT 1
#define LED3_GPIO_PIN 12

#define OUTPUT_DIRECTION 1
#define INPUT_DIRECTION 0

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/

/** \brief Initialization function to control leds in the EDU-CIAA BOARD */
uint8_t initGPIO_leds_EDUCIAA(void)
{
	/** \details This method calls LPCOpen functions to initialize four leds
	 * in the EDU-CIAA board. This method has to be invoked first.
	 * */

	/** Configuration of the GPIO port*/
	Chip_GPIO_Init(LPC_GPIO_PORT);

	/** Pin mappting of RGB leds */
	Chip_SCU_PinMux(LED_RGB_R_MUX_GROUP,LED_RGB_R_MUX_PIN,MD_PUP,FUNC4);
	Chip_SCU_PinMux(LED_RGB_R_MUX_GROUP,LED_RGB_G_MUX_PIN,MD_PUP,FUNC4);
	Chip_SCU_PinMux(LED_RGB_R_MUX_GROUP,LED_RGB_B_MUX_PIN,MD_PUP,FUNC4);

	/** Mapeo de pines Leds 1, 2 y 3 */
	Chip_SCU_PinMux(LED1_MUX_GROUP,LED1_MUX_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED2_MUX_GROUP,LED2_MUX_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED3_MUX_GROUP,LED3_MUX_PIN,MD_PUP,FUNC0);


	/** Configuración como salida para los leds RGB */
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED_RGB_R_GPIO_PORT,(1<<LED_RGB_R_GPIO_PIN)|(1<<LED_RGB_G_GPIO_PIN)|(1<<LED_RGB_B_GPIO_PIN),1);
	/** Configuración como salida para los leds LED1 */
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED1_GPIO_PORT,1<<LED1_GPIO_PIN,OUTPUT_DIRECTION);
	/** Configuración como salida para los leds LED2 y LED3 */
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED2_GPIO_PORT,1<<LED2_GPIO_PIN,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED3_GPIO_PORT,1<<LED3_GPIO_PIN,OUTPUT_DIRECTION);

	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED_RGB_R_GPIO_PORT,(1<<LED_RGB_R_GPIO_PIN)|(1<<LED_RGB_G_GPIO_PIN)|(1<<LED_RGB_B_GPIO_PIN));
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED1_GPIO_PORT,1<<LED1_GPIO_PIN);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED2_GPIO_PORT,1<<LED2_GPIO_PIN);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED3_GPIO_PORT,1<<LED3_GPIO_PIN);

	return TRUE;
}

/** \brief Function to turn on a specific led */
uint8_t ledOn(uint8_t led)
{
	/** \details Function to turn on a specific led at the EDU-CIAA board.
	 * 	\params uint8_t led: this word represent a specific led based on the LED_COLOR enumeration.
	 * */
	uint8_t result = FALSE;

	if (led & YELLOW_LED)
	{
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED1_GPIO_PORT,LED1_GPIO_PIN);
		result = TRUE;
	}
	if (led & RED_LED)
	{
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED2_GPIO_PORT,LED2_GPIO_PIN);
		result = TRUE;
	}
	if (led & GREEN_LED)
	{
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED3_GPIO_PORT,LED3_GPIO_PIN);
		result = TRUE;
	}

	return result;
}

/** \brief Function to turn off a specific led */
uint8_t ledOff(uint8_t led)
{
	/** \details Function to turn off a specific led at the EDU-CIAA board.
		 * 	\params uint8_t led: this word represent a specific led based on the LED_COLOR enumeration.
		 * */
	uint8_t result = FALSE;

	if (led & YELLOW_LED)
	{
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED1_GPIO_PORT,LED1_GPIO_PIN);
		result = TRUE;
	}
	if (led & RED_LED)
	{
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED2_GPIO_PORT,LED2_GPIO_PIN);
		result = TRUE;
	}
	if (led & GREEN_LED)
	{
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED3_GPIO_PORT,LED3_GPIO_PIN);
		result = TRUE;
	}
	return result;
}

/** \brief Function to turn off a specific led */
uint8_t toggleLed(uint8_t led)
{
	/** \details Function to toogle a specific led at the EDU-CIAA board.
	 * 	\params uint8_t led: this word represent a specific led based on the LED_COLOR enumeration.
	 * */
	switch(led)
	{
	case YELLOW_LED:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LED1_GPIO_PORT,LED1_GPIO_PIN);
		break;
	case RED_LED:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LED2_GPIO_PORT,LED2_GPIO_PIN);
		break;
	case GREEN_LED:
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LED3_GPIO_PORT,LED3_GPIO_PIN);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/



/* Otras funciones disponibles
 * Para los leds
 * Chip_GPIO_ClearValue();
 * Chip_GPIO_SetValue();
 * Chip_GPIO_SetPinOutLow();
 * Chip_GPIO_SetPinOutHigh();
 * Chip_GPIO_SetPortOutHigh();
 * Chip_GPIO_SetPinToggle();
 * Chip_GPIO_SetPortToggle();
 *
 * */
