/*
LOGIC ANALYZER SETUP
SCK   CH0
MISO  CH1
CS    CH2
*/
#include <SPI.h>

// MAX6675 constants
const int SPI_CS_PIN = 10;
const int TEMP_LSB = 3;
const int TEMP_MASK = 0x7FF8;
const int SPI_CLK = 1000000;
const float TEMP_MAX = 1023.75;

// PSM controller constants
const int ZC = 2;
const int PSM_OUT = 7;
const int half_cycle_us = 8000;
const int psm_delay_us = 250;

// Temperature control constants
const float target_temp = 50.0;

// Global Variables for loop timing & heater control
int volatile temp_meas_cycles = 31;
bool volatile heater_pulse = 0;
unsigned long volatile max6675_data = 0;

void PSM_PULSE_HEATER() {
  delayMicroseconds(psm_delay_us);
  digitalWrite(PSM_OUT, HIGH);
  delayMicroseconds(half_cycle_us);
  digitalWrite(PSM_OUT, LOW);
}

unsigned long max6675_read() {
  unsigned long reg_value = 0;

  SPI.beginTransaction(SPISettings(SPI_CLK, MSBFIRST, SPI_MODE1));
  digitalWrite(SPI_CS_PIN, LOW);

  reg_value |= SPI.transfer(0x00) << 8;
  reg_value |= SPI.transfer(0x00);

  digitalWrite(SPI_CS_PIN, HIGH);
  SPI.endTransaction();

  return reg_value;
}

float convert_temp(unsigned int reg_value) {
  int temp_data = (reg_value & TEMP_MASK) >> TEMP_LSB;
  float temp_value = TEMP_MAX * (temp_data / 4095.0);

  return temp_value;
}

void ZC_ISR() {
  if (heater_pulse) {
    PSM_PULSE_HEATER();
    heater_pulse = 0;
  }

  if (temp_meas_cycles <= 0) {
    max6675_data = max6675_read();
    temp_meas_cycles = 31;
  }

  temp_meas_cycles--;
}

void setup() {
  Serial.begin(115200);
  
  // max6675 setup
  SPI.begin();
  pinMode(SPI_CS_PIN, OUTPUT);

  // heater setup
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ZC, INPUT);
  pinMode(PSM_OUT, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PSM_OUT, LOW);

  attachInterrupt(digitalPinToInterrupt(ZC), ZC_ISR, RISING);
  
  delay(500);

}

void loop() {
  float current_temp = convert_temp(max6675_data);

  if (current_temp < target_temp) {
    heater_pulse = 1;
  }

  Serial.println(current_temp);

  delay(1);  
}
