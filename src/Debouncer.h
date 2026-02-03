#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <Arduino.h>

class Debouncer{
    private: 
        int pin;
        unsigned long debounceDelay;
        boolean lastButtonState;
        boolean buttonState;
        unsigned long lastDebounceTime;
        boolean lastRoseState;


    public: 

        Debouncer(int inputPin, unsigned long delay = 50);

        void begin();

        void update();

        boolean rose();
};

#endif
