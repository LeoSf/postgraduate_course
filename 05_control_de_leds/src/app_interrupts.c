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

/** \brief Interrupt functions for the current app.
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
 * 20160422 v0.1 initials initial version leo
 */

/*==================[inclusions]=============================================*/
#include "app_interrupts.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
/** Tick counter of the PWM cycle of 100 ticks (used in fade function for RGB )*/
uint8_t tick_counter;

/** Cycle counter of a state before to change to the nex bright value in the fade function of the RGB LED */
uint16_t cycle_counter;

/** Variable to know exactly which status led has to be modified */
uint8_t led_counter;

/** Variable to know if a led has to be on or off. 0-Off 1-On */
uint8_t led_status;

/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/

/** \brief Interrupt Routine Service of the RIT timer used in Activity number five */
void RIT_IRQHandler(void)
{
	/** \details
	 * 	Interrupt Routine Service of the RIT timer used in Activity number five.
	 *	This IRS does a toggle of the selected led in the main function.
	 * */

	/** Clearing of the Interrupt flag */
	RITCleanInterrupt();

	/** Condition when the led is shifted */
	if (led_status == 2)
	{
		ledOff(YELLOW_LED | RED_LED | GREEN_LED);
		ledOffRGB(BLUE_RGB | RED_RGB | GREEN_RGB);
		led_status = 1;
	}

	if (led_status == 1)
	{
		if (led_counter < 8)
			ledOnRGB(led_counter);
		else
			ledOn(led_counter);
		led_status = 0;
	}
	else
	{
		if (led_counter < 8)
			ledOffRGB(led_counter);
		else
			ledOff(led_counter);
		led_status = 1;
	}
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

