#include "header.h"
#include <string.h>
#include <stdbool.h>

char string[] = {'H','E','L','L','O','\r','\n','\0'};
volatile char receiveChar = 0;

int main(void)
{	
	SoscConfig();
//	PLLConfig();
//	ClkOutput();
//	LEDConfig();

	SPIConfig();
	
	while(1)
	{
		SPISendChar('H'); //ex2
//		SPISendString (string); //ex4


	}
}

