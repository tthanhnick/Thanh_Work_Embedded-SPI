#include "header.h"
#include <string.h>

void SetOrClearBit(unsigned int *address, unsigned char position, unsigned char action)
{
	if (action == SET_BIT)
	{
		*address |= (1U<<position);
	}
	else
	{
		*address &= ~(1U<<position);
	}
	return;
}

void SetOrClearMultiBit(unsigned int *address, unsigned char position, unsigned int mask, unsigned char action)
{
	if (action == SET_BIT)
	{
		*address |= (mask<<position);
	}
	else
	{
		*address &= ~(mask<<position);
	}
	return;
}

void LEDConfig (void)
{
	SetOrClearBit((unsigned int*) PCC_PORTD, 30u, SET_BIT);
	SetOrClearMultiBit((unsigned int*) PORTD_PCR15, 8u, 1u, SET_BIT);
	SetOrClearBit((unsigned int*) GPIOD_PDDR, 15u, SET_BIT); 
	
	SetOrClearBit((unsigned int*) GPIOD_PDOR, 15u, SET_BIT); 
}


void SysTick(void)
{
	SetOrClearBit((unsigned int*) SYSTICK_CTRL, 0, CLEAR_BIT);
	SetOrClearMultiBit((unsigned int*) SYSTICK_VAL, 0, 0, SET_BIT);
	SetOrClearMultiBit((unsigned int*) SYSTICK_LOAD, 0, 800000-1, SET_BIT); //0.1s
	SetOrClearBit((unsigned int*) SYSTICK_CTRL, 0, SET_BIT);
	SetOrClearBit((unsigned int*) SYSTICK_CTRL, 2, SET_BIT);
	SetOrClearBit((unsigned int*) SYSTICK_CTRL, 1, SET_BIT);
}

void PLLConfig(void)
{
	SetOrClearBit((unsigned int*) SCG_SPLLCSR, 0, CLEAR_BIT); //disable SPPCSR
	SetOrClearMultiBit((unsigned int*) SCG_SPLLDIV, 0u, 0b001 , SET_BIT); // div by 1
	SetOrClearMultiBit((unsigned int*) SCG_SPLLDIV, 8u, 0b001 , SET_BIT); // div by 1
	SetOrClearBit((unsigned int*) SCG_SPLLCFG, 0, CLEAR_BIT); //Choose SOSC as input
	SetOrClearMultiBit((unsigned int*) SCG_SPLLCFG, 8, 0b000 , SET_BIT); // div factor 1
	SetOrClearMultiBit((unsigned int*) SCG_SPLLCFG, 16, 0b01000 , SET_BIT); // multi factor 24
	SetOrClearBit((unsigned int*) SCG_SPLLCSR, 23, CLEAR_BIT); // Unlock SPLLCSR
	SetOrClearBit((unsigned int*) SCG_SPLLCSR, 0, SET_BIT); //Enable SPPCSR
}

void SoscConfig(void)
{
	SetOrClearBit((unsigned int*) SCG_SOSCCSR, 0, CLEAR_BIT); // disble SOSCCSR
	SetOrClearBit((unsigned int*) SCG_SOSCCSR, 23, CLEAR_BIT); // Unlock SOSCCSR
	
	SetOrClearMultiBit((unsigned int*) SCG_SOSCDIV, 0u, 0b001 , SET_BIT); //SOSC div 1 div by 1
	SetOrClearMultiBit((unsigned int*) SCG_SOSCDIV, 8u, 0b001 , SET_BIT); //SOSC div 2 div by 1
	
	SetOrClearBit((unsigned int*) SCG_SOSCCFG, 2, SET_BIT); // XTAL - Internal Osc
	SetOrClearBit((unsigned int*) SCG_SOSCCFG, 3, CLEAR_BIT); // Low gain
	
	SetOrClearMultiBit((unsigned int*) SCG_SOSCCFG, 4u, 0b11 , CLEAR_BIT); //0b11 clear range select
	SetOrClearMultiBit((unsigned int*) SCG_SOSCCFG, 4u, 0b10 , SET_BIT); //0b10 Medium range
	
	SetOrClearBit((unsigned int*) SCG_SOSCCSR, 0, SET_BIT); //enable SOSCCSR
}

