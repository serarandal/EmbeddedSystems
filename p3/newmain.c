/*
 * File:   newmain.c
 * Author: sgtta
 *
 * Created on 29 de septiembre de 2021, 15:59
 */
#include <xc.h>
#include <stdio.h>

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF
#pragma intrinsic(_delay)
#define _XTAL_FREQ 20000000


int Resultado;
int continua = 0;
char x =0;
int aux = 0;
void init_T0(void)
{
    OPTION_REGbits.PS=0b111;
    OPTION_REGbits.T0CS=0;
    OPTION_REGbits.PSA=0;
}

void init_uart(void)
{  /* See chapter 12.3 PIC16F886 manual (table 12-5) */

  TXSTAbits.BRGH = 0;
  BAUDCTLbits.BRG16 = 0;

  // SPBRGH:SPBRG = 
  SPBRGH = 32;
  SPBRG = 32;  // 9600 baud rate with 20MHz Clock
  
  TXSTAbits.SYNC = 0; /* Asynchronous */
  TXSTAbits.TX9 = 0; /* TX 8 data bit */
  RCSTAbits.RX9 = 0; /* RX 8 data bit */

  PIE1bits.TXIE = 0; /* Disable TX interrupt */
  PIE1bits.RCIE = 0; /* Disable RX interrupt */

  RCSTAbits.SPEN = 1; /* Serial port enable */

  TXSTAbits.TXEN = 0 ; /* Reset transmitter */
  TXSTAbits.TXEN = 1; /* Enable transmitter */
  
 }

void putch(char c)
{ 
    while(!TRMT);
    TXREG = c;
 } 

void __interrupt() T0int(void)
{
    
    if (TMR0)
    {
        aux++;
        TMR0=0;
    }
    if(aux == 1548){
    ADCON0bits.GO_DONE = 1;
    aux = 0;
    TMR0=0;
    T0IF=0;}
    if(!ADCON0bits.GO_DONE)
    {
        continua = 1;
        Resultado = ADRESL;
        Resultado += (ADRESH << 8); 
    }
}


void init_CAD(void)
{
    VCFG1 = 0;
    VCFG0 = 0;
    ADCS0 = 0b0;
    ADCS1 = 0b1;
    ADON = 1;
    CHS3=0 ;
    CHS2=0 ;
    CHS1=0 ;
    CHS0=0 ;
    ADFM = 1;
}

void main(void)
{ OSCCON = 0b00001000; // External cristal
ANSEL = 0b00000001;
ANSELH = 0;  

  init_CAD();
  init_uart();
  init_T0();
  T0IE=1;
  GIE=1;
  TRISA=1;
  TRISB=0;
  
  while(1){
  while(!continua);
  printf("%d\r\n",Resultado);
  PORTB = Resultado;
  continua=0;
  }
}
      
 


