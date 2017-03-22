/*
 * GccApplication1.c
 *
 * Created: 11/03/2017 22:43:20
 *  Author: Roberto
 */ 

//Frequencia e intervalo do serial shifter
#define F_CPU 8000000UL
#define TIME 1


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Port.cpp"



//Segmentos e-d-g-f-a-b-c-p
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




void extInterruptSetup();
void writeDisplay();


#define DATAPIN PB0
#define SHPIN PB2
#define STPIN PB1
#define LEDPIN PB4
#define SWPIN PB3

int n=99;
Port port;
char display[10] = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9};
	

int main(void)
{
	

	
		
	
	port.setMode(DATAPIN,OUT); //out pb0
	port.setMode(SHPIN,OUT); //out pb2
	port.setMode(STPIN,OUT); //out pb1
	port.setMode(SWPIN,IN); 
	port.changePullUp(SWPIN,0);
	port.setMode(LEDPIN,OUT);
	
	extInterruptSetup();
	
	
	while(1){
		
		writeDisplay();
		_delay_ms(500);
		if(n<=0) n=100;
		n--;
		
	
	}
	return 0;

}



ISR(PCINT0_vect){
	
	while(port.read(SWPIN)==0x01){
		n++;
		if(n>99){
			n=99;
		}
		writeDisplay();
		_delay_ms(500);
	}
	
}

void writeDisplay(){
	int i=0,j=0;
	i = n/10;
	j= n%10;
	port.shift74ch595(display[j],DATAPIN,SHPIN,STPIN);
	port.shift74ch595(display[i],DATAPIN,SHPIN,STPIN);
}


void extInterruptSetup(){
	
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
	return;
	
}