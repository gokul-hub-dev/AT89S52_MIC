#ifndef _MYHEADER_H
#define _MYHEADER_H
#include <REGX51.H>
#include <string.h>

/***********FRAME_BYTE*******/
#define IDENTITY_BYTE 0xA5
#define START_BYTE 0x5A
#define CHECKSUM(A, B) (A + B + 0xFF)
#define END_BYTE 0xAA

sbit PORT3_PIN2 = P3 ^ 2;
sbit PORT3_PIN3 = P3 ^ 3;
sbit PORT3_PIN4 = P3 ^ 4;
sbit PORT3_PIN5 = P3 ^ 5;
sbit PORT3_PIN6 = P3 ^ 6;
sbit PORT3_PIN7 = P3 ^ 7;

void Int_Uart();
void Tx_char(unsigned char);
void Delay(unsigned int);
unsigned char Rx_char();
void Tx_string(unsigned char *get_data);
void Port3_Init();
unsigned char PORT3_func();
#endif