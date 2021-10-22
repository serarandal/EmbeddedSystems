#include <xc.h>

// See /opt/microchip/xc8/v1.10/docs/chips/16f886.html
// for details on #pragma config

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF

#pragma intrinsic(_delay)
#define _XTAL_FREQ 20000000 // necessary for __delay_us
char x =0;
int aux = 0;
void init_T0()
{
    OPTION_REGbits.PS=0b111;
    OPTION_REGbits.T0CS=0;
    OPTION_REGbits.PSA=0;
}



void main(void)
{ 

  // OSCCON = 0b01110001;  // Change to internal 8MHz Clock
  OSCCON = 0b00001000; // External cristal

  
  ANSEL = 0;	// Configure as digital all CAD channels
  ANSELH = 0;
  TRISA = 0; 	// Configure port A as output
  TRISB = 0;

  
  init_T0();
  T0IE=1;
  GIE=1;
  
  while(1);
  
  
}


void __interrupt() T0int(void)
{
    
    if (TMR0)
    {
        aux++;
        TMR0=0;
    }
    if(aux == 3095){
    aux = 0;
    TMR0=0;
    x+=1;
    PORTB = x;
    T0IF=0;}
}

