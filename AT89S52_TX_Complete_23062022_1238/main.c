#include <REGX51.H>
#include <MyHeader.h>
#define TX_CAPACITY 6
unsigned char tx_data[TX_CAPACITY];

void main() {
  Int_Uart();
  P0 = 0xFF;
	Port3_Init();
  while (1) {
    tx_data[0] = IDENTITY_BYTE;
    tx_data[1] = START_BYTE;
    tx_data[2] = P0;
    tx_data[3] = P3;
    tx_data[4] = CHECKSUM(IDENTITY_BYTE, START_BYTE, tx_data[2], tx_data[3]);
    tx_data[5] = END_BYTE;
    Tx_string(tx_data);
		//delay(250);
  }
}