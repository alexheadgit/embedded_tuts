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
const int LED_PIN = 4;
const int SWITCH_PIN = 2;
unsigned long int lastChangeTime; 

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
  digitalWrite(LED_PIN, LOW);
  int delay = getLEDDelay();

  if (timeDiff(lastChangeTime, delay))
    current = LED_ON;
}

void ledOn(){
  digitalWrite(LED_PIN, HIGH);
  int delay = getLEDDelay();

  if (timeDiff(lastChangeTime, delay))
    current = LED_OFF;
}

void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  current = LED_OFF; 
  lastChangeTime = 0;
}

void loop(){
  State old = current; 
  switch (current){
    case LED_OFF: 
      ledOff();
      break;
    
      case LED_ON:
        ledOn();
        break;
  }

  if (old!=current){
    lastChangeTime = millis();
  }
}*/

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