void ClkOutput(void)
{
	SetOrClearBit((unsigned int*) SCG_RCCR, 24u, CLEAR_BIT); // SPLL CLK
	SetOrClearBit((unsigned int*) SCG_RCCR, 25u, CLEAR_BIT); // SPLL CLK
	SetOrClearBit((unsigned int*) SCG_RCCR, 26u, CLEAR_BIT); // SPLL CLK
	SetOrClearBit((unsigned int*) SCG_RCCR, 27u, CLEAR_BIT); // SPLL CLK
	SetOrClearMultiBit((unsigned int*) SCG_RCCR, 24u, 6u , SET_BIT); // SPLL CLK
	
	SetOrClearMultiBit((unsigned int*) SCG_RCCR, 16u, 0b0000 , SET_BIT); // core div by 1
	SetOrClearMultiBit((unsigned int*) SCG_RCCR, 4u, 0b0001 , SET_BIT); // bus div by 2
	SetOrClearMultiBit((unsigned int*) SCG_RCCR, 0u, 0b1111 , CLEAR_BIT); // divslow by 3	
	SetOrClearMultiBit((unsigned int*) SCG_RCCR, 0u, 0b0010 , SET_BIT); // divslow by 3
}

void SPIConfig(void)
{
	SetOrClearBit((unsigned int*) PCC_PORTB, 30u, SET_BIT); // PCC PORTC CGC
	SetOrClearMultiBit((unsigned int*) PORTB_PCR2, 8u, 3u , SET_BIT); // Port B2: MUX = ALT3, LPSPI0_SCK
	SetOrClearMultiBit((unsigned int*) PORTB_PCR3, 8u, 3u , SET_BIT); // Port B3: MUX = ALT3, LPSPI0_SIN
	SetOrClearMultiBit((unsigned int*) PORTB_PCR4, 8u, 3u , SET_BIT); // Port B4: MUX = ALT3, LPSPI0_SOUT
	SetOrClearMultiBit((unsigned int*) PORTB_PCR5, 8u, 3u , SET_BIT); // Port B5: MUX = ALT3, LPSPI0_PCS1
	
	SetOrClearMultiBit((unsigned int*) PCC_LPSPI0, 24u, 1u, SET_BIT); //SPI PCC PCS
	SetOrClearBit((unsigned int*) PCC_LPSPI0, 30u, SET_BIT); //SPI PCC CGC
	
	LPSPI0->TCR = 0x09000007; // Cannot use each function to turn each bit on. Cannot find issue 
	
//	LPSPI0->TCR |= (0b001<<27); // Prescale div by 2
	LPSPI0->CCR |= (2u <<0); // SCK Div (Div + 2)
	
//	LPSPI0->TCR &= ~(0b11<<30); // CPOL, CPHA = 0
//	
//	LPSPI0->TCR |= (7u<<0); // 8bit = FRAMZ + 1
//	LPSPI0->TCR &=~ (1<<23); // LSBF MSB first
//	
//	LPSPI0->TCR |= (0b01<<24); // PCS 1
	
	LPSPI0->FCR &= ~(0b11<<16); // RXWATER = 0
	LPSPI0->FCR &= ~(0b11<<0); // TXWATER = 0
	LPSPI0->CFGR1 &= ~(1<<3); //  NOSTALL=0 Stall if Tx FIFO empty or Rx FIFO full

	LPSPI0->CFGR1 |= (1<<0); // Master mode
	LPSPI0->CR |= (1<<3); // Debug Enable
	
	LPSPI0->CR |= (1<<0); // Module Enable
}

void SPISendChar(char c)
{
	if ((LPSPI0->SR) & (1<<0)) //Tx FIFO available 
	{
		LPSPI0->TDR = c; // send data
		LPSPI0->SR |= (1<<0); //write 1 to clear
	}
}

void SPISendString (char data_string[])
{
	int i = 0;
	while (data_string [i] != '\0')
	{
		SPISendChar(data_string [i]);
		i++;
	}
}

void SPISendLED(unsigned int address, unsigned int data)
{
	if ((LPSPI0->SR) & (1<<0)) //Tx FIFO available 
	{
		LPSPI0->TDR = address; // send data 'address'
		LPSPI0->SR |= (1<<0); //write 1 to clear
	}
	
	if ((LPSPI0->SR) & (1<<0)) //Tx FIFO available 
	{
		LPSPI0->TDR = data; // send data 'data'
		LPSPI0->SR |= (1<<0); //write 1 to clear
	}
}

void DisplayLetterLED(void)
{
	SPISendLED(decode, 0x00u);
	SPISendLED(intensity, 0x0Au);
	SPISendLED(scan_limit, 0x07u);
	SPISendLED(shut_down, 0x01u);
	SPISendLED(display_test, 0x00u);
	SPISendLED(first_digit, 0x67u); // send 'H'
}