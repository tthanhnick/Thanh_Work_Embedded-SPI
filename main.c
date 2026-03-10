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

	MAX7219Init(); // Initialize MAX7219 once before the loop
			
	while(1)
	{
//		SPISendChar('H'); //ex2
//		SPISendString (string); //ex4
		DisplayLetterLED(); //MAX7219 7 LED Segment 
	}
}
