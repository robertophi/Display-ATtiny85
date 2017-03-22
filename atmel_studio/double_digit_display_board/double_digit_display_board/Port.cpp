#include "Port.h"


Port::Port(){
	DDRB = 0xFF; //All output por default
	PORTB = 0xFF; //Todos em HIGH por default
	MCUCR &= ~(0x01 << PUD); //Pull up enabled por default	
}

void Port::setMode(char pin, char mode){
	//Mode 1 -> output
	//Mode 0 -> input
	if( (pin>=0) && (pin <= 5) && ((mode==0)||(mode==1))){
		DDRB = (DDRB & ~(0x01 << pin)) | (mode << pin); 
	}
	
}
void Port::changePullUp(char pin, char pullup){
	char c = DDRB;
	c = (c & (0x01 << pin));
	c = c >> pin;
	//c = 0 -> input
	//c = 1 -> output
	if(c == 0 ){
		PORTB = (PORTB & ~(0x01 << pin)) |(pullup << pin);
	}
	
}
char Port::read(char pin){
	char ch;
	ch = PINB;
	ch = PINB & (0x01 << pin);
	ch = ch >> pin;
	return ch;
}
void Port::write(char pin, char state){
	PORTB = (PORTB & ~(0x01 << pin)) | (state << pin); 
}
void Port::changeGlobalPullup(char mode){
	//mode = 1 -> disable pull ups
	//mode = 0 -> enable pull ups
	if(mode == 1){
		MCUCR |= (0x01 << PUD); 	
	}
	else{
		MCUCR &= ~(0x01 << PUD);
	}
}

