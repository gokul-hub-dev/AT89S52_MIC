#include <MyHeader.h>

UINT8 TX_Data[TX_BUFFER];
UINT8 RX_Data[RX_BUFFER];
UINT16 RX_Index = 0;
UINT16 count = 0;


void serial_isr() interrupt 4 {
  unsigned char receivedChar;
  if (RI == 1) {
    RI = 0; // Clear the Receive interrupt flag
    receivedChar = SBUF; // get character in var	
    //if (RX_Index >= 6) RX_Index=0;
    //RX_Data[RX_Index++] = receivedChar; //working
    if (RX_Index >= RST_RX_Index) RX_Index = 0;
    else {
      RX_Data[RX_Index++] = receivedChar; //working
      if (RX_Data[0] != 0xA5) RX_Index = 0;
    }
  }
}

void timer0_isr() interrupt 1 {
  TH0 = 0x4B;
  TL0 = 0xFD;
  count++;
}

void main() {
  Int_Uart();
  Ports_Init();
  while (1) {
    if (count >= 10) {
      Transmit_Data();
      count = 0;
    }
    Delay(10);
    if (RX_Index != 0) {
      Received_Data();
      RX_Index = 0;
      memset(RX_Data, '\0', 6 * sizeof(char));
    }
  }
}