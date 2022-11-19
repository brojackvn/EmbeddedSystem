#include<at89x52.h>	
#include<intrins.h>
#define GPIO_LED P2

unsigned char Time;
unsigned char LED_Data;

void Init()
{
    TMOD = 0x01; 
    TH0 = 0x3C;	 //~50 ms
    TL0 = 0xB0; 
    EA = 1;			 
    ET0 = 1;		 
    TR0 = 1;		 
}

void main(void)
{
	P0 = 0;					//turn off the 7-seg LEDs
	Time = 0;
	LED_Data = 0xFE;
	Init();
	while(1)
	{
		if (Time == 10)
		{
			LED_Data = _crol_(LED_Data, 1);
			GPIO_LED = LED_Data;
			Time = 0;
		}
	}				
}

void Timer0() interrupt 1
{
	  TH0 = 0x3C;	 //reload for ~50 ms interval
    TL0 = 0xB0;
		Time++;
}