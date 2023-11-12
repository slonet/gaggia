#define ZC 2
#define PSM_OUT 7

volatile int pulse_count = 0;
const int half_cycle_us = 8000;
const int psm_delay_us = 250;

void PSM_ISR() {
    
    if((int) random(2)) {
      delayMicroseconds(psm_delay_us);
      digitalWrite(PSM_OUT, HIGH);
      delayMicroseconds(half_cycle_us);
      digitalWrite(PSM_OUT, LOW);
    }

}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ZC, INPUT);
  pinMode(PSM_OUT, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ZC), PSM_ISR, RISING);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PSM_OUT, LOW);

}

void loop() {}