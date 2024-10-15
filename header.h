#define SET_BIT 1
#define CLEAR_BIT 0

#define PCC_PORTD (0x40065000u + 0x130u) //PORTD PIN 15
#define PORTD_PCR15 (0x4004C000u + 0x3Cu)
#define GPIOD_PDDR (0x400FF0C0u + 0x14u)
#define GPIOD_PDOR (0x400FF0C0u + 0x0u)

#define PCC_PORTC (0x40065000u + 0x12Cu) //PORTC PIN 13 
#define PORTC_PCR15 (0x4004B000u + 0x34u)
#define GPIOC_PDDR (0x400FF080u + 0x14u)
#define GPIOC_PDIR (0x400FF080u + 0x10u)

#define SYSTICK_CTRL (0xE000E010)
#define SYSTICK_LOAD (0xE000E014)
#define SYSTICK_VAL (0xE000E018)

#define SCG_RCCR (0x40064000u + 0x14u)
#define SCG_SPLLCSR (0x40064000u + 0x600u)
#define SCG_SPLLDIV (0x40064000u + 0x604u)
#define SCG_SPLLCFG (0x40064000u + 0x608u)
#define SCG_SOSCCSR (0x40064000u + 0x100u)
#define SCG_SOSCDIV (0x40064000u + 0x104u)
#define SCG_SOSCCFG (0x40064000u + 0x108u)

#define PCC_PORTB (0x40065000u + 0x128u) //PCC_PORTB
#define PCC_LPSPI0 (0x40065000u + 0xB0u) //SPI0
#define PCC_LPSPI1 (0x40065000u + 0xB4u) //SPI1
#define PORTB_PCR14 (0x4004A000u + 0x38u) //PORTB 14
#define PORTB_PCR15 (0x4004A000u + 0x3Cu) //PORTB 15
#define PORTB_PCR16 (0x4004A000u + 0x40u) //PORTB 16
#define PORTB_PCR17 (0x4004A000u + 0x44u) //PORTB 17

typedef struct {
	volatile unsigned int VERID; //0x0
	volatile unsigned int PARAM; //0x4
	volatile unsigned int rev1; //0x8
	volatile unsigned int rev2; //0xc
	volatile unsigned int CR; //10
	volatile unsigned int SR;//14
	volatile unsigned int IER;//18
	volatile unsigned int DER; //1c
	volatile unsigned int CFGR0; //20
	volatile unsigned int CFGR1; //24
	volatile unsigned int rev3; //28
	volatile unsigned int rev4; //2c
	volatile unsigned int DMR0; //30
	volatile unsigned int DMR1; //34
	volatile unsigned int rev5; //38
	volatile unsigned int rev6; //3c
	volatile unsigned int CCR; //40
	volatile unsigned int rev7; //44
	volatile unsigned int rev8; //48
	volatile unsigned int rev9; // 4c 
	volatile unsigned int rev10; // 50 
	volatile unsigned int rev11; // 54 
	volatile unsigned int FCR; //58
	volatile unsigned int FSR; //5c
	volatile unsigned int TCR; //60
	volatile unsigned int TDR; //64
	volatile unsigned int rev12; //68
	volatile unsigned int rev13; //6c
	volatile unsigned int RSR; //70
	volatile unsigned int RDR; //74
}LPSPI_Type;

#define LPSPI0_base_address (0x4002C000u)
#define LPSPI0 ((LPSPI_Type *) LPSPI0_base_address)

#define LPSPI1_base_address (0x4002D000u)
#define LPSPI1 ((LPSPI_Type *) LPSPI1_base_address)

#define LPSPI2_base_address (0x4002E000u)
#define LPSPI2 ((LPSPI_Type *) LPSPI2_base_address)

void SetOrClearBit(unsigned int *address, unsigned char position, unsigned char action);
void SetOrClearMultiBit(unsigned int *address, unsigned char position, unsigned int mask, unsigned char action);
void LEDConfig (void);
void SysTick(void);
void PLLConfig(void);
void SoscConfig(void);
void ClkOutput(void);
void SPIConfig(void);
void SPISendChar(char c);
void SPISendString (char string[]);
