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


const int DATAPIN = PB0;
const int SHPIN = PB2;
const int STPIN = PB1;
const int LEDPIN = PB4;
const int SWPIN = PB3;

#include "Display.cpp"	

Display display;
int main(void)
{

	display.Port::setMode(DATAPIN,OUT); //out pb0
	display.Port::setMode(SHPIN,OUT); //out pb2
	display.Port::setMode(STPIN,OUT); //out pb1
	display.Port::setMode(SWPIN,IN);
	display.Port::changePullUp(SWPIN,0);
	display.Port::setMode(LEDPIN,OUT);
	display.interruptSetup();

	while(1){

		display.countdown();
		_delay_ms(500);	
	
	}
	return 0;

}



ISR(PCINT0_vect){
	display.interrupt();	
}