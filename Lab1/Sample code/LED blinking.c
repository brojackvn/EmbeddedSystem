#include <at89x52.h>

typedef unsigned int u16;	  
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit Beep =  P1^5 ;
unsigned char Time;
u8 code LED_Mask[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};


void delay(u16 i)
{
	while(i--);	
}

void Timer0() interrupt 1
{
	TH0 = 0x3C;	 //reload for ~50 ms interval
    TL0 = 0xB0;
	Time++;
}

void Init()
{
		TMOD = 0x01; 
   TH0 = 0x3C;	 //~50 ms
   TL0 = 0xB0; 
   EA = 1;			 
   ET0 = 1;		 
   TR0 = 1;
}

void Display()
{
	/*
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 
		{
		  case(0):
				LSA=1;LSB=1;LSC=1; break;
			case(1):
				LSA=0;LSB=1;LSC=1; break;
			case(2):
				LSA=1;LSB=0;LSC=1; break;
			case(3):	
				LSA=0;LSB=0;LSC=1; break;
			case(4):
				LSA=1;LSB=1;LSC=0; break;
			case(5):
				LSA=0;LSB=1;LSC=0; break;
			case(6):
				LSA=1;LSB=0;LSC=0; break;
			case(7):
				LSA=0;LSB=0;LSC=0; break;	
		}
		P0=LED_Mask[i];
		delay(100); 	
		P0=0x00;
	}
	*/
		LSA=1;LSB=1;LSC=0;
		
		P0=LED_Mask[9];
		delay(100); 	
		P0=0x00;
}

void DisplayBai3() {
	// u8 p2; p2 = 0;
	
	/*
	for (i = 6; i < 8; ++i) {
			if (i == 7) {
					u8 j;
					for (j = 0; j < 10; ++j) {
							LSA=1;LSB=0;LSC=0;
							P0=LED_Mask[0];
							
							//delay(10000);
						
							LSA=0;LSB=0;LSC=0;
							P0=LED_Mask[j];
							
							delay(10000); 	
							P0=0x00;
					}
			}
			else {
					continue;
			}	
	}
	*/
	u8 i;
	u8 led6 = 0; //led6 = 0;
	u8 led7 = 0; //led7 = 0;
	for(i=6;i<8;i++)
	{
		switch(i)	 
		{
		  case(0):
				LSA=1;LSB=1;LSC=1; break;
			case(1):
				LSA=0;LSB=1;LSC=1; break;
			case(2):
				LSA=1;LSB=0;LSC=1; break;
			case(3):	
				LSA=0;LSB=0;LSC=1; break;
			case(4):
				LSA=1;LSB=1;LSC=0; break;
			case(5):
				LSA=0;LSB=1;LSC=0; break;
			case(6):
				LSA=1;LSB=0;LSC=0; break;
			case(7):
				LSA=0;LSB=0;LSC=0; break;	
		}
		if (i == 6) {
				P0=LED_Mask[led6];
				Timer0();
				//delay(3000);	
				//P0=0x00;
		}
			
		if (i == 6 && led7 == 0) {
				++led6;
				P0=LED_Mask[led6];
				Timer0();
				//delay(3000); 	
				//P0=0x00;
		}
		if (i == 7 && led7 == 10) {
				led7 = 0;
				P0=LED_Mask[led7];
				Timer0();
				//delay(5000); 	
				//P0=0x00;
				i = 5;
		}
		if (i == 7 && led7 != 10) {
				++led7;
				P0=LED_Mask[led7];
				Timer0();
				//delay(5000); 	
				//P0=0x00;
				i = 5;
		}
		if (led6 == 9 && led7 == 9) {
				led6 = -1;
				led7 = 0;
		}
	}
	
}

void main()
{	
	int i = 0;
	for (i = 0; i< 500;i++)
	{
		Beep=~Beep;
		delay(80);
	}
	Beep = 0;
	delay(3000);
	for (i = 0; i< 500;i++)
	{
		Beep=~Beep;
		delay(80);
	}
	Beep = 0;
	delay(3000);
	for (i = 0; i< 500;i++)
	{
		Beep=~Beep;
		delay(80);
	}
	while(1)
	{	
		DisplayBai3();  
	}		
}