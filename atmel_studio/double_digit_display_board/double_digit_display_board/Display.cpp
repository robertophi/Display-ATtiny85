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
        n = 99;
        char aux[10] = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9};
        for(int i=0;i<=9;i++){
            display[i] = aux[i];
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
	//Habilita interruptção do EXT0
	//Habilita interrupção por "pin change"
	//Só existe uma interrupção externa comum - INT0
	//Todos os pinos de PCINT[5:0] geram a mesma interrupção

	PCMSK |= (1 << PCINT3);
	//Habilita o pin0 como gerador da interrupção PCINT
	//Poderiamos colocar os outros também, que iriam gerar apenas a mesma interrupção
	sei();
	//Enable Global Interrupt
}
void Display::interrupt(){
	while(Port::read(SWPIN)==0x01){
		n++;
		if(n>99){
			n=99;
		}
		writeDisplay();
		_delay_ms(500);
	}

}
