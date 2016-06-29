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

/** \brief Bare Metal application of a LCD HD33780
 ** \details
 **	This application controls a 16x1 LCD, using a library developed by Matias
 **	Ferraro at "Dpto de Electrónica y Laboratorio de Sistemas Embebidos"
 **	University of Catamarca (Argentina). Somo modifications of the source code
 **	has been made.
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
 *	MF			Matias Ferraro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160627 v1.0 Driver base version
 */


#include "app.h"

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

int i=1,j=1,k=1,m=1;
char string_1[12]="Boton->UNO\0";
char string_2[12]="Boton->DOS\0";
char string_3[12]="Boton->TRES\0";
char string_4[16]="Boton->CUATRO\0";
char string_5[16]="Boton->ninguno\0";

int main(void) {

	uint8_t switches = 0;
	/*Inicialización de los Leds */
	initGPIO_leds_EDUCIAA();
//	Inicializar_Led();

	/*Inicialización de las teclas*/
	initGPIO_switches_EDUCIAA();
//	Inicializar_Teclas();

	/*Inicialización de los GPIO para el LCD*/
	lcd_init_port();
	/*Inicialización de LCD*/
	lcd_init();
//	ledOn(GREEN_LED);

	/*Posicionamos el cursor fila 1, columna 1*/
	lcd_gotoxy(1,1);
	lcd_putc('P');	/*Mandamos a mostrar el carácter ‘P’ */
	lcd_putc('U');
	lcd_putc('L');
	lcd_putc('S');
	lcd_putc('A');
	lcd_putc('R');
	lcd_putc(':');


	while(1)
	{

		switches = readSwitches();
//		lcd_gotoxy(1, 1);
//		printf_lcd("        ");
//		lcd_gotoxy(1, 2);
//		printf_lcd("        ");


//		lcd_gotoxy(1, 1);
//		printf_lcd("12345678");
//		lcd_gotoxy(1, 2);
//		printf_lcd("abcdefgh");


		if ((switches & TEC4) != 0)
		{
			ledOn(GREEN_LED);
			lcd_gotoxy(1, 2);
			printf_lcd("        ");
			lcd_gotoxy(1, 2);
			printf_lcd(string_4);
		}
		else
		{
			ledOff(GREEN_LED);
		}

		if ((switches & TEC3) != 0)
		{
			ledOn(RED_LED);
			lcd_gotoxy(1, 2);
			printf_lcd("        ");
			lcd_gotoxy(1, 2);
			printf_lcd(string_3);
		}
		else
		{
			ledOff(RED_LED);
		}

		if ((switches & TEC2) != 0)
		{
		/*. . . . .*/
		}
		if ((switches & TEC1) != 0)
		{
			/*. . . . .*/
		}
	}
	return 0;
}
