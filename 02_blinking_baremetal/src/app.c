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

/** \brief Bare Metal application of a blinking project without using RTOS in the EDU-CIAA NXP board.
 **
 ** \details
 **	It is mandatory to implement a driver layer of "LEDs" to control them. It is also necessary to apply
 **	as many rules of the MISRA C guideline.
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
 * 20160522 v1.1	source modification based on the new implementation of the RGB driver.
 * 20160502 v1.0.0 	source documentation included
 * 20160422 v0.0.2 	initials initial version leo
 * yyyymmdd v0.0.1 	initials initial version
 */

/*==================[inclusions]=============================================*/
#include "app.h"       /* <= own header */


/*==================[macros and definitions]=================================*/
#define COUNT_DELAY 2000000
#define LEFT 	0
#define RIGHT 	1
#define ELEMENTS_IN_SEQUENCE 3

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
/** \brief Basic delay program implemented in software */
void basicDelay(void)
{
	/** \details Basic delay function to obtain a delay between flashing lights */
	volatile uint32_t i;

	for(i=COUNT_DELAY; i!=0; i--)
	{
		   asm  ("nop");
	}
}

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main(void)
{
//	uint8_t direction = 0;
	uint8_t sequence[ELEMENTS_IN_SEQUENCE]={YELLOW_LED, RED_LED, GREEN_LED};
	uint8_t i;


	edu_ciaa_ledRGB rgb;


	/* Initialization */
	rgb.red = 0;
	rgb.green = 0;
	rgb.blue = 0;

	initGPIO_leds_EDUCIAA();
	initGPIO_switches_EDUCIAA();

	rgb.blue = ON;
	setLedRGB(&rgb);

	while(1)
	{

		for(i=ELEMENTS_IN_SEQUENCE; i!=0; i--)
		{
			ledOn(sequence[ELEMENTS_IN_SEQUENCE-i]);
			basicDelay();

			ledOff(sequence[ELEMENTS_IN_SEQUENCE-i]);
			basicDelay();
		}

		if(readSwitches() == TEC1)
		{
			rgb.blue = ON;
			setLedRGB(&rgb);
		}
		else
		{
			rgb.blue = OFF;
			setLedRGB(&rgb);
		}
		if(readSwitches() == TEC2)
		{
			rgb.red = ON;
			setLedRGB(&rgb);
		}
		else
		{
			rgb.red = OFF;
			setLedRGB(&rgb);
		}

		if(readSwitches() == TEC3)
		{
			rgb.green = ON;
			setLedRGB(&rgb);
		}
		else
		{
			rgb.green = OFF;
			setLedRGB(&rgb);
		}
		if(readSwitches() == TEC4)
		{
			rgb.red = ON;
			rgb.green = ON;
			rgb.blue = ON;
			setLedRGB(&rgb);
		}

	 }
	 return 0;


}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


