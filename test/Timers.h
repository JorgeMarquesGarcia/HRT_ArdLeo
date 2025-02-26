#define TIMER1_LED  13
#define TIMER3_LED  12
#include <Arduino.h>

volatile boolean timer1_out = HIGH;
volatile boolean timer3_out = HIGH;

// Timer1 interrupt
ISR (TIMER1_COMPA_vect) {
  digitalWrite(TIMER1_LED, timer1_out);
  timer1_out = !timer1_out;
}

// Timer3 interrupt
ISR (TIMER3_COMPA_vect) {
  digitalWrite(TIMER3_LED, timer3_out);
  timer3_out = !timer3_out;
}

void setup() {
  pinMode(TIMER1_LED, OUTPUT);
  pinMode(TIMER3_LED, OUTPUT);
  delay(3000);

  setupTimer();
  setTimer1(3);
  setTimer3(0.5);
}

void loop() {
}

void setupTimer() {
  cli();   ///Disable global interrupts 
  initTimer1();
  initTimer3();
  sei();  ///Enable global interrupts 
}

void initTimer1() {
    /*Inizialite two time counters control in 0 and one timer in 0. Set output compare register and set one of the time counters in one configuration*/
  TCCR1A = 0; ///Time counter control register 1A
  TCCR1B = 0; ///Time counter control register 1B
  TCNT1 = 0; /// Time counter 1
  OCR1A = 10000; ///Output compare Register 1A
  TCCR1B = bit(WGM12) | bit(CS12)| bit(CS10);  // WGM12 => CTC(Clear Timer on Compare Match), CS12 & CS10  => prescaler 1/1024
  TIMSK1 = bit(OCIE1A);                        // OCIE1A => Timer1 compare match A interrupt Timer Conter Interrupt Mask Register 
}

void initTimer3() {
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;
  OCR3A = 10000;
  TCCR3B = bit(WGM32) | bit(CS32);  // WGM32 => CTC(Clear Timer on Compare Match), CS32 => prescaler 1/256
  TIMSK3 = bit(OCIE3A);             // OCIE3A => Timer3 compare match A interrupt
}

void setTimer1(float _time) {
  long cnt = 16000000 / 1024 * _time;  // cnt = clk / prescaler * time(s)
  if(cnt > 65535) {
    cnt = 65535;         // "timer1 16bit counter over."
  }
  OCR1A = cnt;           // Output Compare Register Timer1A
  TIMSK1 = bit(OCIE1A);
}

void stopTimer1(){
    TIMSK1 = 0;
}

void setTimer3(float _time) {
  long cnt = 16000000 / 256 * _time;  // cnt = clk / prescaler * time(s)
  if(cnt > 65535) {
    cnt = 65535;        // "timer3 16bit counter over."
  }
  OCR3A = cnt;          // Output Compare Register Timer3A
  TIMSK3 = bit(OCIE3A);
}

void stopTimer3(){
    TIMSK3 = 0;
}

/*
|  CS12  |  CS11  |  CS10  |  Description                       |
|:-------|:------:|:------:|:----------------------------------:|
|   0    |    0   |    0   |  No clock source(timer stop)       |
|   0    |    0   |    1   |  clk / 1                           |
|   0    |    1   |    0   |  clk / 8                           |
|   0    |    1   |    1   |  clk / 64                          |
|   1    |    0   |    0   |  clk / 256                         |
|   1    |    0   |    1   |  clk / 1024                        |
|   1    |    1   |    0   |  External clock source no T1 pin.  |
|   1    |    1   |    1   |  External clock source no T1 pin.  |
*/