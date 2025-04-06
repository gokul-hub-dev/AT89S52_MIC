#include <REGX51.H>

#include <MyHeader.h>

unsigned int i = 0;
unsigned char Rx_Data[5];

void main() {
  Int_Uart();

  P1 = 0x00; // OUTPUT PORT
  P2 = 0x00; // OUTPUT PORT

  while (1) {

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
