#include "./headers/scheduler.h"

extern unsigned int processCount;
extern unsigned int softBlockCount;
extern struct list_head readyQueue;
extern pcb_PTR currentProcess;
extern pcb_PTR blockedpcbs[SEMDEVLEN][2];
extern cpu_t ultimo;

void scheduler(){
    currentProcess = removeProcQ(&readyQueue);
    if(currentProcess != NULL){
        currentProcess->p_s.status = currentProcess->p_s.status | TEBITON;
        setTIMER(TIMESLICE);
        LDST(&currentProcess->p_s);
    }
    if(processCount == 1){
        HALT();
    }
    if(processCount > 1 && softBlockCount > 0){
        setSTATUS ((getSTATUS () | IECON | IMON) & ~TEBITON);
        WAIT();
    } 
}