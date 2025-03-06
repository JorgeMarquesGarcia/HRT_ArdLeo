#ifndef ATTACHINTERRUPT_H
#define ATTACHINTERRUPT_H
#endif

#include <Arduino.h>


class AttachInterrupt {
    public:
        void attachInterrupt(int interrupt_num, void (*task)(void), int prescaler, float time);
        void detachInterrupt(int interrupt_num);
        


    private: 
        void Interrupt1(void (*task)(void));
        void Interrupt2(void (*task)(void));
        void Interrupt3(void (*task)(void));
        void Interrupt4(void (*task)(void));
        void Interrupt5(void (*task)(void));
        void Interrupt6(void (*task)(void));
        void configureTimer(int timer_num, int prescaler, float time);
};