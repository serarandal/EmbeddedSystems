#include <xc.h>


// See /opt/microchip/xc8/v{ver}/docs/chips/16f886.html
// for details on #pragma config

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF


void init_uart(void)
{  /* See chapter 12.3 PIC16F886 manual (table 12-5) */

  TXSTAbits.BRGH = 0;
  BAUDCTLbits.BRG16 = 0;

  // SPBRGH:SPBRG = 
  SPBRGH = 0;
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


void main(void)
{ 
  OSCCON = 0b00001000; // External cristal
  init_uart();
  while(1)
      TXREG = "a";
    
 }
