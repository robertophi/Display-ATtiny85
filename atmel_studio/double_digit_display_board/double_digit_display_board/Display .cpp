#include "Display.h"


Display::Display():
    Port::Port() {
        n = 99;
}
void Display::writeDisplay(){
    int i=0,j=0;
	i = n/10;
	j= n%10;
	Port::shift74ch595(display[j],DATAPIN,SHPIN,STPIN);
	Port::shift74ch595(display[i],DATAPIN,SHPIN,STPIN);
}
void Display::interruptSetup();
void Display::interrupt();