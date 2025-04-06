#ifndef _INT_DEVICE_H
#define _INT_DEVICE_H
#include <REGX51.H>
#include <MyHeader.h>

/********* UART Int ***************/
void Int_Uart()
{
//  TMOD = 0x20; //use timer 1, 8 bit auto reload
	TMOD = 0x21; //sets the mode1 of Timer0 used for timing & sets the mode2 of Timer1 used for timing
  SCON = 0x50; // Mode 1, reception enable 
  PCON = 0x80; //enable SMOD register
  TH1 = 0xFD; //9600 baud rate
  TR1 = 1; //start timer for baud rate generate
  ES = 1; // enable serial interrupt
  EA = 1; // enable global interrupt bit
	
	TH0 = 0x4B; // LOAD THE TIMER VALUE
	TL0 = 0xFD;
	TR0 = 1; // ENABLE TIMER0 INTERRUPT
	ET0 = 1;
}

/******** TX Char ****************/
void Tx_char(unsigned char Tx_Data)
{
  SBUF = Tx_Data;
  while(TI == 0);
  TI = 0;
}

/*********TX STRING***************/
void Tx_string(unsigned char *get_data)
{
	unsigned int addr=0;
	while(*(get_data+addr)!='\0')
	{
		Tx_char(*(get_data+addr));
		addr++;
	}
}

/******** RX Char ****************/
//unsigned char Rx_char()
//{
//  unsigned char Rx_Data;
//  while(RI == 0);
//  Rx_Data = SBUF;
//  RI = 0;
//  return(Rx_Data);
//}

/********PORT 3 init***************/ //DON'T REMOVE. IF REMOVE SERIAL WILL NOT WORK
void Port3_Init() {
  PORT3_PIN2 = 1;
  PORT3_PIN3 = 1;
  PORT3_PIN4 = 1;
  PORT3_PIN5 = 1;
  PORT3_PIN6 = 1;
  PORT3_PIN7 = 1;
}

void Delay(unsigned int itime)
{
unsigned int i,j;
	for (i=0;i<itime;i++) // this is For(); loop delay used to define delay value in Embedded C
	{
		for (j=0;j<1275;j++);
	}
}

#endif




