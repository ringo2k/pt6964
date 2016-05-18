/*
 * pt6964.h
 *
 *  Created on: 16.05.2016
 *      Author: ringo
 */

#ifndef PT6964_H_
#define PT6964_H_

#include <avr/io.h>

#define STBPIN PB1
#define STBPORT PORTB
#define STBDDR DDRB


#define CLKPIN PB2
#define CLKPORT PORTB
#define CLKDDR DDRB

#define DIOPIN PB3
#define DIOPORT PORTB
#define DIODDR DDRB
#define DIOPININ PINB

#define CLKSPEED 10

#define HIGH(port, pin) port |= ( 1 << pin)
#define LOW(port, pin) port &= ~( 1 << pin)

#define COMMAND_DISPLAY_ON 0b10001000
#define COMMAND_DISPLAY_OFF 0b10000000

#define COMMAND1 0b00000010
#define COMMAND2_WRITE 0b01000000
#define COMMAND2_READ 0b01000010

#define KEY1 8
#define KEY2 1
#define KEY3 256

typedef struct t_segmentDisplay
{
	uint16_t digit[7];
	uint8_t green_led;
	uint8_t red_led;
	uint8_t point;
	uint8_t display_on;
	uint8_t pwm;

}segmentDisplay;


void init_pt6964();
void write_byte_to_pt6964(uint8_t byte);
void write_display_to_pt6964(segmentDisplay* display);
void write_command_to_pt6964(uint8_t command);

uint16_t read_keys();

void set_int_to_display(int flo, segmentDisplay* display);


#endif /* PT6964_H_ */
