#include "traffic_light_control.h"
#include <p18f4550.h>

const int TC1 = 1;
const int TC2 = 2;
const int TP1 = 3;
const int TP2 = 4;
const int TP3 = 5;
const int TP4 = 6;


const int Vm = 1;
const int Vd = 2;
const int Am = 3;
const int Pv = 4;

void init(void){
    
}
//coloca todos os sem'aforos em vermelho
void reset(void){
    PORTD = 0x0;
    PORTC = 0x0;
    PORTCbits.RC2 = 1;
    PORTDbits.RD0 = 1;
    PORTDbits.RD2 = 1;
    PORTDbits.RD5 = 1;
    PORTDbits.RD6 = 1;
}


void set_light( const int tl, const int cor){
    switch(tl){
        case 1: 
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 0;
            if( cor == Vm){
                PORTCbits.RC2 = 1;
            }else if ( cor == Vd){
                PORTCbits.RC0 = 1;
            }else if ( cor == Am){
                PORTCbits.RC1 = 1;
            }
            break;
        case 2:
            PORTCbits.RC6 = 0;
            PORTDbits.RD4 = 0;
            PORTDbits.RD5 = 0;
            if( cor == Vm){
                PORTDbits.RD5 = 1;
            }else if ( cor == Vd){
                PORTCbits.RC6 = 1;
            }else if ( cor == Am){
                PORTDbits.RD4 = 1;
            }
            break;
        case 3:
            PORTDbits.RD0 = 0;
            PORTDbits.RD1 = 0;
            if( cor == Vm){
                PORTDbits.RD0 = 1;
            }else if ( cor == Vd || cor == Pv){
                PORTDbits.RD1 = 1;
            }
            break;
        case 4:
            PORTDbits.RD2 = 0;
            PORTDbits.RD3 = 0;
            if( cor == Vm){
                PORTDbits.RD2 = 1;
            }else if ( cor == Vd || cor == Pv){
                PORTDbits.RD3 = 1;
            }
            break;
        case 5:
        case 6:
            PORTDbits.RD6 = 0;
            PORTDbits.RD7 = 0;
            if( cor == Vm){
                PORTDbits.RD6 = 1;
            }else if ( cor == Vd  || cor == Pv){
                PORTDbits.RD7 = 1;
            }
            break;
    };
}