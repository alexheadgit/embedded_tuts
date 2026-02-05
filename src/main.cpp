#include <Arduino.h>
#include <esp_task_wdt.h>


/*enum State {
  LED_ON, 
  LED_OFF
};
State current; 
const int LED_PIN = 14;
const int LED_DELAY = 1000;
unsigned long int lastChangeTime; 

boolean timeDiff(unsigned long start, int specifiedDelay){
  return (millis()-start >= specifiedDelay);
}

void setup() {
  current = LED_OFF; 
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  State old = current; 
  switch(current){
    case LED_OFF:
      digitalWrite(LED_PIN, LOW);
      if (timeDiff(lastChangeTime, LED_DELAY))
        current = LED_ON;
    break;

    case LED_ON:
      digitalWrite(LED_PIN, HIGH);
      if (timeDiff(lastChangeTime, LED_DELAY))
        current = LED_OFF;
    break;
  }
  if (old != current)
    lastChangeTime = millis();
  delay(100);
}
/*const int LED_PIN=14;
static int count = 0;

void setup(){
  pinMode(LED_PIN, OUTPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);

  TCCR1B |= (1 << WGM12);

  TIMSK1 |= (1 << OCIE1A);

  TIMSK1 |= (1 << OCIE1A);

  OCR1A = 1562.5; 

  interrupts();
}

void loop(){
 
}

ISR(TIMER1_COMPA_vect) {
  unsigned int ledOld = digitalRead(LED_PIN);
  if (count == 0) {
    digitalWrite(LED_PIN, ledOld ^ 1);   
  }
  else if (count == 2) {
    digitalWrite(LED_PIN, ledOld ^ 1);   
  }

  count--;

  if (count >= 9) {  
    count = 0;
  }
}

const int DELAY = 1000;
const int LED_PIN = 16;
const int SWITCH_PIN = 2;
unsigned long int lastChangeTime; 
static int count = 0;

enum State {
  LED_ON, 
  LED_OFF
};

State current;

boolean timeDiff(unsigned long start, int specifiedDelay){
  return (millis()-start >= specifiedDelay);
}

int getLEDDelay(){
  int delay = DELAY;
  if (digitalRead(SWITCH_PIN) == HIGH)
    delay /= 2;
  return delay;
}

void ledOff(){
  int delay = getLEDDelay();

  if (timeDiff(lastChangeTime, delay)){
    digitalWrite(LED_PIN, HIGH);  
    current = LED_ON;
  }
  count = 0;
}

void ledOn(){
  int delay = getLEDDelay();

  if (timeDiff(lastChangeTime, delay)){
    digitalWrite(LED_PIN, LOW);  
    current = LED_OFF;
  }
  count = 0;
}
void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  Serial.begin(115200); 
  current = LED_OFF; 
  lastChangeTime = millis(); 
}

void loop(){
  State old = current; 
  Serial.print("State: ");
  Serial.print(current);
  Serial.print(" Time: ");
  Serial.println(millis() - lastChangeTime);
  
  switch (current){
    case LED_OFF: 
      if(count >= 3)
        ledOff();
      count++;
      break;
    
    case LED_ON:
      if(count >= 3)
        ledOn();
      count++;
      break;
  }

  if (old != current){  
    lastChangeTime = millis();
  }
}

const int LED_PIN = 16;
const int SWITCH_PIN = 2;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);

  Serial.begin(115200);   // ← HERE
}

void loop() {
  int buttonState = digitalRead(SWITCH_PIN);
  Serial.println(buttonState);
  digitalWrite(LED_PIN, HIGH);

  if (buttonState == 0) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(200); // slow down printing
}

const int LED_PIN = 16;
const int SWITCH_PIN = 2;
const int DEBOUNCE_DELAY = 50; // 50ms debounce time

static int count = 0;

enum State {
  LED_ON, 
  LED_OFF
};

State current;
boolean lastButtonState = LOW;
boolean buttonState = LOW;
unsigned long lastDebounceTime = 0;

void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLDOWN);
  Serial.begin(115200);
  current = LED_OFF;
  digitalWrite(LED_PIN, LOW);
}

void loop(){
  boolean reading = digitalRead(SWITCH_PIN);

  if (reading != lastButtonState){
    lastDebounceTime = millis(); 
  }
  
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY){
    if (reading != buttonState){
      buttonState = reading;
      if (buttonState == HIGH){
        if (current == LED_OFF && count >= 3){
          current = LED_ON;
          digitalWrite(LED_PIN, HIGH);
          count = 0;
        } 
        else if(current == LED_ON && count >= 3) {
          current = LED_OFF;
          digitalWrite(LED_PIN, LOW);
          count = 0;
        }
        
        count++;
        Serial.print("Count: ");
        Serial.println(count);
      }
    }
  }
  
  lastButtonState = reading;
}

#include "Debouncer.h"

const int BLINK_DELAY = 1000;
const int LED_PIN = 16; 
const int SWITCH_PIN = 2;

enum State{
  BLINKING,
  ONE, 
  TWO, 
  THREE
};

State current; 
unsigned long LastBlinkTime = 0;
boolean ledState = LOW;


Debouncer button(SWITCH_PIN, 50);

void setup(){
  pinMode(LED_PIN, OUTPUT);
  button.begin();
  Serial.begin(115200);
  current = BLINKING;
  LastBlinkTime = millis(); 
  digitalWrite(LED_PIN, LOW);
}

void loop(){
  button.update();

  switch(current){
    case BLINKING:
      if(millis()-LastBlinkTime >= BLINK_DELAY){
          ledState = !ledState; 
          digitalWrite(LED_PIN, ledState);
          LastBlinkTime = millis();
      }
      break; 

    case ONE:
        if(millis()-LastBlinkTime >= BLINK_DELAY/2){
          ledState = !ledState; 
          digitalWrite(LED_PIN, ledState);
          LastBlinkTime = millis();
        }
        break; 
    case TWO:
        if(millis()-LastBlinkTime >= BLINK_DELAY/4){
          ledState = !ledState; 
          digitalWrite(LED_PIN, ledState);
          LastBlinkTime = millis();
        }
        break; 

    case THREE:
      if(millis()-LastBlinkTime >= BLINK_DELAY/8){
        ledState = !ledState; 
        digitalWrite(LED_PIN, ledState);
        LastBlinkTime = millis();
      }
      break; 
  }

  if (button.rose()){
    State oldState = current; 

    current = (State)((current + 1) % 4);

    if (oldState != current){
      LastBlinkTime = millis();
      ledState = LOW;
    }
  }
    
}*/

