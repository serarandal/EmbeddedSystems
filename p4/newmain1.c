/*
 * File:   newmain1.c
 * Author: sgtta
 *
 * Created on 20 de octubre de 2021, 12:03
 */

#include <xc.h>
#include <stdio.h>

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF
#pragma intrinsic(_delay)
#define _XTAL_FREQ 20000000

int modo = 0;
int aux = 0;
void init_pwm()
{
    PR2=166;
    T2CONbits.TMR2ON=1;  
    CCP1CONbits.P1M=0b00;   //Single output;P1A modulated; P1B,P1C,P1D assigned as port pins
    CCP1CONbits.CCP1M=0b1100; // PWM mode; P1A,P1C active-high; P1B,P1D active-high
    TRISCbits.TRISC2=1;
    CCPR1L=0;
}
void init_ccp2()
{
    CCP2CONbits.CCP2M = 0b1100;
    TRISCbits.TRISC1 = 1;
    CCPR2L = 0;

}

void init_T0()
{
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b111;
    TMR0=157;
}
void init_T1()
{
    TMR2IF=0;
    T2CONbits.T2CKPS=0;
   
}

void __interrupt() intr_T0(void)
{
    
    if(TMR0)
    {
        if(modo == 0)
        {
            CCPR1L++;
            CCPR2L--;
        }
        else if(modo ==1)
        {
            CCPR1L--;
            CCPR2L++;
        }
        
     TMR0=0; 
    }
    if(TMR2IF)
    {
        if(aux==1)
        {
            modo=0;
            TRISCbits.TRISC2=0;
            TRISCbits.TRISC1=0;
            TMR2IF=0;
        }
        else
        {
            aux = 1;
            modo =1;
            TRISCbits.TRISC2=0;
            TRISCbits.TRISC1=0;
            TMR2IF = 0;  
        }
        
    } 
    

    
}


void main(void) {
    INTCONbits.GIE = 1;
    INTCONbits.T0IE= 1;
    init_pwm();
    init_ccp2();
    init_T0();
    init_T1();
    while(1);
    
    
    return;
}
