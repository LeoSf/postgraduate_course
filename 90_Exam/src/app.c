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

/** \brief Bare Metal application of the ninth activity present in the activity guide of the course.
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
 * 20160603 v0.1 initials initial version leo
 * 20160610 v1.0 work in progress.
 */

/*==================[inclusions]=============================================*/
#include "app.h"       /* <= own header */

/*==================[macros and definitions]=================================*/
/** time interval of the RTI timer interrupt in [us] */
#define TIME_INTERVAL_US 1000
#define TIME_INTERVAL_MS 100

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
uint8_t option = 0;
/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{
	char uartMessage_T1[] = "Aumento la ganancia\n\r";
	char uartMessage_T2[] = "Disminuyo la ganancia\n\r";
	char uartMessage_T3[] = "MUTE\n\r";
	char uartMessage_T4[] = "Normalización de cuadrados\n\r";


	initGPIO_leds_EDUCIAA();
	initGPIO_switches_EDUCIAA();

	init_DAC_EDUCIAA();
	init_ADC_EDUCIAA();
	init_UART_FTDI_EDUCIAA();

	RITSetTimeInterval_ms(TIME_INTERVAL_MS);
	RITInitInterrupt();


	while(1)
	{
		switch(readSwitches())
		{
			case TEC1:
				option = OPTION1;
				sendString_UART_USB_EDUCIAA(uartMessage_T1, sizeof(uartMessage_T1)/sizeof(char));
				break;
			case TEC2:
				option = OPTION2;
				sendString_UART_USB_EDUCIAA(uartMessage_T2, sizeof(uartMessage_T2)/sizeof(char));
				break;
			case TEC3:
				option = OPTION3;
				sendString_UART_USB_EDUCIAA(uartMessage_T3, sizeof(uartMessage_T3)/sizeof(char));
				break;
			case TEC4:
				option = OPTION4;
				sendString_UART_USB_EDUCIAA(uartMessage_T4, sizeof(uartMessage_T4)/sizeof(char));
				break;
		}
	}
	return 0;

}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


