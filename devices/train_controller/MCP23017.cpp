

#include "MCP23017.h"


MCP23017Controller::MCP23017Controller( byte i2c_address ) {
  this->i2c_address = i2c_address ;
}

void MCP23017Controller::attachDevice( MCP23017Device device , MCP23017GpioPin pin ) {
  this->device[pin] = device ;
  device.setPin(pin);
}

/**
 * Transmits the direction of each pin to the MCP23017 chip.
 */
void MCP23017Controller::transmitDevicePinDirection() {
  // Cycle through all the pins. Collecting the overall direction for
  // each pin in a 2-byte number. The lower byte is the A-bank, the
  // higher byte is the B-bank
  // Bit value of 0 : Output pin
  // Bit value of 1 : Input pin
  unsigned short total_direction_bit_values = 0x0000;
  for( pinId = MCP23017GpioPinId.A0 ; pinId < MCP23017_MAX_GPIO_PINS ; pinId +=1 ) {
    boolean isInputPin = this->device[pinId]->isInputDevice();
    unsigned short direction_bit_value = 0x0000 ; // Output direction is default
    if( isInputPin ) {
      direction_bit_value = 1 << pinId ;
    }
    total_direction_bit_values = total_direction_bit_values | direction_bit_value ;
  }

  byte bank_a_direction = (total_direction_bit_values & 0x00FF );
  byte bank_b_direction = (total_direction_bit_values & 0xFF00 ) >>8 ;

  // Transmit the direction for Bank A pins...
  Wire.beginTransmission(this->i2c_address);
  Wire.write(IODIRA);
  Wire.write(bank_a_direction);
  Wire.endTransmission();

  // Transmit the direction for Bank B pins...
  Wire.beginTransmission(this->i2c_address);
  Wire.write(IODIRB);
  Wire.write(bank_b_direction);
  Wire.endTransmission();
}

void MCP23017Controller::transmitPullupResistorSettings() {
  // Cycle through all the pins. Collecting the overall direction for
  // each pin in a 2-byte number. The lower byte is the A-bank, the
  // higher byte is the B-bank
  // Bit value of 0 : Turned off
  // Bit value of 1 : 100KOhm pull-up resistor turned on
  unsigned short total_pull_up_bit_values = 0x0000;
  for( pinId = MCP23017GpioPinId.A0 ; pinId < MCP23017_MAX_GPIO_PINS ; pinId +=1 ) {
    boolean isInputPin = this->device[pinId]->isInputDevice();
    unsigned short pull_up_bit_value = 0x0000 ;
    if( isInputPin ) {
      boolean isPullUpResistorRequired = this->device[pinId]->isPullUpResistorEnabled();
      if( isPullUpResistorRequired ) {
        pull_up_bit_value = 1 << pinId ;
      }
    }
    total_pull_up_bit_values = total_pull_up_bit_values | pull_up_bit_value ;
  }

  byte bank_a_pull_ups = (total_pull_up_bit_values & 0x00FF );
  byte bank_b_pull_ups = (total_pull_up_bit_values & 0xFF00 ) >>8 ;

  // Transmit the direction for Bank A pins...
  Wire.beginTransmission(this->i2c_address);
  Wire.write(GPPUA);
  Wire.write(bank_a_pull_ups);
  Wire.endTransmission();

  // Transmit the direction for Bank B pins...
  Wire.beginTransmission(this->i2c_address);
  Wire.write(GPPUB);
  Wire.write(bank_b_pull_ups);
  Wire.endTransmission();
}

void MCP23017Controller::transmitOutputs() {
  // Cycle through all the pins. Collecting the overall direction for
  // each pin in a 2-byte number. The lower byte is the A-bank, the
  // higher byte is the B-bank
  // Bit value of 0 : Turned off
  // Bit value of 1 : Turned on
  unsigned short total_output_bit_values = 0x0000;
  for( pinId = MCP23017GpioPinId.A0 ; pinId < MCP23017_MAX_GPIO_PINS ; pinId +=1 ) {
    boolean isOutputDevice = this->device[pinId]->isOutputDevice();
    unsigned short output_bit_value = 0x0000 ;
    if( isOutputDevice ) {
      boolean isOutputHigh = this->device[pinId]->isOutputHigh();
      if( isOutputHigh ) {
        output_bit_value = 1 << pinId ;
      }
    }
    total_output_bit_values = total_output_bit_values | output_bit_value ;
  }

  byte bank_a_outputs = (total_output_bit_values & 0x00FF );
  byte bank_b_outputs = (total_output_bit_values & 0xFF00 ) >>8 ;

  // Transmit the direction for Bank A pins...
  Wire.beginTransmission(this->i2c_address);
  Wire.write(GPIOA);
  Wire.write(bank_a_outputs);
  Wire.endTransmission();

  // Transmit the direction for Bank B pins...
  Wire.beginTransmission(this->i2c_address);
  Wire.write(GPIOB);
  Wire.write(bank_b_outputs);
  Wire.endTransmission();
}

void MCP23017Controller::setup() {
  this->transmitDevicePinDirection();
  this->transmitPullupResistorSettings();
  this->transmitOutputs();
}
