#include "LeoTimers.h"
#include <Arduino.h>



#define F_CLOCK 16000000
#define PRESCALER_1 1
#define PRESCALER_8 8
#define PRESCALER_64 64
#define PRESCALER_256 256
#define PRESCALER_1024 1024



void Timers::initCounter(int counter_num, int prescaler) {
    cli();   ///Disable global interrupts
    switch (counter_num) {
        case 1:
            initCounter1(prescaler);
            break;
        case 3:
            initCounter3(prescaler);
            break;
        default:
            printf("Timer not available\n");
            break;
    }
    sei();  ///Enable global interrupts
}

void Timers::initCounter1(int prescaler){
    TCCR1A = 0; ///Time counter control register 1A start point
    TCCR1B = 0; ///Time counter control register 1B start point
    TCNT1 = 0; /// Time counter 1
    prescaler1 = prescaler;
    switch (prescaler) {
        case 1:
            TCCR1B = bit(WGM12) | bit(CS10);  // WGM12 => CTC(Clear Timer on Compare Match), CS10  => prescaler 1
            break;
        case 8:
            TCCR1B = bit(WGM12) | bit(CS11);  // WGM12 => CTC(Clear Timer on Compare Match), CS11  => prescaler 1/8
            break;
        case 64:
            TCCR1B = bit(WGM12) | bit(CS11) | bit(CS10);  // WGM12 => CTC(Clear Timer on Compare Match), CS11 & CS10  => prescaler 1/64
            break;
        case 256:
            TCCR1B = bit(WGM12) | bit(CS12);  // WGM12 => CTC(Clear Timer on Compare Match), CS12  => prescaler 1/256
            break;
        case 1024:
            TCCR1B = bit(WGM12) | bit(CS12)| bit(CS10);  // WGM12 => CTC(Clear Timer on Compare Match), CS12 & CS10  => prescaler 1/1024
            break;
        default:
            printf("Prescaler not available\n");
            break;
    }
    TIMSK1 = bit(OCIE1A);                        // OCIE1A => Timer1 compare match A interrupt Timer Conter Interrupt Mask Register 
}


void Timers::initCounter3(int prescaler){
    TCCR3A = 0; ///Time counter control register 1A start point
    TCCR3B = 0; ///Time counter control register 1B start point
    TCNT3 = 0; /// Time counter 1
    prescaler3 = prescaler;
    switch (prescaler) {
        case PRESCALER_1:
            TCCR3B = bit(WGM32) | bit(CS30);  // WGM12 => CTC(Clear Timer on Compare Match), CS10  => prescaler 1
            break;
        case PRESCALER_8:
            TCCR3B = bit(WGM32) | bit(CS31);  // WGM12 => CTC(Clear Timer on Compare Match), CS11  => prescaler 1/8
            break;
        case PRESCALER_64:
            TCCR3B = bit(WGM32) | bit(CS31) | bit(CS30);  // WGM12 => CTC(Clear Timer on Compare Match), CS11 & CS10  => prescaler 1/64
            break;
        case PRESCALER_256:
            TCCR3B = bit(WGM32) | bit(CS32);  // WGM12 => CTC(Clear Timer on Compare Match), CS12  => prescaler 1/256
            break;
        case PRESCALER_1024:
            TCCR3B = bit(WGM32) | bit(CS32)| bit(CS30);  // WGM12 => CTC(Clear Timer on Compare Match), CS12 & CS10  => prescaler 1/1024
            break;
        default:
            printf("Prescaler not available\n");
            break;
    }
    TIMSK3 =  bit(OCIE3A);                        // OCIE1A => Timer1 compare match A interrupt Timer Conter Interrupt Mask Register 
}

void Timers::setTimer(int timer_num, float _time_sec) {
    switch (timer_num) {
        case 1:
            setTimer1(_time_sec);
            break;
        case 2:
            TIMSK1 = bit(OCIE1A) | bit(OCIE1B);
            setTimer2(_time_sec);
            break;
        case 3:
            setTimer3(_time_sec);
            break;
        case 4:
            TIMSK3 =  bit(OCIE3A) | bit(OCIE3B);
            setTimer4(_time_sec);
            break;
        default:
            printf("Timer not available\n");
            break;
    }
}
void Timers::setTimer1(float _time_sec) {
    long cnt = F_CLOCK / prescaler1 * _time_sec;  // cnt = clk / prescaler * time(s)
    if(cnt > 65535) {
        cnt = 65535;         // "timer1 16bit counter over."
        printf("Timer1 16bit counter over\n");

    }
    OCR1A = cnt;           // Output Compare Register Timer1A
}

void Timers::setTimer2(float _time_sec) {
    long cnt = F_CLOCK / prescaler1 * _time_sec;  // cnt = clk / prescaler * time(s)
    if(cnt > 65535) {
        cnt = 65535;         // "timer1 16bit counter over."
        printf("Timer1 16bit counter over\n");

    }
    OCR1B = cnt;           // Output Compare Register Timer1A
}

void Timers::setTimer3(float _time_sec){
    long cnt = F_CLOCK / prescaler3 * _time_sec;  // cnt = clk / prescaler * time(s)
    if (cnt > 65535) {
        cnt = 65535;        // "timer3 16bit counter over."
        printf("Timer3 16bit counter over\n");
    }
    OCR3A = cnt;          // Output Compare Register Timer3A
}

void Timers::setTimer4(float _time_sec_sec){
    long cnt = F_CLOCK / prescaler3 * _time_sec_sec;  // cnt = clk / prescaler * time(s)
    if (cnt > 65535) {
        cnt = 65535;        // "timer3 16bit counter over."
        printf("Timer3 16bit counter over\n");
    }
    OCR3B = cnt;          // Output Compare Register Timer3A
}

void Timers::stopCounter(int counter){
    switch (counter) {
        case 1:
            stopCounter1();
            break;
        case 3:
            stopCounter3();
            break;
        default:
            printf("Counter not available\n");
            break;
    }
}

void Timers::stopCounter1(){
    TIMSK1 = 0;
}

void Timers::stopCounter3(){
    TIMSK3 = 0;
}