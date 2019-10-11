/*
 * main.c
 *
 *  Created on: Dec 3, 2018
 *      Author: omar ehab
 */



#include "UART.h"
#include "ADC.h"
#include "util/delay.h"
#include "BLUETOOTH.h"
#include <avr/io.h>
#include "SEGMENT.h"
#include <avr/interrupt.h>


int i,j;
char b;
volatile uint8_t num[2];
char x;
long temp=0;
char str[20];

ISR(TIMER0_OVF_vect)
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


ISR(USART_RXC_vect)
{   x=UART_recieve_byte();
if(x=='1')
{   SEGMENT_SETNUM(temp,num);
    itoa(temp,str,10);
    BLUETOOTH_SENDSTRING(str);
	PORTD|=(1<<PD7);
}
else if(x=='0')
{   SEGMENT_SETNUM(temp,num);
    itoa(temp,str,10);
    BLUETOOTH_SENDSTRING(str);
	PORTD&=~(1<<PD7);}
}





int main(void)
{
	sei();
	SEGMENT_INIT();
	SEGMENT_REFRESH(0xC2);
    Uart_init(9600);
    ADC_init();
    DDRD|=(1<<PD7);
    PORTD&=~(1<<PD7);
while(1)
	{
	temp=ADC_read(PA5);
	temp*=500;
	temp/=1023;
	SEGMENT_SETNUM(temp,num);
	itoa(temp,str,10);
	BLUETOOTH_SENDSTRING(str);
					_delay_ms(1000);
			}

return 0;
}



