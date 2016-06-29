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

/** \brief Blinking Bare Metal driver for the RGB led.
 **
 **
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
#include "timers.h"       /* <= own header */

/*==================[macros and definitions]=================================*/
//#define COUNT_DELAY 800
//#define COUNT_DELAY #define COUNT_DELAY 2000000

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
uint32_t timeIntervalRTIms = 0;
uint32_t timeIntervalRTIus = 0;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void BasicDelay(uint32_t count_delay){
	volatile uint32_t i;

	for(i=count_delay; i!=0; i--)
	{
		   asm  ("nop");
	}
}

/** \brief Set timer interval value in microseconds */
void Chip_RIT_SetTimerIntervaluS(LPC_RITIMER_T *pRITimer, uint32_t time_interval_us)
{
	/** \details
	 * This method is a copy of Chip_RIT_SetTimerInterval provided by vendor, in which
	 * I made a minimal change to obtain a function that uses as parameter a number
	 * in microseconds to interrupt with the RIT timer
	 *
	 * \param LPC_RITIMER_T *pRITimer: pointer to the RIT timer.
	 * \param uint32_t time_interval_us: time interval in microseconds.
	 *
	 * \return nothing
	 * */
	uint32_t cmp_value;

	/* Determine approximate compare value based on clock rate and passed interval */
	cmp_value = (Chip_Clock_GetRate(CLK_MX_RITIMER)/1000000) * time_interval_us;

	/* Set timer compare value */
	Chip_RIT_SetCOMPVAL(pRITimer, cmp_value);

	/* Set timer enable clear bit to clear timer to 0 whenever
	   counter value equals the contents of RICOMPVAL */
	Chip_RIT_EnableCTRL(pRITimer, RIT_CTRL_ENCLR);
}

void RITSetTimeInterval_ms(uint32_t timeInterval)
{
	timeIntervalRTIms = timeInterval;
//	Chip_RIT_SetTimerInterval(LPC_RITIMER,timeInterval);
}

void RITSetTimeInterval_us(uint32_t timeInterval)
{
	timeIntervalRTIus = timeInterval;
//	Chip_RIT_SetTimerIntervaluS(LPC_RITIMER,timeInterval);
}

uint32_t RITGetTimeIntervalms(void)
{
	return timeIntervalRTIms;
}
uint32_t RITGetTimeIntervalus(void)
{
	return timeIntervalRTIus;
}

void RITInitInterrupt(void)
{
	Chip_RIT_Init(LPC_RITIMER);
	if( timeIntervalRTIms != 0 )
		Chip_RIT_SetTimerInterval(LPC_RITIMER,timeIntervalRTIms);
	else
		Chip_RIT_SetTimerIntervaluS(LPC_RITIMER,timeIntervalRTIus);
//	NVIC_ClearPendingIRQ(RITIMER_IRQn);
	NVIC_EnableIRQ(RITIMER_IRQn);
}

void RITCleanInterrupt(void)
{
	Chip_RIT_ClearInt(LPC_RITIMER);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

