uint8_t _clk_pin = 21;
uint8_t _data_pin = 20;
uint8_t _pulse_time_us = 1; // defaut to a clock speed of 1 MHz
int32_t _raw_data = 0;

void setup() 
{
  Serial.begin(115200);

  pinMode(_data_pin, INPUT);
  pinMode(_clk_pin, OUTPUT);
  digitalWrite(_clk_pin, 0);
}

int set_clock_period(int clock_rate_khz)
{
  if (clock_rate_khz > 1000) 
    {
      clock_rate_khz = 1000;
    }

  int pulse_time_us = 1000 / (2 * clock_rate_khz); // The positive and negative clock pulses are 1/2 a cycle

  return pulse_time_us;
}


int32_t read_hx711(uint8_t pulse_time_us)
{
  uint8_t read_cycles = 24;
  uint8_t config_cycles = 1;
  int32_t data = 0;

  while (read_cycles > 0)
  {
    digitalWrite(_clk_pin, 1);
    delayMicroseconds(pulse_time_us);
    digitalWrite(_clk_pin, 0);

    data |= digitalRead(_data_pin) && 0x01;
    data = data << 1;

    //delayMicroseconds(pulse_time_us);
    read_cycles--;
  }

  data = data >> 1; // remove the final bit shift so the LSB is in the right place

  while (config_cycles > 0)
  {
    digitalWrite(_clk_pin, 1);
    //delayMicroseconds(pulse_time_us);
    digitalWrite(_clk_pin, 0);
    //delayMicroseconds(pulse_time_us);
    config_cycles--;
  }

  return data;
}

void loop()
{
  while(digitalRead(_data_pin)) {}
  _raw_data = read_hx711(_pulse_time_us);
  Serial.println(_raw_data);
}
