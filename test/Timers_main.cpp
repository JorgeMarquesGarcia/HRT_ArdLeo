#define TIMER1_LED  7
#define TIMER3_LED  5
#include <Arduino.h>
#include <LeoTimers.h>
#include <AttachInterrupt.h>

volatile boolean timer1_out = HIGH;
volatile boolean timer3_out = HIGH;
AttachInterrupt Interrupts;

void ledBlink(int led, volatile bool &time);

void setup() {
  pinMode(TIMER1_LED, OUTPUT);
  pinMode(TIMER3_LED, OUTPUT);
  delay(3000);

  //Interrupts.configureTimer(1, 1024, 3);
  //Interrupts.configureTimer(2, 256, 5);

  Interrupts.attachInterrupt(2, []() { ledBlink(TIMER1_LED, timer1_out); }, 1024, 3);
  Interrupts.attachInterrupt(1, []() { ledBlink(TIMER3_LED, timer3_out); }, 256, 5);

}

void loop() {
}



void ledBlink(int led, volatile bool &time) {
  digitalWrite(led, time);
  time = !time; // Cambia el valor de time
}