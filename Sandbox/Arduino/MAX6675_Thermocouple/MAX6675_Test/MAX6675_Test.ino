/*
LOGIC ANALYZER SETUP
SCK   CH0
MISO  CH1
CS    CH2
*/

#include <SPI.h>

#define SPI_CS_PIN 53
#define TEMP_LSB 3
#define TEMP_MASK 0x7FF8
#define SPI_CLK 1000000

const float TEMP_MAX = 1023.75;


void setup() {
  Serial.begin(115200);
  SPI.begin();
  pinMode(SPI_CS_PIN, OUTPUT);
  delay(500);

}

// Read the full 16 bit register back from the MAX6675
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

// Extract the temperature data from the full 16 bit register and convert to Deg C
float convert_temp(unsigned int reg_value) {
  int temp_data = (reg_value & TEMP_MASK) >> TEMP_LSB;
  float temp_value = TEMP_MAX * (temp_data / 4095.0);

  return temp_value;
}

void loop() {
  unsigned long reg_value = max6675_read();
  double temp_value = convert_temp(reg_value);
  Serial.println(temp_value);  
  delay(250); //Maximum conversion time is 220ms, this allows 30ms margin
}
