/* 
 * File:   traffic_light_control.h
 * Author: IEUser
 *
 * Created on November 23, 2015, 3:05 PM
 */

#ifndef TRAFFIC_LIGHT_CONTROL_H
#define	TRAFFIC_LIGHT_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif
    extern const int TC1;
    extern const int TC2;
    extern const int TP1;
    extern const int TP2;
    extern const int TP3;
    extern const int TP4;
    extern const int TP5;
    
    extern const int Vm;
    extern const int Vd;
    extern const int Am;
    extern const int Pv;
    
    void init(void);
    void reset(void);
    void set_light(const int tl, const int cor);


#ifdef	__cplusplus
}
#endif

#endif	/* TRAFFIC_LIGHT_CONTROL_H */

