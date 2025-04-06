#include <REGX51.H>
#include <MyHeader.h>
#define TX_CAPACITY 6
unsigned char tx_data[TX_CAPACITY];

unsigned int i;
unsigned char Rx_Data[TX_CAPACITY];


void main() {
  Int_Uart();

  P1 = 0x00; // OUTPUT PORT
  P2 = 0x00; // OUTPUT PORT
	P0 = 0xFF; // INPUT PORT
	Port3_Init();

  while (1) {

		tx_data[0] = IDENTITY_BYTE;
    tx_data[1] = START_BYTE;
    tx_data[2] = P0;
    tx_data[3] = P3;
    tx_data[4] = CHECKSUM(tx_data[2], tx_data[3]);
    tx_data[5] = END_BYTE;
    Tx_string(tx_data);

    Rx_Data[0] = Rx_char();
    if (Rx_Data[0] == IDENTITY_BYTE) {
      for (i = 1; i < 6; i++)
        Rx_Data[i] = Rx_char();
			
			if (Rx_Data[1] == START_BYTE) {
				unsigned char temp  = CHECKSUM(Rx_Data[2], Rx_Data[3]); 
				if ((Rx_Data[4] == temp)&& (Rx_Data[5] == END_BYTE)) 
				{
          P1 = Rx_Data[2];
          P2 = Rx_Data[3];
          memset(Rx_Data, '\0', 6 * sizeof(char));
        } else {
          Tx_string("WRONG CHECKSUM or END_BYTE");
          memset(Rx_Data, '\0', 6 * sizeof(char));
        }
      } else {
        Tx_string("WRONG START_BYTE");
        memset(Rx_Data, '\0', 6 * sizeof(char));
      }
      memset(Rx_Data, '\0', 6 * sizeof(char));
    }
  }
}