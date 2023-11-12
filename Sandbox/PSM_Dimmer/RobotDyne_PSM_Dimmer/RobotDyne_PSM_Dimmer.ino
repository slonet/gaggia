#define ZC 8
#define PSM_OUT 7

const int pulse_max = 100;
volatile int pulse_count = 0;
volatile int pulse_stop = 5;

int validate_pulse() {
  int i = 0;
  
  while(i < 5) {
    delayMicroseconds(50);
    
    if(!digitalRead(ZC)) {
      return 0;
    }

    i++;
  } 

  return 1;
}

void psm_pulse() {
  digitalWrite(PSM_OUT, HIGH);
  delay(8);
  digitalWrite(PSM_OUT, LOW);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ZC, INPUT);
  pinMode(PSM_OUT, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PSM_OUT, LOW);
}

void loop() {
  pulse_count = 0;

  while (pulse_count < pulse_max) {
    
    while (pulse_count < pulse_stop) {
        
        while(!digitalRead(ZC)) {}
        
        if(validate_pulse()) {
          psm_pulse();
        }

        pulse_count++;
    }

    while(!digitalRead(ZC)) {}

    if(validate_pulse()) {
          delay(8);
        }
    pulse_count++;
  }
}
