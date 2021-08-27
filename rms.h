/* 
 * File:   rms.h
 * Author: ragab
 *
 * Created on May 10, 2018, 8:39 PM
 */

#ifndef RMS_H
#define	RMS_H
#include <xc.h>
#include "stack.h"

/**
 * Fosc=4Mhz  , use  Internal clock (FOSC/4)  so the Fosc =4/4 =1Mhz  
 * T=1/f = 1/1 =1 microsec ---16bit timer  will make overflow every(65536 *1) = 65536 Microsec equal to 65 MilliSecond
 * so 1clk----> 0.001 milliSecond
 *      X ----> 20    milliseconde  
 *  to give overflow every 20milisecond which we want  you need 20000 clk only  
 * so we will place  65536 - 20000 =45536  in counter every overflow --> TMR1L=224  and TMR1H=177;
 *     
 */


void timer1_init();//for initialize timer1 to make delay 20msec
unsigned char LCM(PROCESS *p , unsigned char num_process);//sort the process from highest priority to lowest 
unsigned char RMS_Scheduler(PROCESS *p ,STACK *ps,unsigned char num_process);//RMS scheduler start



#endif	/* RMS_H */

