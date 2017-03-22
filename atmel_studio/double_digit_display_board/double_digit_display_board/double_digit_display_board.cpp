/*
 * GccApplication1.c
 *
 * Created: 11/03/2017 22:43:20
 *  Author: Roberto
 */ 

//Frequencia e intervalo do serial shifter
#define F_CPU 8000000UL
#define TIME 10


#include <avr/io.h>
#include <util/delay.h>
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




void sendCommand(char cmd);
void sendData(char cmd);

#define DATAPIN PB0
#define SHPIN PB2
#define STPIN PB1
#define LEDPIN PB4
#define SWPIN PB3

Port port;
int main(void)
{
	

	char display[10] = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9};
		

	port.setMode(DATAPIN,OUT); //out pb0
	port.setMode(SHPIN,OUT); //out pb2
	port.setMode(STPIN,OUT); //out pb1
	//port.setMode(SWPIN,IN); 
	//port.changePullUp(SWPIN,0);
	port.setMode(LEDPIN,OUT);
	
	
	
	int n=0,i=0,j=0;
	char ch;
	while(1){
		i = n/10;
		j = n%10;
		
		
		
		
		
		
		sendData(display[j]);
		sendData(display[i]);
		
	
		_delay_ms(300);

		n++;
		if(n>99) n=0;
	
	}
	return 0;

}

void sendData(char data){
	char i,ch;
	port.write(STPIN,0);

	for(i=0;i<8;i++){
		ch = data >> i;
		ch = ch & 0x01;
		port.write(DATAPIN,ch);
		_delay_us(TIME);
		port.write(SHPIN,1);
		_delay_us(TIME);
		port.write(SHPIN,0);
		_delay_us(TIME);
	}
	
	port.write(STPIN,1);
	_delay_us(TIME);
	port.write(STPIN,0);
}



