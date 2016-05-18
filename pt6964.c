
#include "pt6964.h"

#include <avr/delay.h>


uint16_t digitLUT[] =
{
 0b1100110011, //0
 0b1000010000, //1
 0b0100111001,
 0b1000111001,
 0b1000011010,
 0b1000101011,
 0b1100101011,
 0b1000010001,
 0b1100111011,
 0b1000111011
};

void init_pt6964()
{
	CLKDDR |= ( 1 << CLKPIN);
	STBDDR |= ( 1 << STBPIN);


	HIGH(STBPORT, STBPIN);
	LOW(CLKPORT, CLKPIN);

}

void write_command_to_pt6964(uint8_t command)
{
	LOW(STBPORT, STBPIN);
	_delay_us(CLKSPEED);
	write_byte_to_pt6964(command);
	_delay_us(CLKSPEED);
	LOW(DIOPORT, DIOPIN);
	HIGH(STBPORT, STBPIN);
}

void set_int_to_display(int flo, segmentDisplay* display)
{
	int digit = 0;

	digit = flo/1000;
	if (digit >= 10)
	{
		digit = 9;
	}
	flo -= digit * 1000;
	display->digit[2] = digit;

	digit = flo/100;
	if (digit >= 10)
	{
		digit = 9;
	}
	display->digit[3] = digit;
	flo -= digit * 100;


	digit = flo/10;
	if (digit >= 10)
	{
		digit = 9;
	}
	display->digit[1] = digit;
	flo -= digit * 10;

	digit = flo;
	if (digit >= 10)
	{
		digit = 9;
	}
	display->digit[4] = digit;

	//display.digit[0] = 0;

	//display.digit[1] = 3; // 3. 11.Bit = rote LED
	//display.digit[2] = 1; // 1.
	//display.digit[3] = 2; // 2.
	//display.digit[4] = digit;
}
void write_display_to_pt6964(segmentDisplay* display)
{
	uint8_t i = 0;
	uint8_t y = 0;
	uint16_t data;


	write_command_to_pt6964(COMMAND2_WRITE);
	DIODDR |= ( 1 << DIOPIN);
	write_command_to_pt6964(COMMAND1);

	if (display->display_on)
	{
		y = COMMAND_DISPLAY_ON;
	} else {
		y = COMMAND_DISPLAY_OFF;
	}

	y |= display->pwm;

	write_command_to_pt6964(y);


	LOW(STBPORT, STBPIN);
	_delay_us(CLKSPEED);
	write_byte_to_pt6964(0b11000000);
	_delay_us(CLKSPEED);

	for ( y = 0; y < 7; y++)
	{
		data = digitLUT[display->digit[y]];

		if (y == 0) {
			if (display->point != 0) {
				data |= 0x04;
			} else {
				data &= ~0x04;
			}
		} else if (y == 1) {
			if (display->red_led != 0) {
				data |= (1 << 11);
			} else {
				data &= ~(1 << 11);
			}
		} else if (y == 4) {
			if (display->green_led != 0) {
				data |= (1 << 11);
			} else {
				data &= ~(1 << 11);
			}
		}

		for (i = 0; i < 16; i++)
		{
			LOW(CLKPORT, CLKPIN);
			_delay_us(CLKSPEED);
			if (data & ( 1 << i ))
			{
				HIGH(DIOPORT, DIOPIN);
			} else {
				LOW(DIOPORT, DIOPIN);
			}
			_delay_us(CLKSPEED);
			HIGH(CLKPORT, CLKPIN);
			_delay_us(CLKSPEED);

		}
	}
	LOW(DIOPORT, DIOPIN);
	HIGH(STBPORT, STBPIN);
	LOW(CLKPORT, CLKPIN);

}
void write_byte_to_pt6964(uint8_t byte)
{
	uint8_t i = 0;
	for (i = 0; i < 8; i++)
	{
		LOW(CLKPORT, CLKPIN);
		_delay_us(CLKSPEED);
		if (byte & ( 1 << i ))
		{
			HIGH(DIOPORT, DIOPIN);
		} else {
			LOW(DIOPORT, DIOPIN);
		}
		_delay_us(CLKSPEED);
		HIGH(CLKPORT, CLKPIN);
		_delay_us(CLKSPEED);

	}

}

uint16_t read_keys() {
	uint8_t i = 0;
	uint16_t key = 0;

	LOW(STBPORT, STBPIN);
	_delay_us(CLKSPEED);
	write_byte_to_pt6964(COMMAND2_READ);
	_delay_us(CLKSPEED);

	LOW(DIOPORT, DIOPIN);
	DIODDR &= ~(1 << DIOPIN);
	HIGH(DIOPORT, DIOPIN);

	for (i = 0; i < 16; i++) {
		LOW(CLKPORT, CLKPIN);
		_delay_us(CLKSPEED);
		if (DIOPININ & ( 1 << DIOPIN)) {
			key |= ( 1 << i);
		}
		_delay_us(CLKSPEED);
		HIGH(CLKPORT, CLKPIN);
		_delay_us(CLKSPEED);

	}

	LOW(DIOPORT, DIOPIN);
	DIODDR |= (1 << DIOPIN);
	HIGH(STBPORT, STBPIN);
	LOW(CLKPORT, CLKPIN);
	DIODDR |= (1 << DIOPIN);

	return key;
}
