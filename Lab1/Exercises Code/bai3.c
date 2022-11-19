
#include <at89x52.h>
#include<intrins.h>
#define GPIO_LED P0
  
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code LED_Mask[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};


int choice = 0;
int c = 5;

int i;
unsigned char Time;
unsigned char LED_Data;
unsigned char maskLED[] = { 0x7E, 0xBD, 0xDB, 0xE7 };

void Init()
{
		TMOD = 0x01; 
    TH0 = 0x3C;	 //~50 ms
    TL0 = 0xB0; 
    EA = 1;			 
    ET0 = 1;		 
    TR0 = 1;
}


void delay(int i)
{
	while(i--);	
}
int led6 = 0, led7 = 0;

void main(){
	Init();
	while(1){
		delay(100);
		
		
		if(Time == 20){
			led7 +=1;
			if(led7 > 9){
				led7 = 0;
				led6 +=1;
			}
			if(led6 > 9){
				led6 = 0;
			}
			Time = 0;
		}
		LSA=1;LSB=0;LSC=0;
		LED_Data = LED_Mask[led6];
		GPIO_LED = LED_Data;
		delay(100);
		
		LSA=0;LSB=0;LSC=0;
		LED_Data = LED_Mask[led7];
		GPIO_LED = LED_Data;
		delay(100);
		
	}
	
		
}


void Timer0() interrupt 1
{
	  TH0 = 0x3C;	 // reload for ~50 ms interval
    TL0 = 0xB0;
		Time++;
}