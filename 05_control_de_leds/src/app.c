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

/** \brief Bare Metal application of the fifth activity present in the activity guide of the course.
 ** \details
 ** In this program by default it is blinking LED2. Then, the user with:
 ** 	key1 - selects the LED that is on the left of the current LED.
 ** 	key2 - selects the LED that is on the right of the current LED.
 *
 ** 	key3 - increment the frequency of the blinking led
 **		key4 - decrement the frequency of the blinking led
 **
 **	If key1 or key2 stay pressed, the blinking sequence has to be visible.
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
 * 20160522 v1.1	source modification based on the new implementation of the RGB driver.
 * 20160502 v1.0.0 	source documentation included
 * 20160422 v0.1 	initials initial version leo
 */

/*==================[inclusions]=============================================*/
#include "app.h"       /* <= own header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
uint8_t led_counter = 1;

int main(void)
{
	/** Time interval for the RIT timer.
	 * \remark It's important that the blinking frequency is 2/time_interval */
	uint16_t time_interval_ms = 500;

	RITSetTimeInterval_ms(time_interval_ms);
	RITInitInterrupt();

	initGPIO_leds_EDUCIAA();
	initGPIO_switches_EDUCIAA();
	initGPIO_rgbLed_EDUCIAA();

	while(1)
	{
		switch(readSwitches())
		{
			case TEC1:
				led_status = 2;

				if(led_counter == 1)
					led_counter = (1<<6);
				else
					led_counter >>= 1;
				break;
			case TEC2:
				led_status = 2;

				if(led_counter == (1<<6))
					led_counter = 1;
				else
					led_counter <<= 1;
				break;
			case TEC3:
				if ((time_interval_ms-40) > 40)
					time_interval_ms -= 40;
				else
					time_interval_ms = 40;
				RITSetTimeInterval_ms(time_interval_ms);
				RITInitInterrupt();
				break;
			case TEC4:
				if ((time_interval_ms+40) < ((1<<16)-1))
					time_interval_ms += 40;
				else
					time_interval_ms = ((1<<16)-1);
				RITSetTimeInterval_ms(time_interval_ms);
				RITInitInterrupt();
				break;
		}

		BasicDelay(2000000);

	 }
	 return 0;


}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


