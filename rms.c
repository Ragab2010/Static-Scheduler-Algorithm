/* 
 * File:   rms.c
 * Author: ragab
 *
 * Created on May 10, 2018, 8:39 PM
 */

#include "rms.h"

/* counter  for count  number of overflow every 20 millisecond*/
unsigned char  p1=0,p2=0;
/* top is the important variable that's specify which process will work */
unsigned char top=0;
/*
 * gloable pointer to process  which will used to  interrupt  the lower priority process execution and
 *  call the  highest priority interrupted processor 
 */
PROCESS *pISR;
/*
 * gloable pointer to stack  which will used to  push the process that's interrupted by highest 
 */
STACK *pSTACK;
 
 
 void interrupt ISR(){
    TMR1L=224;
    TMR1H=177;
    if(PIR1bits.TMR1IF == 1 ){
        PIR1bits.TMR1IF =0;
        p1++;
        p2++;

    }
    /*
    /*if p1   ==  1  and p2 == 2 this mean that's 2 overflow happen (40 millisecond) 
     *call the highest priority process--->  process1 and then process2 execute before process3
     */
    if((p1 == 1) && (p2 == 2) ){
        p1=0;p2=0;
        pISR[0].pFun();
        pISR[1].pFun();
    }
    /*to determine the period*/
    /*if p1   ==  1 this mean that's 1 overflow happen (20 millisecond) 
     *call the highest priority process--->  process1
     */

    else if(p1 == 1){
        p1=0;
        //s.top=2;
        pISR[0].flage=1;
        pISR[0].pFun();

    }
    /*if p2  ==  2 this mean that's 2 overflow happen (40 millisecond) 
     *call the second  highest priority process ---> process2
     */
    else if(p2 == 2){
        p2=0;
        pISR[1].flage=1;
        pISR[1].pFun();
    }
    
    /*
     *if the period of the last process(p2) is done so execute again from p1 
     */
    if(p1==5){
        p1=0;
        pSTACK->top=2;
        pSTACK->proces[0].flage=1;
        pSTACK->proces[1].flage=1;
        pSTACK->proces[2].flage=1;
        
    }
    /*
     * in normal the process3  (the lowest priority process) will execute if the others process done
     */
    

    
 }


/*initialize  timer1 to overflow every 20 millisecond */
void timer1_init(){
    TMR1L=224;
    TMR1H=177;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.TMR1IE=1;
    T1CONbits.TMR1ON=1;
    PIR1bits.TMR1IF=0;
      ei(); 
}

/*for sort processes by deadline */
unsigned char LCM(PROCESS *p , unsigned char num_process){
	PROCESS *max_per=p , temp;
	unsigned char i ,j, index=0;
	for(i=0 ; i<num_process ; i++){
		max_per = (p+i);
		for(j=i ; j<num_process ; j++){
			if((p[j].deadline) < (max_per->deadline) ){
				max_per =(p+j);
				index=j;
					temp.cap=p[index].cap;
					temp.deadline=p[index].deadline;
					temp.flage=p[index].flage;
					temp.id=p[index].id;
					temp.pFun=p[index].pFun;

					p[index].cap=p[i].cap;
					p[index].deadline=p[i].deadline;
					p[index].flage=p[i].flage;
					p[index].id=p[i].id;
					p[index].pFun=p[i].pFun;

					p[i].cap=temp.cap;
					p[i].deadline=temp.deadline;
					p[i].flage=temp.flage;
					p[i].id=temp.id;
					p[i].pFun=temp.pFun;
			}

		}

	}
	return 1;
}

/*the scheduler that's specify which process will execute  */
unsigned char RMS_Scheduler(PROCESS *p ,STACK *ps,unsigned char num_process){
	unsigned char i;
    /*this is the execute state  which will execute the process that's pop from stack */
    PROCESS excute_state[1];
    pISR =p;//here we initialize  pISR (the global pointer  )  to the processes array ... to can interrupt  process by ISR
    pSTACK =ps;//here we initialize pSTACK(the global pointer  ) to the stack  to can push or pop from interrupt
	LCM(p ,  num_process);//sort the processes by per
    /*here we push the processes from lowest priority to the highest priority */
    for(i=0 ; i < num_process ; i++){
         PUSH(ps, p  , i);
    }
  timer1_init();
    for(;;){
        /*here pop the highest priority  from stack to execute state */
       POP(ps, excute_state  , i)
       if(excute_state[0].flage == 1){
           excute_state[0].pFun();
       }
    }// infinite loop

	return 1 ;
}

