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
#define TIME_INTERVAL_MS 1

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{

	initGPIO_leds_EDUCIAA();
	initGPIO_switches_EDUCIAA();

	init_UART_FTDI_EDUCIAA();
	uint8_t data = 0;

	char uartMessage[] = "echo from remote device [LPC4337]\n\r";

	while(1)
	{
		/* do nothing */
		data = 0;

		/* waiting for keyboard character */

		while (data == 0)
		{
			data = readByte_UART_USB_EDUCIAA();

			switch (data){
				case 'r':
					 /*Toggle Red Led*/
					toggleLed(RED_LED);
					break;
				case 'v':
					 /*Toggle Green Led*/
					toggleLed(GREEN_LED);
					break;
				case 'a':
					 /*Toggle Yellow Led*/
					toggleLed(YELLOW_LED);
					break;
				default:
					data = 0;
			}
		}

		sendString_UART_USB_EDUCIAA(uartMessage, sizeof(uartMessage)/sizeof(char));
	}
	return 0;

}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


