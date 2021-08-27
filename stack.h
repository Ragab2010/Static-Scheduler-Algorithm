/* 
 * File:   stack.h
 * Author: ragab
 *
 * Created on May 10, 2018, 8:41 PM
 */

#ifndef STACK_H
#define	STACK_H

#define STACK_SIZE 3


typedef struct  process{
	unsigned char  id;
	unsigned char  cap;
	unsigned char  deadline;
    void (*pFun)();
	unsigned char flage;
}PROCESS;

typedef struct stack{
    PROCESS  proces[STACK_SIZE];
     int top;
    
}STACK;

/*we make STACK S  as globle  to can access it by interrupt ISR*/
//STACK s;

#define INITIALIZESTACK(Ps) {(Ps)->top = -1;}
#define INITIALIZESTACKK(ss) {(ss).top = -1;}

#define PUSH(ss,pp,i) {(ss)->proces[++((ss)->top)].id = pp[i].id; \
                       (ss)->proces[((ss)->top)].cap = pp[i].cap;\
                       (ss)->proces[((ss)->top)].deadline = pp[i].deadline;\
                       (ss)->proces[((ss)->top)].pFun = pp[i].pFun;\
                       (ss)->proces[((ss)->top)].flage = pp[i].flage;} 

#define POP(ss,pp,i) {pp[i].id = (ss)->proces[((ss)->top)].id ;\
                      pp[i].cap = (ss)->proces[((ss)->top)].cap;\
                      pp[i].deadline = (ss)->proces[((ss)->top)].deadline ;\
                      pp[i].pFun = (ss)->proces[((ss)->top)].pFun;\
                      pp[i].flage = (ss)->proces[((ss)->top)--].flage;} 


#define POPP(ss) {(ss)->top--};

#endif	/* STACK_H */

