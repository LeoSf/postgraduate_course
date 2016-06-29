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

/** \brief Bare Metal application of the sixth activity present in the activity guide of the course.
 ** \details
 **	The application has to start blinking two LEDs (LED1 and LED2) intermittently, with time on equal
 **	to 250 [ms]. Then if the user press Key1, the RGB LED has to show at least 16 different colors.
 ** This could be achieved using a pseudo PWM technique by software.
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
 * 20160527 v1.2	PWM bright error fixed
 * 20160522 v1.1	source modification based on the new implementation of the RGB driver.
 * 20160502 v1.0.0 	source documentation included
 * 20160422 v0.1 initials initial version leo
 */

/*==================[inclusions]=============================================*/
#include "app.h"       /* <= own header */

/*==================[macros and definitions]=================================*/
#define ELEMENTS_IN_SEQUENCE 3
/** time interval of the RTI timer interrupt in [ms] */
#define TIME_INTERVAL_MS 500
//#define TIME_INTERVAL_US 5000000	/* verificación */
/** time interval of the RTI timer interrupt in [us] */
#define TIME_INTERVAL_US 100
//#define TIME_INTERVAL_US 500	/* t lento para ver en osciloscopio*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** Duty cycle counter to control the PWM of the RGB led. Value from 0 to 100 */
uint8_t dutyCycleCounter = 0;


int main(void)
{
	uint8_t i;

	edu_ciaa_ledRGB rgb;
	/* Initialization */
	rgb.red = 0;
	rgb.red_duty = 0;
	rgb.green = 0;
	rgb.green_duty = 0;
	rgb.blue = 0;
	rgb.blue_duty = 0;

	dutyCycleCounter = 0;

	RITSetTimeInterval_us(TIME_INTERVAL_US);
	RITInitInterrupt();
	initGPIO_leds_EDUCIAA();
	initGPIO_switches_EDUCIAA();


	initGPIO_rgbLed_EDUCIAA();
	initGPIO_keyboard_EDUCIAA();

	while(1)
	{
		fadeRGB(&rgb);
	}
	return 0;
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


