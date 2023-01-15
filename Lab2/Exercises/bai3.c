//Tan so voi F91A la 261.08Hz ; F9DB la 293.13Hz; FA87 là 329.14Hz
//Ta khong the tao tan so chinh xac 261.63 vi ta khong the tao duoc mot so thap phan tu hexa (63773.7340901)
//Truong do cua not nhac duoc quyet dinh boi thong so duration

#include<at89x52.h>	
#include<intrins.h>
#define BUZZER P1_5
bit buzz = 0;

unsigned char code notes[] = {
	0xF9, 0x1A, 
	0xF9, 0xDB,
	0xFA, 0x87
};

unsigned char code durations[] = {20, 10, 5};

unsigned char TH0_val = 0, TL0_val = 0, duration = 0, elapsed = 0;
unsigned char curNote = 0;

void InitTimers()
{
	//Timer 0 for note frequency
	//Timer 1 for note duration (interval of 50 ms)
	TMOD = 0x11; 
	TH0 = TH0_val;	 
	TL0 = TL0_val; 
	// 65536 - 50000/1 = 15536 = (3CB0) (1: chu ki bo dinh thoi)
	TH1 = 0x3C;	 // 50 ms
	TL1 = 0xB0; 
	EA = 1;			 
	ET0 = 1;	
	ET1 = 1;
	TR0 = 1;
	TR1 = 1;
}

void main(void)
{
	P0 = 0;					//turn off the 7-seg LEDs
	TH0_val = notes[2*curNote];
	TL0_val = notes[2*curNote+1];
	duration = durations[curNote];
	InitTimers();
	while(1)
	{

	}				
}

void Timer0() interrupt 1
{
	TH0 = TH0_val;	 //reload for playing music
	TL0 = TL0_val;
	buzz = ~buzz;
	BUZZER = buzz;
}

void Timer1() interrupt 3
{
	TH1 = 0x4C;	 //reload for ~50 ms interval
	TL1 = 0x00;
	elapsed++;
	if (elapsed == duration)
	{
		elapsed = 0;
		
		curNote++;
		if (curNote > 2) curNote = 0;
		
		TH0_val = notes[2*curNote];
		TL0_val = notes[2*curNote+1];
		duration = durations[curNote];
	}
}
