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

/** \brief Final Exam of the postgraduate course.
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
/* DAC Resolution  TODO it's the same that in the driver file of the DAC */
# define DAC_RESOLUTION	10
# define DAC_MAX_VALUE 	((1<<DAC_RESOLUTION)-1)
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/


/*==================[external data definition]===============================*/
extern uint8_t option;

/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/
/** \brief Interrupt Routine Service of the RIT timer used in ... */
void RIT_IRQHandler(void)
{
	/** \details
	 *	RIT timer interrupt to acquire a signal of 10 HZ
	 * */
	uint16_t adc_valueRead = 0;
	uint16_t dac_valueOut = 0;
	static uint16_t gain = 1<<8;

	RITCleanInterrupt();
	adc_valueRead = read_ADC_value_pooling();

	toggleLed(YELLOW_LED);

	switch(option)
	{
		case OPTION1:
			gain += 1;
			break;
		case OPTION2:
			gain -= 1;
			break;
		case OPTION3:
			gain = 0;
			break;
		case OPTION4:
			gain = adc_valueRead;
			break;
	}
	dac_valueOut = gain * adc_valueRead/(1<<8);
	if (dac_valueOut > DAC_MAX_VALUE)
	{
		dac_valueOut = DAC_MAX_VALUE;
	}
	update_DAC_value(dac_valueOut);


}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

