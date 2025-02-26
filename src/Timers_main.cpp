#include <Arduino.h>
#include <LeoTimers.h>

#define TIMER1_LED  7
#define TIMER3_LED  5
// put function declarations here:
volatile boolean timer1_out = HIGH;
volatile boolean timer3_out = HIGH;

Timers timer; 


ISR(TIMER1_COMPA_vect) {
  digitalWrite(TIMER1_LED, timer1_out);
  timer1_out = !timer1_out;
}

ISR(TIMER3_COMPA_vect) {
  digitalWrite(TIMER3_LED, timer3_out);
  timer3_out = !timer3_out;
}



void setup() {
  Serial.begin(9600);
  pinMode(TIMER1_LED, OUTPUT);
  pinMode(TIMER3_LED, OUTPUT);
  delay(3000);


  timer.initCounter(1, 1024);
  timer.initCounter(3, 1024);
  timer.setTimer(1, 5);
  timer.setTimer(3, 3);
}

void loop() {
}

// put function definitions here:

