/*
 * SEGMENT.h
 *
 *  Created on: Dec 14, 2018
 *      Author: omar ehab
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define DATA_PORT       PORTB
#define DATA_PORT_DIR   DDRB
#define SEGMENT_PORT     PORTA
#define SEGMENT_DIR     DDRA



//copy this isr in your code to multiplex the 7 segment //
/*ISR(TIMER0_OVF_vect)
{   static int s=0;
if(s==1)
{
    s=0;
}
else {s++;}

   PORTA&=~(1<<(s+3));
if(s==1)
{   PORTB=num[s-1];}
else if(s==0)
{   PORTB=num[s+1];}
_delay_us(500);
   PORTA|=(1<<(s+3));
}
 *
 */
void SEGMENT_INIT(void);
void SEGMENT_SETNUM (int num,volatile uint8_t *arr);
void SEGMENT_REFRESH(char value);
void set_brightness(int brightvalue);


#endif /* SEGMENT_H_ */
