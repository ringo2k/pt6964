/*
 * main.c
 *
 *  Created on: 09.05.2016
 *      Author: ringo
 */

#include <avr/io.h>
#include <avr/delay.h>
#include "pt6964.h"

segmentDisplay display;

int main ()
{
	DDRD |= ( 1 << PD6);
	uint16_t i = 0;
	uint16_t key = 0;


	init_pt6964();
	_delay_ms(10);


	display.display_on = 1;
	display.pwm = 4;


	while(1)
	{
		PORTD ^= ( 1 << PD6);
		write_display_to_pt6964(&display);
		key = read_keys();
		i++;

		if ( key & KEY1)
		{
			display.red_led = 1;
		} else {
			display.red_led = 0;
		}

		if ( key & KEY2)
		{
			display.green_led= 1;
		} else {
			display.green_led= 0;
		}


		if ( key & KEY3)
		{
			display.point= 1;
		} else {
			display.point= 0;
		}



		if (!(i % 50))
		{
			set_int_to_display(1234,&display);
			display.display_on = 1;

		}
		if (!(i % 100))
		{
			display.display_on = 1;
		}
	}
}
