#include "Port.cpp"
class Display : public Port
{
public:
    char n;
    char display[10];
 
	Display();
	void writeDisplay();
	void interruptSetup();
	void interrupt();
	
};