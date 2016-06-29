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

/** \brief Bare Metal Blinking Methods driver for the RGB led.
 **
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
 * 20160601 v1.1.1 documentation of the driver translation
 * 20160520 v1.1.0 end of documentation for the rgb driver.
 * 20160506 v1.0.0 base version with FSM (leo)
 * 20160422 v0.1 initials initial version leo
 */

/*==================[inclusions]=============================================*/
#include "rgbled.h"

/*==================[macros and definitions]=================================*/
#define TRUE 	0xFF
#define FALSE 	0x00

/* Mapeo de pines Leds RGB
 * P2_0  in GPIO 5[0], LED0R and enable the pull up.
 * P2_1  in GPIO 5[1], LED0G and enable the pull up.
 * P2_2  in GPIO 5[2], LED0B and enable the pull up.
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

#define OUTPUT_DIRECTION 1
#define INPUT_DIRECTION 0

/** Maximum number of repetition of a brightness level before it changes. value multiple of 10 */
#define MAX_CYCLE_REPETITION 40
/** Increment of the intensity when fade function is called */
#define DELTA_INTENSITY 1

/*==================[internal data declaration]==============================*/

/** Finite State Machine initialized in the first state by default */
fade_sequence_rgb FSM = {START, GREEN_RGB, 0, 0};

/** Transition counter of the different states in the FSM */
 uint16_t fsmCounterState = 0;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/** \brief Red fade function of the RGB LED in the EDU-CIAA Board */
void fadeRed(edu_ciaa_ledRGB *prgb)
{
	/** \details It modifies the intensity of the red LED using a technique that
	 * imitate the behavior of a PWM signal. So, it changes the duty cycle of the signal
	 * that drives the LED.
	 *
	 * \param edu_ciaa_ledRGB *prgb: struct pointer of a RGB LED.
	 * */
	uint8_t redInit = TRUE;
	static uint16_t cycle_red_max = 0;
	static uint8_t redDeltaIntensity = DELTA_INTENSITY;

	if(FSM.current_cycle != cycle_counter)
	{
		fsmCounterState++;
		if (redInit == TRUE)
		{
			cycle_red_max = cycle_counter + MAX_CYCLE_REPETITION;
			redInit = FALSE;
			prgb->red_duty += redDeltaIntensity;
		}
		else
			if(cycle_counter >= cycle_red_max)
				redInit = TRUE;

		FSM.current_cycle = cycle_counter;


		if (prgb->red_duty >= 100 )
		{
			redDeltaIntensity = -redDeltaIntensity;
		}
		else
			if(prgb->red_duty <= 0 )
			{
				redDeltaIntensity = -redDeltaIntensity;
//				prgb->red_duty = 0;
			}
	}

	if(tick_counter < prgb->red_duty)
		prgb->red = ON;
	else
		prgb->red = OFF;

	setLedRGB(prgb);
}

/** \brief Green fade function of the RGB LED in the EDU-CIAA Board */
void fadeGreen(edu_ciaa_ledRGB *prgb)
{
	/** \details It modifies the intensity of the red LED using a technique that
	 * imitate the behavior of a PWM signal. So, it changes the duty cycle of the signal
	 * that drives the LED.
	 *
	 * \param edu_ciaa_ledRGB *prgb: struct pointer of a RGB LED.
	 * */
	uint8_t greenInit = TRUE;
	static uint16_t cycle_green_max = 0;
	static uint8_t greenDeltaIntensity = DELTA_INTENSITY;

	if(FSM.current_cycle != cycle_counter)
	{
		fsmCounterState++;
		if (greenInit == TRUE)
		{
			cycle_green_max = cycle_counter + MAX_CYCLE_REPETITION;
			greenInit = FALSE;
			prgb->green_duty += greenDeltaIntensity;
		}
		else
			if(cycle_counter >= cycle_green_max)
				greenInit = TRUE;

		FSM.current_cycle = cycle_counter;


		if (prgb->green_duty >= 100 )
		{
			greenDeltaIntensity = -greenDeltaIntensity;
		}
		else
			if(prgb->green_duty <= 0 )
			{
				greenDeltaIntensity = -greenDeltaIntensity;
//				prgb->green_duty = 0;
			}
	}

	if(tick_counter < prgb->green_duty)
		prgb->green = ON;
	else
		prgb->green = OFF;

	setLedRGB(prgb);
}

