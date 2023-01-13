#include "at89x52.h" 
typedef unsigned int u16;
typedef unsigned char u8;

sbit k3=P3^2; 
sbit led=P2^0;

void delay(u16 i)
{
	while(i--);
}

void Init()
{
	IT0=1;
	EX0=1;
	EA=1; 
}

void main()
{
	Init(); 
	while(1);
}

void Int0_ISR() interrupt 0 
{
	EA = 0;
	delay(1000); 
	if(k3==0)
	{
		led=~led;
	}
	EA = 1;
}