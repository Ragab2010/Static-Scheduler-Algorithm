/* 
 * File:   main.c
 * Author: ragab
 *
 * Created on May 10, 2018, 7:52 PM
 */

#include "pc.h"
#include "stack.h"



/*
 * 
 */
#define NUM_PROCESS 3


void process1();
void process2();
void process3();

void process1(){
//    for(;;){
//        
//    }
        __delay_ms(4);
       PORTBbits.RB0=1;
       PORTBbits.RB1=0;
       PORTBbits.RB2=0;

}
void process2(){
//    for(;;){
//        
//    }
     __delay_ms(00);
    PORTBbits.RB0=0;
    PORTBbits.RB1=1;
    PORTBbits.RB2=0;

}
void process3(){
//    for(;;){
//        
//    }
     __delay_ms(40);
    PORTBbits.RB0=0;
    PORTBbits.RB1=0;
    PORTBbits.RB2=1;
    
}

void init_led(){
    
     
    TRISBbits.TRISB0 =0;
    TRISBbits.TRISB1 =0;
    TRISBbits.TRISB2 =0;
    PORTBbits.RB0=0;
    PORTBbits.RB1=0;
    PORTBbits.RB2=0;
}

unsigned char i;

int main() {
    /*here we create the processs'*/
    PROCESS p[NUM_PROCESS]={{1 , 4 ,20 ,process1 ,1},
                            {2 , 20 ,80 ,process2,1},
                            {3 , 80 ,120 ,process3 ,1} };
    
    /*here we create stack */
    STACK S;
    /*initialize the stack */
   INITIALIZESTACK(&S);

    /*here we initialize the led at PORTB */
    init_led();
    
    /*here we call the RMS Scheduler */
    RMS_Scheduler(p  ,&S , NUM_PROCESS );
    
   
    

    /*do this forever*/
    while(1);
    

    return 0;
}

