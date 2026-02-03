#include "Debouncer.h"

Debouncer::Debouncer(int inputPin, unsigned long delay){
    pin = inputPin; 
    debounceDelay = delay; 
    lastButtonState = LOW;
    buttonState = LOW; 
    lastDebounceTime = 0;
    lastRoseState = 0;

}

void Debouncer::begin() {
    pinMode(pin, INPUT_PULLDOWN);
}

void Debouncer::update() {
  boolean reading = digitalRead(pin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
    }
  }
  
  lastButtonState = reading;
}

boolean Debouncer::rose() {
  boolean currentState = buttonState;
  boolean result = (currentState == HIGH && lastRoseState == LOW);
  lastRoseState = currentState;
  return result;
}