/** \brief Blue fade function of the RGB LED in the EDU-CIAA Board */
void fadeBlue(edu_ciaa_ledRGB *prgb)
{
	/** \details It modifies the intensity of the red LED using a technique that
	 * imitate the behavior of a PWM signal. So, it changes the duty cycle of the signal
	 * that drives the LED.
	 *
	 * \param edu_ciaa_ledRGB *prgb: struct pointer of a RGB LED.
	 * */
	uint8_t blueInit = TRUE;
	static uint16_t cycle_blue_max = 0;
	static uint8_t blueDeltaIntensity = DELTA_INTENSITY;

	if(FSM.current_cycle != cycle_counter)
	{
		fsmCounterState++;
		if (blueInit == TRUE)
		{
			cycle_blue_max = cycle_counter + MAX_CYCLE_REPETITION;
			blueInit = FALSE;
			prgb->blue_duty += blueDeltaIntensity;
		}
		else
			if(cycle_counter >= cycle_blue_max)
				blueInit = TRUE;

		FSM.current_cycle = cycle_counter;


		if (prgb->blue_duty >= 100 )
		{
			blueDeltaIntensity = -blueDeltaIntensity;
		}
		else
			if(prgb->blue_duty <= 0 )
			{
				blueDeltaIntensity = -blueDeltaIntensity;
//				prgb->blue_duty = 0;
			}
	}

	if(tick_counter < prgb->blue_duty)
		prgb->blue = ON;
	else
		prgb->blue = OFF;

	setLedRGB(prgb);
}
/*==================[external functions definition]==========================*/
/** \brief Initialization funtion of the RGB LED in the EDU-CIAA Board */
uint8_t initGPIO_rgbLed_EDUCIAA(void)
{
	/** \details Port configuration method, mapping pins to GPIO functions to use the RGB LED.
	 *
	 * \return uint8_t: control variable to handle exceptions (not implemented yet).
	 * */

	Chip_GPIO_Init(LPC_GPIO_PORT);											/* Configuración del GPIO */

	Chip_SCU_PinMux(LED_RGB_R_MUX_GROUP,LED_RGB_R_MUX_PIN,MD_PUP,FUNC4);	/* Mapeo del pin del leds rojo del RGB */
	Chip_SCU_PinMux(LED_RGB_R_MUX_GROUP,LED_RGB_G_MUX_PIN,MD_PUP,FUNC4);	/* Mapeo del pin del leds verde del RGB */
	Chip_SCU_PinMux(LED_RGB_R_MUX_GROUP,LED_RGB_B_MUX_PIN,MD_PUP,FUNC4);	/* Mapeo del pin del leds azul del RGB */

	/* Output configuration to RGB LEDs */
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED_RGB_R_GPIO_PORT,(1<<LED_RGB_R_GPIO_PIN)|(1<<LED_RGB_G_GPIO_PIN)|(1<<LED_RGB_B_GPIO_PIN),1);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED_RGB_R_GPIO_PORT,(1<<LED_RGB_R_GPIO_PIN)|(1<<LED_RGB_G_GPIO_PIN)|(1<<LED_RGB_B_GPIO_PIN));

	return TRUE;
}

/** \brief Function to turn on leds in the RGB led */
uint8_t ledOnRGB(uint8_t leds)
{
	/** \details Method to turn on one or more leds of the RGB led. This is achived
	 * using only a 1 byte width word, where the first three bits represent each led.
	 * \param  uint8_t leds: Desired State on the leds. If the bit is cero, it does nothing.
	 * */
	uint8_t result = 1;
	if(leds & RED_RGB)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED_RGB_R_GPIO_PORT,LED_RGB_R_GPIO_PIN);

	if(leds & GREEN_RGB)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED_RGB_G_GPIO_PORT,LED_RGB_G_GPIO_PIN);

	if(leds & BLUE_RGB)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED_RGB_B_GPIO_PORT,LED_RGB_B_GPIO_PIN);

	return result;
}

/** \brief Function to turn off LEDs in the RGB led */
uint8_t ledOffRGB(uint8_t leds)
{
	/** \details Method to turn off one or more LEDs of the RGB led. This is achieved
	 * using only a 1 byte width word, where the first three bits represent each led.
	 * \param  uint8_t leds: Desired State on the LEDs. If the bit is zero, it does nothing.
	 * */
	uint8_t result = 1;
	if(leds & RED_RGB)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED_RGB_R_GPIO_PORT,LED_RGB_R_GPIO_PIN);

	if(leds & GREEN_RGB)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED_RGB_G_GPIO_PORT,LED_RGB_G_GPIO_PIN);

	if(leds & BLUE_RGB)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED_RGB_B_GPIO_PORT,LED_RGB_B_GPIO_PIN);

	return result;
}

