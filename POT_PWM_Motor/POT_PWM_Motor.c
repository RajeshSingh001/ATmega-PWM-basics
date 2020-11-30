#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void InitPWM()
{
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);

	
	DDRB|=(1<<PB3);//Set OC0 PIN as output. It is  PB3 on ATmega16 ATmega32
}

void SetPWMOutput(uint8_t duty)// Sets the duty cycle of output. 
{
	OCR0=duty;
}



void Wait()
{
 _delay_loop_2(3200);
}

void main()
{
	uint8_t speed=0;
	InitLCD(0);
	InitPWM();//Initialize PWM Channel 0
	InitADC();//ADC initialization
	LCDClear();
	while(1)//Do this forever
	{
		speed=ReadADC(0);// Read ADC channel 0	
		SetPWMOutput(speed);//Now Set The speed using PWM
		LCDWriteIntXY(0,0,speed,3)// print speed on LCD
		Wait();//Now Wait For Some Time
		
	}
}
