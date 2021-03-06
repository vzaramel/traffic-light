#include<p18f4550.h>
#include<delays.h>
#include "traffic_light_control.h"


#pragma config FOSC=HS
#pragma config WDT=OFF
#pragma config MCLRE=ON
#pragma config LVP=OFF
#pragma config BOR=OFF
#pragma config CPUDIV=OSC1_PLL2
#pragma config CCP2MX=ON

void delay_ms (unsigned int tempo);
void INTs (void);
void config_timer2(void);


const float TIME_MULT = 0.1; //Multiplicador de tempo para ajustar os segundoss
    
void InterruptServiceHigh(void);

#pragma code

unsigned char proximo_estado=0;
unsigned char apertou_btn = 0;
void main ()
{
    TRISC = 0;
    TRISD = 0;
    
    DDRBbits.RB0 = 1;
    ADCON0bits.ADON=0;
    ADCON1= 0xFF;
    RCONbits.IPEN=0;     //desliga interrupcoes com prioridade
    INTCONbits.GIE=1;    //liga interrupcoes globais
    INTCONbits.PEIE=1;
    INTCONbits.INT0IE = 1;
    INTCONbits.INT0IF = 0;
    INTCONbits.RBIE = 0;
    INTCONbits.RBIF = 0;
    INTCONbits.PEIE_GIEL = 0;
    INTCON2bits.INTEDG0 = 1;
   
    PIR1bits.TMR2IF=0;   //Flag de interrupcao ZERADO
    PIE1bits.TMR2IE=1;   //liga a interrupcao do timer 2
    
    init(); //Inicia os registradores para ligar as portas referentes aos leds
    //reset(); //coloca todos os leds vermelhos ativos
    config_timer2();
    while (1)
    {
        switch(proximo_estado){
            case 0:
                reset();//reseta todos os sem'aforos para a configura'c~ao padr~ao
                set_light(TC1, Vd);
                set_light(TP2, Vd);
                delay_ms(TIME_MULT*45*1000);
                proximo_estado = 1;
                break;
            case 1:
                set_light(TC1, Am);
                set_light(TP2, Pv);
                delay_ms(TIME_MULT*15*1000);
                proximo_estado = 2;
                break;
            case 2:
                set_light(TC1, Vm);
                set_light(TC2, Vd);
                set_light(TP1, Vd);
                set_light(TP2, Vm);
                delay_ms(TIME_MULT*45*1000);
                proximo_estado = 3;
                break;
            case 3:
                set_light(TC2, Am);
                if( !apertou_btn){
                    set_light(TP1, Pv);
                }
                delay_ms(TIME_MULT*15*1000);
                if(apertou_btn){
                    proximo_estado = 4;
                }else{
                    proximo_estado = 0;
                }
                break;
            case 4:
                set_light(TC2, Vm);
                set_light(TP2, Vd);
                set_light(TP3, Vd);
                set_light(TP4, Vd);
                delay_ms(TIME_MULT*10*1000);
                proximo_estado = 5;
                break;
            case 5:
                set_light(TP1, Pv);
                set_light(TP2, Pv);
                set_light(TP3, Pv);
                set_light(TP4, Pv);
                delay_ms(TIME_MULT*5*1000);
                proximo_estado = 0;
                apertou_btn = 0;
                break;
        }
    }
}


void config_timer2(void)
{
    T2CONbits.TMR2ON=1;   //LIGA O TIMER 2
    T2CONbits.T2CKPS0=1;  //------------------
    T2CONbits.T2CKPS1=1;  // PRE-ESCALA 1:16
    T2CONbits.T2OUTPS0=1; //------------------
    T2CONbits.T2OUTPS1=1; //   POS-ESCALA
    T2CONbits.T2OUTPS2=1; //      1:16
    T2CONbits.T2OUTPS3=1; //------------------
    TMR2=0x00;            //VALOR INICIAL EM ZERO
    PR2=255; //OU OxOO    //VALOR FINAL EM 255
    //TEMPO = CICLO_DE_MAQUINA * PRES * POS * (PR2+1)
    //TEMPO = (1/20000000)*4)  * (16)   (16)* (255+1)
    //TEMPO = 13,1mS
}

void delay_ms (unsigned int tempo)
{
    unsigned int i;
    for(i=0;i<tempo;i++)
    {
        Delay1KTCYx(5);
    }
}

// High priority interrupt vector

#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh(void)
{
    _asm
        goto InterruptServiceHigh
    _endasm
}
// Interrupt Service Routine

// Interrupt pragma for high priority

#pragma code
#pragma interrupt InterruptServiceHigh
void InterruptServiceHigh()
{
    if(INTCONbits.INT0IF)
    {
        apertou_btn = 1;
        
        INTCONbits.INT0IF = 0;
    }
}