/** \brief Function to toggle all LEDs in the RGB led */
uint8_t toggleLedsRGB(void)
{
	/** \details This method toggle the RGB led without relying on the present state
	 * of the LEDs.
	 * \param none
	 * */
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_RGB_R_GPIO_PORT, LED_RGB_R_GPIO_PIN);
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_RGB_G_GPIO_PORT, LED_RGB_G_GPIO_PIN);
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_RGB_B_GPIO_PORT, LED_RGB_B_GPIO_PIN);
	return TRUE;
}

/** \brief Function to set the different led states in the RGB led. */
uint8_t setLedRGB(edu_ciaa_ledRGB *rgb)
{
	/** \details
	 * This method set the state of the red, yellow and blue led of the RGB led
	 * based on the state of each led in the structure used to represent the RGB led.
	 * \param edu_ciaa_ledRGB *rgb: pointer to a RGB structure.
	 * */
	if(rgb->red == ON)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_RGB_R_GPIO_PORT, LED_RGB_R_GPIO_PIN);
	else
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_RGB_R_GPIO_PORT, LED_RGB_R_GPIO_PIN);

	if(rgb->green == ON)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_RGB_G_GPIO_PORT, LED_RGB_G_GPIO_PIN);
	else
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_RGB_G_GPIO_PORT, LED_RGB_G_GPIO_PIN);

	if(rgb->blue == ON)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED_RGB_B_GPIO_PORT, LED_RGB_B_GPIO_PIN);
	else
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED_RGB_B_GPIO_PORT, LED_RGB_B_GPIO_PIN);

	return 1;
}
/** \brief Fade function to the RGB LED in the EDU-CIAA Board */
void fadeRGB(edu_ciaa_ledRGB *prgb)
{
	/** \details A state machine is implemented to perform the sequence of LEDs triggered by a
	 * request. At the same time, transition periods between states are given by the number of
	 * ticks required to obtain a change in brightness from 0 to 100. divide
	 * The purpose of this method is to accomplish a smooth transition, decreasing the brightness
	 * level of a LED while the next one is increasing it.
	 *
	 * \param edu_ciaa_ledRGB *prgb: struct pointer to a RGB LED. It contains information about
	 * the current state on-off of the three LEDs and the duty cycle of each one, with values
	 * between 0 and 100.
	 * */


	switch (FSM.current_state)
	{
		case START:								/* estado: START - estado inicial luego de reset de la máquina de estados */
		{
			fadeBlue(prgb);						/* ejecución de un período de aumento de brillo para preparar para el siguiente estado.  */

			if(fsmCounterState >= 100)
			{
				fsmCounterState = 0;			/* Reinicio del contador de estados para arrancar con el primero de ellos */
				FSM.current_state = BLUE_RED;	/* siguiente estado: encendido azul y rojo */
			}
		}
		break;
		case BLUE_RED:							/* estado: Blue (decreciente) y Red (creciente) en intensidades lumínicas */
		{
			fadeBlue(prgb);						/* fade de los dos leds necesarios */
			fadeRed(prgb);

			if(fsmCounterState >= 200)			/* condición de salida para siguiente estado */
				FSM.current_state = RED_GREEN;
		}
		break;

		case RED_GREEN:							/* estado: Red (decreciente) y Green (creciente) */
		{
			fadeRed(prgb);						/* Fade de los dos leds correspondientes */
			fadeGreen(prgb);

			if(fsmCounterState >= 400)			/* Condición de salida para el siguiente estado*/
				FSM.current_state = GREEN_BLUE;

		}
		break;

		case GREEN_BLUE:						/* estado: Green */
		{
			fadeGreen(prgb);					/* Fade de los dos leds correspondientes */
			fadeBlue(prgb);

			if(fsmCounterState >= 600)			/* Condición de salida para el siguiente estado*/
			{
				FSM.current_state = BLUE_RED;
				fsmCounterState = 0;			/* Reinicio del contador de estados para la FSM */
			}
		}
		break;

	default:
		FSM.current_state = START;				/* Ante algún problema, estado de START para acondicionar el brillo del led azul */
		break;
	}
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
