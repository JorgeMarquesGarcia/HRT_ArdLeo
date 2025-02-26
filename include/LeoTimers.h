#ifndef TIMERS_H
#define TIMERS_H
#if !(defined(ARDUINO_AVR_LEONARDO) && defined(__AVR_ATmega32U4__))
  #error This code is designed to run on Arduino Leonardo boards with ATmega32U4! Please check your Tools->Board setting.
#endif

#include <Arduino.h>


class Timers {
    public: 
        void initCounter(int counter_num, int prescaler);
        void setTimer(int timer, float _time);
        void stopCounter(int counter);


    private: 
        void initCounter1(int prescaler);
        void initCounter3(int prescaler);
        void setTimer1(float _time);
        void setTimer2(float _time);
        void setTimer3(float _time);
        void setTimer4(float _time);
        void stopCounter1();
        void stopCounter3();
        

        int prescaler1;
        int prescaler3;
};



#endif // TIMERS_H<