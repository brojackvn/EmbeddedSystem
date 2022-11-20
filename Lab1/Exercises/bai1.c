#include "reg51.h"

void delay(unsigned int time){
		while(time--){};
}

void blink_all(){
		P2= 0xFF;
		delay(50000);
		P2=0x00;
		delay(50000);
		P2=0xFF;
		delay(50000);
}

void blink_cycle_left_to_right(){
		unsigned char i;
		P2=0xFF;
		for(i=0;i<8;++i){
				P2<<=1;
				if(i>0) P2+=1;
				delay(50000);
		}
		P2=0xFF;
}

void blink_cycle_right_to_left(){
		unsigned int i;
		P2=0xFF;
		for(i=0;i<8;++i){
				P2>>=1;
				if(i>0) P2+=1<<7;
				delay(50000);
		}
		P2=0xFF;
}

void bumping() {
		unsigned char i;
		unsigned char left = 0xFF;
		unsigned char right = 0xFF;
		P2 = 0xFF;
		for (i = 0; i < 8; i++) {
				left >>= 1;
				right <<= 1;
				if (i > 0) {
						left += 1 << 7;
						right += 1;
				}
				P2 = left & right;
				delay(50000);
		}
		P2 = 0xFF;
}


void main(){
		while(1){
				blink_all();
				delay(50000);
			
				blink_cycle_left_to_right();
				delay(50000);
				
				blink_cycle_right_to_left();
				delay(50000);
				
				bumping();
				delay(50000);
		}
}