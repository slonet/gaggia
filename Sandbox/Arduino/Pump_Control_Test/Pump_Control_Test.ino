#define ZC 2
#define PSM_OUT 7
#define PRES_IN A0

const int half_cycle_us = 8000;
const int psm_delay_us = 250;
const float target_pres_mpa = 1.3;

void psm_pulse() {
  while(digitalRead(ZC)) {} // Wait for ZC to go low if we're in a zero crossing
  
  delayMicroseconds(100);

  while(!digitalRead(ZC)) {} // Wait for ZC to go high again

  delayMicroseconds(psm_delay_us);
  digitalWrite(PSM_OUT, HIGH);
  delayMicroseconds(half_cycle_us);
  digitalWrite(PSM_OUT, LOW);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ZC, INPUT);
  pinMode(PSM_OUT, OUTPUT);
  
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PSM_OUT, LOW);

  Serial.begin(115200);

}


void loop() {
  int pres_value = analogRead(A0);

  float pres_mpa = (4 * pres_value / 1023.0);
  Serial.println(pres_mpa);

  if (pres_mpa < target_pres_mpa) {
    digitalWrite(LED_BUILTIN, HIGH);
    psm_pulse();
  }

  delay(10);
  digitalWrite(LED_BUILTIN, LOW);
}