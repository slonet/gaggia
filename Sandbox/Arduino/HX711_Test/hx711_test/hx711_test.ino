#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);

}

/*
Waits for the HX711 to complete a measurement
Sends clock pulses to the HX711 at the specified rate. 
Sends the correct number of clock pulses for the specified mode

mode: int 0,1,2
  0 = Input A, Gain = 128
  1 = Input B, Gain = 32
  2 = Input A, Gain = 64

clock_rate: int 10 - 500
  clock rate in kHz
*/
void read_load_cell(mode, clock_rate)

void loop() {

}
