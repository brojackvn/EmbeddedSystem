#include<at89x52.h>	
#include<intrins.h>
#include "string.h"
#define BUZZER P1_5
bit buzz = 0;

//Dinh nghia mot so chan de dieu khien den LCD
#define LCD_DATA P0
sbit EN=P2^7;
sbit RS=P2^6;
sbit RW=P2^5;	 

code unsigned int notes[]={
  0xF9, 0x1C, //C4:0
	0xF9, 0xDC, //D4:1
	0xFA, 0x87, //E4:2
	0xFA, 0xD6, //F4:3
	0xFB, 0x66, //G4:4
	0xFB, 0xE6, //A4:5
	0xFC, 0x59, //B4:6
	0xFC, 0x8D, //C5:7
	0xFC, 0xED, //D5:8
	0xFD, 0x43, //E5:9
	0xFD, 0x6A, //F5:10
};

code unsigned int melody[] = {0,2,4,5,4,4,7,6,5,4,5,4,3,2,4};
code unsigned int durations[] = {20,10,20,10,20,10,10,10,10,20,10,10,10,10,40};
unsigned char* nameNote[] = {"DO4", "RE4", "MI4", "FA4", "SOL4", "LA4", "SI4", "DO5", "RE5", "MI5", "FA5"};
unsigned char TH0_val = 0, TL0_val = 0, duration = 20, elapsed = 0;
unsigned char curNote = 0;

//Khai bao prototype cho cac ham
void Init_System();	
void Delay_ms(int interval);  
void LCD_init();
void Wait_For_LCD();
void LCD_Send_Command(unsigned char x);
void LCD_Write_One_Char(unsigned char c);
void LCD_Write_String(unsigned char *s);

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
	InitTimers();
	Init_System();
	LCD_init();
	
	TH0_val = notes[2*melody[curNote]];
	TL0_val = notes[2*melody[curNote]+1];
	duration = durations[melody[curNote]]/2;
	
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
		if (curNote > 14) curNote = 0;
		LCD_Send_Command(0x01);
		TH0_val = notes[2*melody[curNote]];
		TL0_val = notes[2*melody[curNote]+1];
		duration = durations[curNote]/2;
		LCD_Write_String(nameNote[melody[curNote]]);
	}
}

void Init_System()
{
	//Thiet lap LCD o che do doc
	RW=1;	
}
void Delay_ms(int interval)
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<interval;j++);
	}
}
//Ham thuc hien gui mot lenh xuong LCD
void LCD_Send_Command(unsigned char x)
{
	LCD_DATA=x;
	RS=0; //Chon thanh ghi lenh
	RW=0; //De ghi du lieu
	EN=1;
	Delay_ms(1);
	EN=0;		
	Wait_For_LCD(); //Doi cho LCD san sang
	EN=1;		  
}
//Ham khoi tao LCD o che do ghi
//Ham kiem tra va cho den khi LCD san sang
void Wait_For_LCD()
{
	//Delay_By_Timer_0(80);
	Delay_ms(1);
}
void LCD_init()
{
	//LCD_Send_Command(0x38); //Chon che do 8 bit, 2 hang cho LCD
	LCD_Send_Command(0x0E); //Bat hien thi, nhap nhay con tro	
	LCD_Send_Command(0x01); //Xoa man hinh	
	LCD_Send_Command(0x80); //Ve dau dong
	
}
//Ham de LCD hien thi mot ky tu
void LCD_Write_One_Char(unsigned char c)
{
	LCD_DATA=c; //Dua du lieu vao thanh ghi 
	RS=1; //Chon thanh ghi du lieu
	RW=0;
	EN=1;
	Delay_ms(1);	
	EN=0;
	Wait_For_LCD();	
	EN=1;
}
//Ham de LCD hien thi mot xau
void LCD_Write_String(unsigned char *s)
{
	unsigned char length;
	length=strlen(s); //Lay do dai xau
	while(length!=0)
	{
		LCD_Write_One_Char(*s); //Ghi ra LCD gia tri duoc tro boi con tro
		s++; //Tang con tro
		length--;	  		 
	}
}