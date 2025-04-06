#include <REGX51.H>
#include <MyHeader.h>

/********* UART Int ***************/
void Int_Uart()
{
  TMOD = 0x20; //use timer 1, 8 bit auto reload
  SCON = 0x50; // Mode 1, reception enable 
  PCON = 0x80; //enable SMOD register
  TH1 = 0xFD; //9600 baud rate
  //TH1 = 0xFE; //19200 baud rate
  TR1 = 1; //start timer for baud rate generate
  //  ES = 1; // enable serial interrupt
  //  EA = 1; // enable global interrupt bit
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
unsigned char Rx_char()
{
  unsigned char Rx_Data;
  while(RI == 0);
  Rx_Data = SBUF;
  RI = 0;
  return(Rx_Data);
}



