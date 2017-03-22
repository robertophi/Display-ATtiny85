#include "Display.h"

#define n0 0b11011110
#define n1 0b00000110
#define n2 0b11101100
#define n3 0b01101110
#define n4 0b00110110
#define n5 0b01111010
#define n6 0b11111010
#define n7 0b00001110
#define n8 0b11111110
#define n9 0b00111110


Display::Display():
    Port::Port() {
        n = 15;
		finish = 0;
		Port::write(LEDPIN,0);
        char aux[10] = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9};
        for(int i=0;i<=9;i++){
            display[i] = aux[i];
        }
}

void Display::countdown(){
	if(n != 0){
		n--;
	}
	writeDisplay();
	if((n==0) && (finish == 0)){
		finish =1;
		for(int i=0;i<=10;i++){
			Port::write(LEDPIN,1);
			_delay_ms(100);
			Port::write(LEDPIN,0);
			_delay_ms(100);
		}
	}
	
	

}
void Display::writeDisplay(){
    int i=0,j=0;
	i = n/10;
	j= n%10;
	Port::shift74ch595(display[j],DATAPIN,SHPIN,STPIN);
	Port::shift74ch595(display[i],DATAPIN,SHPIN,STPIN);
}

void Display::interruptSetup(){
	GIMSK |=  (1<<PCIE);
	PCMSK |= (1 << PCINT3);
	sei();
}
void Display::interrupt(){
	char speed=0;
	if(finish == 1){
		finish = 0;
	}
	while(Port::read(SWPIN)==0x01){
		n++;
		speed++;
		if(n>99){
			n=99;
		}
		writeDisplay();
		if(speed<=3){
			_delay_ms(500);
		}
		else if(speed <= 10){
			_delay_ms(200);
		}
		else if(speed<=0xFF){
			_delay_ms(100);
		}
		if(speed>20) speed = 20;
	}


}