const int MIN_ADC = 0;
const int MAX_ADC = 4095;
const int MAX_DELAY_MS = 1500;
const int MIN_DELAY_MS = 200;

const int LED_PIN = 2;
const int RES_PIN = 34;

enum class LEDState{
  ON, 
  OFF
};

void setup(){
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

boolean timeDiff(unsigned long start, int specifiedDelay){
  return (millis()-start >= specifiedDelay);
}

unsigned long lastChangeTime; 
LEDState ledCheckUpdate(LEDState state, int delayValue){
  LEDState old = state; 
  if(timeDiff(lastChangeTime, delayValue)){
    if(state == LEDState::ON){
      state = LEDState::OFF;
    }else{ 
      state = LEDState::ON;
    }
  }

  if(state == LEDState::ON){
    digitalWrite(LED_PIN, HIGH);
  }else{
    digitalWrite(LED_PIN, LOW);
  }

  if(old != state){
    lastChangeTime = millis();
  }
  return state; 
}

LEDState current;

void loop(){
  int aRead = analogRead(RES_PIN);
  int delayValue = map(aRead, MIN_ADC, MAX_ADC, MIN_DELAY_MS, MAX_DELAY_MS);

  current = ledCheckUpdate(current, delayValue);
  Serial.println(aRead);
}



