#include <REGX51.H>
#include <MyHeader.h>
#define TX_CAPACITY 6
unsigned char tx_data[TX_CAPACITY];

unsigned int i;
unsigned int Rx_Addr = 0,one_time = 1;
unsigned char Rx_Data[5];
unsigned int count = 0;

void serial_isr() interrupt 4 {
  unsigned char receivedChar;
  if (RI == 1) {
    RI = 0; // Clear the Receive interrupt flag
    receivedChar = SBUF; // get character in var	
    //		if (Rx_Addr >= 6) Rx_Addr=0;
    //		Rx_Data[Rx_Addr++] = receivedChar; //working
		if (Rx_Addr >= 6) Rx_Addr=0;
		else{
      Rx_Data[Rx_Addr++] = receivedChar; //working
			if(Rx_Data[0] != 0xA5) Rx_Addr=0; 			
		}
  }
}

void timer0_isr() interrupt 1
{
	TH0 = 0x4B;
	TL0 = 0xFD;
	count++;
}

void main() {
  Int_Uart();

  P1 = 0x00; // OUTPUT PORT
 // P2 = 0x00; // OUTPUT PORT
	P2 = 0xFF; // INPUT PORT
	P0 = 0xFF; // INPUT PORT
	Port3_Init();

  while (1) {
		if(count>=10){
		tx_data[0] = IDENTITY_BYTE;
    tx_data[1] = START_BYTE;
    tx_data[2] = P0;
		tx_data[3] = P2;//TEST
    //tx_data[3] = P3;
    tx_data[4] = CHECKSUM(tx_data[2], tx_data[3]);
    tx_data[5] = END_BYTE;
    //Tx_string(tx_data);
			Tx_char(tx_data[0]);
			Tx_char(tx_data[1]);
			Tx_char(tx_data[2]);
			Tx_char(tx_data[3]);
			Tx_char(tx_data[4]);
			Tx_char(tx_data[5]);
			count=0;
		}
		
    	Delay(10);
    if (Rx_Addr != 0){	
      if (Rx_Data[0] == IDENTITY_BYTE) {
        if (Rx_Data[1] == START_BYTE) {
          unsigned char temp = CHECKSUM(Rx_Data[2], Rx_Data[3]);
          if ((Rx_Data[4] == temp) && (Rx_Data[5] == END_BYTE)) {
            P1 = Rx_Data[2];
            //P2 = Rx_Data[3];
						P3 = Rx_Data[3];
						Tx_string("WORKING");
            memset(Rx_Data, '\0', 6 * sizeof(char));
          } 
					else {
						Tx_char(temp);
						Tx_char(Rx_Data[4]);
						Tx_char(Rx_Data[5]);
						Rx_Addr=0;
						Tx_string("WRONG CHECKSUM or END_BYTE");
            memset(Rx_Data, '\0', 6 * sizeof(char));
          }
        } 
				else {
					Rx_Addr=0;
          Tx_string("WRONG START_BYTE");
          memset(Rx_Data, '\0', 6 * sizeof(char));
        }
      }
			else
			{
				Tx_char(Rx_Data[0]);
				Rx_Addr=0;
				Tx_string("IDENTITY WRONG");
        memset(Rx_Data, '\0', 6 * sizeof(char));
			}
			Rx_Addr=0;
			memset(Rx_Data, '\0', 6 * sizeof(char));
    }
	}
}
