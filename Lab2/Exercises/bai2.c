//Ta thực hiện loopback để ngay khi một dữ liệu được nhập vào receive thì nó sẽ được cho vào hàng đợi delay rồi hiển thị từng kí tự lên lcd

#include<at89x52.h>	
#include<intrins.h>
#include "string.h"
#define BUZZER P1_5
#define LCD_DATA P0

bit buzz = 0;
sbit EN=P2^7;
sbit RS=P2^6;
sbit RW=P2^5;	   

unsigned char code notes[] = {
	0xF9, 0x1A,
	0xF9, 0xDB,
	0xFA, 0x87};

unsigned char code durations[] = {20, 10, 5};

unsigned char TH0_val = 0, TL0_val = 0, duration = 0, elapsed = 0;
unsigned char curNote = 0;
unsigned char uart_data;

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
	TH1 = 0x4C;	 //50 ms
	TL1 = 0x00; 
	EA = 1;			 
	ET0 = 1;	
	ET1 = 1;
	TR0 = 1;
	TR1 = 1;
	//Timer 2 for baudrate generator
	RCLK = 1;
	TCLK = 1;
	SCON = 0x50; 		// uart in mode 1 (8 bit), REN=1 */
	T2CON = 0x34; 		// Use Timer 2 for uart */
	RCAP2H = 0xFF; 		// 9600 Bds at 11.0592MHz */
	RCAP2L = 0xDC; 		// 9600 Bds at 11.0592MHz */
	ES = 1; 			// Enable serial interrupt*/
	TR2 = 1;	// Timer 2 run
}

void main(void)
{
	
	P0 = 0;					//turn off the 7-seg LEDs
	TH0_val = notes[2*curNote];
	TL0_val = notes[2*curNote+1];
	duration = durations[curNote];
	InitTimers();
	
	Init_System();
	LCD_init();
	
	//LCD_Send_Command(0xC0); //Chuyen con tro xuong dong thu 2
	while(1)
	{

	}				
}

//void Timer0() interrupt 1
//{
//	TH0 = TH0_val;	 //reload for playing music
//	TL0 = TL0_val;
//	buzz = ~buzz;
//	BUZZER = buzz;
//}

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

void serial_IT(void) interrupt 4
{
	if (RI == 1)
	{ 
		RI = 0; 			/* prepare for next reception */
		uart_data = SBUF; 	/* Read receive data */
		SBUF = uart_data; 	/* Send back same data on uart*/
		LCD_Write_One_Char(SBUF);
	}
	else 
		TI = 0; 			/* if emission occur */
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
