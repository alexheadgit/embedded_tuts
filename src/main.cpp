#include <Arduino.h>
#include <avr/wdt.h>

/*enum State {
  LED_ON, 
  LED_OFF
};
State current; 
const int LED_PIN = 8;
const int LED_DELAY = 1000;
unsigned long int lastChangeTime; 

boolean timeDiff(unsigned long start, int specifiedDelay){
  return (millis()-start >= specifiedDelay);
}

void setup() {
  current = LED_OFF; 
  pinMode(LED_PIN, OUTPUT);
  wdt_enable(WDTO_15MS);
}

void loop() {
  wdt_reset();
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
}*/
const int LED_PIN=8;
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

  count++;

  if (count >= 9) {  
    count = 0;
  }
}

