#include <umps3/umps/cp0.h>
#include "initial.c"

int intconst[7];
void interrupthandler();//funzioni abbastanza ovvie comunque sotto spiego cosa fanno
void IT_handler();
void NT_handler(int);//forse qui va qualcosa in input
void startinterrupt();
void endinterrupt();
void get_deviceinterrupt(int *);
int get_numdevice(int);
int get_status(int);
void set_status(char);


//DETERMINA IL TIPO DI INTERRUPT E ASSEGNA 
void interrupthandler(){
    startinterrupt();
    if(getCAUSE() && LOCALTIMERINT){//PLT INTERRUPT
        currentProcess->p_sib = EXCEPTION_STATE;
        currentProcess->p_time += tempopassato();
        insertProcQ(&readyQueue, currentProcess);
        currentProcess = NULL;
    } //lascia in questo ordine per la priorità
    else if(getCAUSE() && TIMERINTERRUPT)//INTERVAL TIMER INTERRUPT
        IT_handler();
    else
        NT_handler();
    endinterrupt();
}


//aggiorna il tempo di esecuzione del current process così da non dargli il tempo di esecuzione dell'interrupt
void startinterrupt(){
  //se il processo corrente non è nullo allora aggiorna il tempo
  //poi cambia lo status  
  if(currentProcess != NULL){
    currentProcess->p_time += tempopassato();
  }
  setSTATUS (getSTATUS() && ~TEBITON);
}

//fine interrupt e riprende il processo interrotto, se nullo chiama lo scheduler
void endinterrupt(){
    setSTATUS (getSTATUS() || TEBITON);
    STCK (ultimo);
    if (currentProcess != NULL)
        LDST (EXCEPTION_STATE);
    else
        scheduler ();
}


void NT_handler(int ip){
    int line, numero, mask;

}

void IT_handler(){
    while (headBlocked (&itSemaphore) != NULL){
        verhogen (&itSemaphore);
        softBlockedCount--;
        }
    LDIT (PSECOND);
}

int get_numdevice(int line){
    switch (line){
        case DEV1ON:
            devAddrBase = 0x10000054 + ((IntlineNo - 3) * 0x80) + (1 * 0x10);        
            break;
        case DEV2ON:
            devAddrBase = 0x10000054 + ((IntlineNo - 3) * 0x80) + (2 * 0x10);
            break;
        case DEV3ON:
            devAddrBase = 0x10000054 + ((IntlineNo - 3) * 0x80) + (3 * 0x10);       
            break;
        case DEV4ON:
            devAddrBase = 0x10000054 + ((IntlineNo - 3) * 0x80) + (4 * 0x10);       
            break;
        case DEV5ON:
            devAddrBase = 0x10000054 + ((IntlineNo - 3) * 0x80) + (5 * 0x10);       
            break;
        case DEV6ON:
            devAddrBase = 0x10000054 + ((IntlineNo - 3) * 0x80) + (6 * 0x10);       
            break;
        case DEV7ON:
            devAddrBase = 0x10000054 + ((IntlineNo - 3) * 0x80) + (7 * 0x10);       
            break;
        
    default:
        break;
    }
    status = get_status(devAddrBase);
    set_status(ACK);
    
}
