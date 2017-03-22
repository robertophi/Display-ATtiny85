#include <avr/io.h>
#include <util/delay.h>

#define IN 0
#define OUT 1
using namespace std;

class Port
{
public:
	Port();
	void setMode(char pin, char mode);
	void changePullUp(char pin, char pullup);
	char read(char pin);
	void write(char pin, char state);
	void changeGlobalPullup(char mode);
	void shift74ch595(char data, char DATAPIN, char SHPIN, char STPIN);
protected:
private:
};