#include <inttypes.h>	//short forms for various integer types
#include <avr/io.h>
#include <util/delay.h>
#include"lcd.h"

#define XTAL	16000000L

static void delay(uint16_t us)
{
	while ( us ) us--;
}

int main(void)
{
	InitLCD(0);
	LCDClear();
	uint8_t i = 0;
	DDRB  = 0xff;                  // use all pins on PortB for output 
	PORTB = 0x00;                  // set output high -> turn all LEDs off
	// set OC1A pin as output, required for output toggling
	DDRD |= _BV(PD5);
	// enable 8 bit PWM, select inverted PWM
	TCCR1A =  _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0);
	// timer1 running on 1/8 MCU clock with clear timer/counter1 on Compare Match
	// PWM frequency will be MCU clock / 8 / 512, e.g. with 4Mhz Crystal 977 Hz.
	TCCR1B = _BV(CS11) | _BV(WGM12);
while(1)
	//for (;;)
	{   
		/* dimm LED on */
		for (i=0; i<255; i++)
		{
			OCR1AL = i;			//Note OCR1AL NOT OCR1A
			PORTB=i;
			LCDWriteIntXY(0,0,i,3);	//for debugging
			_delay_ms(50);
			//delay(XTAL/100);	//delay 10 ms just to slow things down
			LCDClear();
		}
		/* dimm LED off */
		for( i=255; i>0; i--)
		{
			OCR1AL = i;         //Note OCR1AL NOT OCR1A   
			PORTB=i;
			LCDWriteIntXY(0,1,i,3);				//for debugging
			_delay_ms(50);
			//delay(XTAL/100);	//delay 10 ms just to slow things down
			LCDClear();
		}
	}
	return 0;
}
