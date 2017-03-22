/*
 * GccApplication1.c
 *
 * Created: 11/03/2017 22:43:20
 *  Author: Roberto
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "Port.cpp"
//Frequencia e intervalo do serial shifter
#define F_CPU 8000000UL
#define TIME 10

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




void sendCommand(char cmd);
void sendData(char cmd);

#define DATAPIN PB0
#define SHPIN PB2
#define STPIN PB1
#define LEDPIN PB3
#define SWPIN PB4

int main(void)
{
	

	//STPIN = data
	//SHPIN = clk
	//DATAPIN = latch
	char display[10] = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9};
	DDRB = 0x00|(0x01 << STPIN )|(0x01 << SHPIN)|(0x01 << DATAPIN)|(0x01<<LEDPIN);
	PORTB = 0x00;
	int n=0,i=0,j=0;
	while(1){
		i = n/10;
		j = n%10;
		
		sendData(display[j]);
		sendData(display[i]);
		_delay_ms(300);
		PORTB=(PORTB^(0x01 << LEDPIN));

		n++;
		if(n>99) n=0;
	
	}
	return 0;

}

void sendData(char data){
	char i,ch;
	PORTB = PORTB & ~(0x01 << STPIN);
	for(i=0;i<8;i++){
		ch = data >> i;
		ch = ch & 0x01;
		ch = ch << DATAPIN;
		
		PORTB = (PORTB & ~(0x01 << DATAPIN)) | ch;
		_delay_us(TIME);
		PORTB = PORTB | (0x01 << SHPIN);
		_delay_us(TIME);
		PORTB = PORTB & ~(0x01 << SHPIN);
		_delay_us(TIME);
	}
	
	PORTB = PORTB | (0x01 << STPIN);
	_delay_us(TIME);
	PORTB = PORTB & ~(0x01 << STPIN);
}