#include "AttachInterrupt.h"
#include <Arduino.h>
#include "LeoTimers.h"

Timers timer;




// # TASK1 TIMER1_COMPA_vect
// # TASK2 TIMER1_COMPB_vect
// # TASK3 TIMER1_COMPC_vect
// # TASK4 TIMER3_COMPA_vect
// # TASK5 TIMER3_COMPB_vect
// # TASK6 TIMER3_COMPC_vect

void (*isr1Function)(void);
void (*isr2Function)(void);
void (*isr3Function)(void);
void (*isr4Function)(void);
void (*isr5Function)(void);
void (*isr6Function)(void);
void Interrupt1(void (*task)(void));
void Interrupt2(void (*task)(void));
void Interrupt3(void (*task)(void));
void Interrupt4(void (*task)(void));
void Interrupt5(void (*task)(void));
void Interrupt6(void (*task)(void));
ISR(TIMER1_COMPA_vect) {
    if (isr1Function) isr1Function();
}

ISR(TIMER1_COMPB_vect) {
    if (isr2Function) isr2Function();
}

ISR(TIMER1_COMPC_vect) {
    if (isr3Function) isr3Function();
}

ISR(TIMER3_COMPA_vect) {
    if (isr4Function) isr4Function();
}

ISR(TIMER3_COMPB_vect) {
    if (isr5Function) isr5Function();
}

ISR(TIMER3_COMPC_vect) {
    if (isr6Function) isr6Function();
}


void AttachInterrupt::attachInterrupt(int interrupt_num, void (*task)(), int prescaler, float time) {
    configureTimer(interrupt_num, prescaler, time);
    switch (interrupt_num) {
        case 1:
            Interrupt1(task);
            break;
        case 2:
            Interrupt2(task);
            break;
        case 3:
            Interrupt3(task);
            break;
        case 4:
            Interrupt4(task);
            break;
        case 5:
            Interrupt5(task);
            break;
        case 6:
            Interrupt6(task);
            break;
        default:
            printf("Numbers of interrups exceeded\n");
            break;
    }
}


void AttachInterrupt::Interrupt1(void (*task)(void)) {
    isr1Function = task;
}

void AttachInterrupt::Interrupt2(void (*task)(void)) {
    isr2Function = task;
}

void AttachInterrupt::Interrupt3(void (*task)(void)) {
    isr3Function = task;
}

void AttachInterrupt::Interrupt4(void (*task)(void)) {
    isr4Function = task;
}

void AttachInterrupt::Interrupt5(void (*task)(void)) {
    isr5Function = task;
}

void AttachInterrupt::Interrupt6(void (*task)(void)) {
    isr6Function = task;
}

void AttachInterrupt::detachInterrupt(int interrupt_num) {
    switch (interrupt_num) {
        case 0:
            detachInterrupt(0);
            break;
        case 1:
            detachInterrupt(1);
            break;
        case 2:
            detachInterrupt(2);
            break;
        case 3:
            detachInterrupt(3);
            break;
        case 4:
            detachInterrupt(4);
            break;
        case 5:
            detachInterrupt(5);
            break;
        case 6:
            detachInterrupt(6);
            break;
        case 7:
            detachInterrupt(7);
            break;
        default:
            printf("Interrupt not available\n");
            break;
    }
}


void AttachInterrupt::configureTimer(int timer_num, int prescaler, float time) {
    if(timer_num == 1 || timer_num == 2 || timer_num == 3){
        timer.initCounter(1, prescaler);
    } else if(timer_num == 4 || timer_num == 5 || timer_num == 6){
        timer.initCounter(3, prescaler);
    }
    timer.setTimer(timer_num, time);
}

