#include <MYHEADER.h>

void Ports_Init() {
  P1 = 0x00; // OUTPUT PORT
  // P2 = 0x00; // OUTPUT PORT
  P2 = 0xFF; // INPUT PORT
  P0 = 0xFF; // INPUT PORT
  Port3_Init();
}

/********* UART Int ***************/
void Int_Uart() {
  // TMOD = 0x20; //use timer 1, 8 bit auto reload
  TMOD = 0x21; //sets the mode1 of Timer0 used for timing & sets the mode2 of Timer1 used for timing
  SCON = 0x50; // Mode 1, reception enable 
  PCON = 0x80; //enable SMOD register
  TH1 = 0xFD; //19600 baud rate
  TR1 = 1; //start timer for baud rate generate
  ES = 1; // enable serial interrupt
  EA = 1; // enable global interrupt bit

  /*********Timer0 Enable***********/
  TH0 = 0x4B; // LOAD THE TIMER VALUE
  TL0 = 0xFD;
  TR0 = 1; // ENABLE TIMER0 INTERRUPT
  ET0 = 1;
}

/******** TX Char ****************/
void Tx_char(unsigned char Tx_Data) {
  SBUF = Tx_Data;
  while (TI == 0);
  TI = 0;
}

/*********TX STRING***************/
void Tx_string(unsigned char * get_data) {
  unsigned int addr = 0;
  while ( * (get_data + addr) != '\0') {
    Tx_char( * (get_data + addr));
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
  /********input***********/
  //  PORT3_PIN2 = 1;
  //  PORT3_PIN3 = 1;
  //  PORT3_PIN4 = 1;
  //  PORT3_PIN5 = 1;
  //  PORT3_PIN6 = 1;
  //  PORT3_PIN7 = 1;
  /******OUTPUT******/
  PORT3_PIN2 = 0;
  PORT3_PIN3 = 0;
  PORT3_PIN4 = 0;
  PORT3_PIN5 = 0;
  PORT3_PIN6 = 0;
  PORT3_PIN7 = 0;
  //PORT3_PIN5 = 0;
  //PORT3_PIN6 = 0;
  //PORT3_PIN7 = 0;
}

void Delay(unsigned int itime) {
  unsigned int i, j;
  for (i = 0; i < itime; i++) // this is For(); loop delay used to define delay value in Embedded C
  {
    for (j = 0; j < 1275; j++);
  }
}

/**************** check the port 3 pin status individually  ****************************/
unsigned char PORT3_func() {

  unsigned char PORT3 = 0x00;
  //  if (PORT3_PIN0 == 0)
  //    PORT3 = PORT3 | 0x01; 
  //  else
  //    PORT3 = PORT3 & 0xFF;
  //	if (PORT3_PIN1 == 0)
  //    PORT3 = PORT3 | 0x02; 
  //  else
  //    PORT3 = PORT3 & 0xFF;
  PORT3 = PORT3 | 0x03;
  if (PORT3_PIN2 == 0)
    PORT3 |= 0x04;
  else
    PORT3 &= 0xFF;
  if (PORT3_PIN3 == 0)
    PORT3 |= 0x08;
  else
    PORT3 = PORT3 & 0xFF;
  if (PORT3_PIN4 == 0)
    PORT3 |= 0x10;
  else
    PORT3 = PORT3 & 0xFF;
  if (PORT3_PIN5 == 0)
    PORT3 |= 0x20;
  else
    PORT3 &= 0xFF;
  if (PORT3_PIN6 == 0)
    PORT3 |= 0x40;
  else
    PORT3 &= 0xFF;
  if (PORT3_PIN7 == 0)
    PORT3 |= 0x80;
  else
    PORT3 &= 0xFF;

  return PORT3;
}
//-----------------transmit section--------------//
void Transmit_Data() {
  TX_Data[0] = IDENTITY_BYTE;
  TX_Data[1] = START_BYTE;
  TX_Data[2] = ~P0;
  TX_Data[3] = ~P2;
  TX_Data[4] = TX_CHECKSUM(TX_Data[2], TX_Data[3]);
  TX_Data[5] = END_BYTE;
  Tx_char(TX_Data[0]);
  Tx_char(TX_Data[1]);
  Tx_char(TX_Data[2]);
  Tx_char(TX_Data[3]);
  Tx_char(TX_Data[4]);
  Tx_char(TX_Data[5]);
}
/*
		7 6 5 4 3 2 1 0 - pin
		8 4 2 1 8 4 2 1- bit
*/
void Rx_012Bit(UINT8 *Rx_data2) //Checking 0,1,2 bits
{
  if (((*Rx_data2 & 0x01) == 0) && ((*Rx_data2 & 0x02) == 0) && ((*Rx_data2 & 0x04) == 0x04)) {
    //return ~(0x00); //6th bit low & 7th bit low
    PORT3_PIN2 = 0;//RLG3_STS1
    PORT3_PIN3 = 0;//RLG3_STS2
  } else if (((*Rx_data2 & 0x01) == 0x01) && ((*Rx_data2 & 0x02) == 0) && ((*Rx_data2 & 0x04) == 0)) {
    //return ~(0x40); // 6th bit high & 7th bit low
    PORT3_PIN2 = 1;
    PORT3_PIN3 = 0;
  } else if (((*Rx_data2 & 0x01) == 0) && ((*Rx_data2 & 0x02) == 0x02) && ((*Rx_data2 & 0x04) == 0)) {
    //return ~(0x80); // 6th bit low & 7th bit high
    PORT3_PIN2 = 0;
    PORT3_PIN3 = 1;
  } else if (((*Rx_data2 & 0x01) == 0x01) && ((*Rx_data2 & 0x02) == 0x02) && ((*Rx_data2 & 0x04) == 0)) {
    //return ~(0xC0); // 6th bit high & 7th bit high
    PORT3_PIN2 = 1;
    PORT3_PIN3 = 1;
  } else {
    PORT3_PIN2 = 0;
    PORT3_PIN3 = 0;
    //return ~(0x00); //6th bit low & 7th bit low
  }
}

void Rx_345Bit(UINT8 *Rx_data3) //Checking 3,4,5 bits 
{
  //	UINT8 _port3;
  if (((*Rx_data3 & 0x08) == 0) && ((*Rx_data3 & 0x10) == 0) && ((*Rx_data3 & 0x20) == 0x20)) {
    //_port3=(0x00); //2th bit low & 3th bit low
    PORT3_PIN4 = 0;//RLG4_STS1
    PORT3_PIN5 = 0;//RLG4_STS2
  } else if (((*Rx_data3 & 0x08) == 0x08) && ((*Rx_data3 & 0x10) == 0) && ((*Rx_data3 & 0x20) == 0)) {
    //_port3=(0x04); //2th bit high & 3th bit low
    PORT3_PIN4 = 1;
    PORT3_PIN5 = 0;
  } else if (((*Rx_data3 & 0x08) == 0) && ((*Rx_data3 & 0x10) == 0x10) && ((*Rx_data3 & 0x20) == 0)) {
    //_port3=(0x08); //2th bit low & 3th bit high
    PORT3_PIN4 = 0;
    PORT3_PIN5 = 1;
  } else if (((*Rx_data3 & 0x08) == 0x08) && ((*Rx_data3 & 0x10) == 0x10) && ((*Rx_data3 & 0x20) == 0)) {
    //_port3=(0x0C); //2th bit high & 3th bit high
    PORT3_PIN4 = 1;
    PORT3_PIN5 = 1;
  } else {
    //_port3=(0x00);
    PORT3_PIN4 = 0;
    PORT3_PIN5 = 0;
  }
  //(Rx_data4>=3)&&(_port3=_port3|0x10)||_port3;
	//(Rx_data4>=3)&&(PORT3_PIN4=0)||(PORT3_PIN4=1);
}

void Received_Data() {
  if (RX_Data[0] == IDENTITY_BYTE) {
    if (RX_Data[1] == START_BYTE) {
      unsigned char temp = RX_CHECKSUM(RX_Data[2], RX_Data[3],RX_Data[4]);
      if ((RX_Data[5] == temp) && (RX_Data[6] == END_BYTE)) {
				P1=RX_Data[2];
        Rx_012Bit(&RX_Data[2]); 
        Rx_345Bit(&RX_Data[2]);
				if(RX_Data[4]>=3)
				{
					(PORT3_PIN6=1);
					(PORT3_PIN7=1);
				}
				else
				{
					(PORT3_PIN6=0);
					(PORT3_PIN7=0);
				}
      }// else {
        //RX_Index=0;
        //Tx_string("WRONG CHECKSUM or END_BYTE");
        //memset(RX_Data, '\0', 7 * sizeof(char));
      //}
    } //else {
      //RX_Index=0;
      //Tx_string("WRONG START_BYTE");
      //memset(RX_Data, '\0', 7 * sizeof(char));
    //}
  } //else {
    //RX_Index=0;
    //Tx_string("IDENTITY WRONG");
    //memset(RX_Data, '\0', 7 * sizeof(char));
  //}
}
void cli()
{
	 ES = 0; // disable interrupt bit
}
void sei()
{
	ES = 1; // enable interrupt bit
}