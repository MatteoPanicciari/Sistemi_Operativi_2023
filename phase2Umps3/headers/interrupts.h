#ifndef INTERRUPTS_H_INCLUDED
#define INTERRUPTS_H_INCLUDED

#include "./initial.h"

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

#endif