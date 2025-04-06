#ifndef _MYHEADER_H
#define _MYHEADER_H
#include <REGX51.H>

/***********FRAME_BYTE*******/
#define IDENTITY_BYTE 0xA5
#define START_BYTE 0x5A
#define CHECKSUM(A, B, C, D)(A + B + C + D)
#define END_BYTE 0xAA

//sbit Pulse_Input_1 = P1^0;
//sbit Pulse_Input_2 = P1^1;
//sbit Pulse_Input_3 = P1^2;
//sbit Pulse_Input_4 = P1^3;
//sbit Pulse_Input_5 = P1^4;
//sbit Pulse_Input_6 = P1^5;
//sbit Pulse_Input_7 = P1^6;
//sbit Pulse_Input_8 = P1^7;
//sbit Pulse_Input_9 = P0^0;
//sbit Pulse_Input_10 = P0^1;
//sbit Pulse_Input_11 = P0^2;
//sbit Pulse_Input_12 = P0^3;


//// 1 & 3 --- Input
//sbit Input_1 = P1^0;
//sbit Input_2 = P1^1;
//sbit Input_3 = P1^2;
//sbit Input_4 = P1^3;
//sbit Input_5 = P1^4;
//sbit Input_6 = P1^5;
//sbit Input_7 = P1^6;
//sbit Input_8 = P1^7;
////sbit Input_9 = P3^0;
////sbit Input_10 = P3^1;
//sbit Input_11 = P3^2;
//sbit Input_12 = P3^3;
//sbit Input_13 = P3^4;
//sbit Input_14 = P3^5;
//sbit Input_15 = P3^6;
//sbit Input_16 = P3^7;

//// 0 & 2 --- Output
//sbit Output_1 = P0^0;
//sbit Output_2 = P0^1;
//sbit Output_3 = P0^2;
//sbit Output_4 = P0^3;
//sbit Output_5 = P0^4;
//sbit Output_6 = P0^5;
//sbit Output_7 = P0^6;
//sbit Output_8 = P0^7;
//sbit Output_9 = P2^0;
//sbit Output_10 = P2^1;
//sbit Output_11 = P2^2;
//sbit Output_12 = P2^3;
//sbit Output_13 = P2^4;
//sbit Output_14 = P2^5;
//sbit Output_15 = P2^6;
//sbit Output_16 = P2^7;

sbit PORT3_PIN2 = P3 ^ 2;
sbit PORT3_PIN3 = P3 ^ 3;
sbit PORT3_PIN4 = P3 ^ 4;
sbit PORT3_PIN5 = P3 ^ 5;
sbit PORT3_PIN6 = P3 ^ 6;
sbit PORT3_PIN7 = P3 ^ 7;

void Int_Uart();
void Tx_char(unsigned char);
void delay(unsigned int );
unsigned char Rx_char();
void Tx_string(unsigned char *get_data);
void Port3_Init();
#endif