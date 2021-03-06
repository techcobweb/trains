

#ifndef MCP23017_H_
#define MCP23017_H_

/*
                                    +---------+
                          GPIO B0 --|         |-- A7 GPIO
                          GPIO B1 --|         |-- A6 GPIO
                          GPIO B2 --|   MCP   |-- A5 GPIO
                          GPIO B3 --|  23017  |-- A4 GPIO
                          GPIO B4 --|         |-- A3 GPIO
                          GPIO B5 --|         |-- A2 GPIO
                          GPIO B6 --|         |-- A1 GPIO
                          GPIO B7 --|         |-- A0 GPIO
          +5v---------------- VDD --|         |-- INTA
          Gnd---------------- VSS --|         |-- INTB
                               NC --|         |-- RESET --------------+5v
                +------------ SCL --|         |-- ADDR_2_MSB
                |   +-------- SDA --|         |-- ADDR_1
                |   |          NC --|         |-- ADDR_0_LSB
                |   |               +---------+
                |   |
+5v ----4.7K ---+   +--- 4.7K pull-up resistor ---- +5v
      pull-up   |   |
                |   +-- A5 Arduino pin
                |
                +------ A4 Arduino Pin


* All the GPIO ports have 100K pull-up resistors

*/

#include "Arduino.h"

#define MCP23017_MAX_GPIO_PINS 16

/*
 * Registers used in the MCP23017
 */
typedef enum MCP23017Register {
  IODIRA   = 0x00, // Direction of pins on GPIO bank A  0=output, 1=input
  IODIRB   = 0x01, // Direction of pins on GPIO bank B  0=output, 1=input
  IPOLA    = 0x02,
  IPOLB    = 0x03,
  GPINTENA = 0x04,
  GPINTENB = 0x05,
  DEFVALA  = 0x06,
  DEFVALB  = 0x07,
  INTCONA  = 0x08,
  INTCONB  = 0x09,
  IOCONA   = 0x0A,
  IOCONB   = 0x0B,
  GPPUA    = 0x0C, // Pull-up resistor on pins in GPIO bank A. 0=disabled. 1=enabled.
  GPPUB    = 0x0D,  // Pull-up resistor on pins in GPIO bank B. 0=disabled. 1=enabled.
  INTFA    = 0x0E,
  INTFB    = 0x0F,
  INTCAPA  = 0x10,
  INTCAPB  = 0x11,
  GPIOA    = 0x12,
  GPIOB    = 0x13,
  OLATA    = 0x14,
  OLATB    = 0x15
};

/*
 * How we identify pins across the API.
 */
typedef enum MCP23017GpioPinId {
GPIO_PIN_A0 = 0x00,
GPIO_PIN_A1 = 0x01,
GPIO_PIN_A2 = 0x02,
GPIO_PIN_A3 = 0x03,
GPIO_PIN_A4 = 0x04,
GPIO_PIN_A5 = 0x05,
GPIO_PIN_A6 = 0x06,
GPIO_PIN_A7 = 0x07,
GPIO_PIN_B0 = 0x08,
GPIO_PIN_B1 = 0x09,
GPIO_PIN_B2 = 0x0A,
GPIO_PIN_B3 = 0x0B,
GPIO_PIN_B4 = 0x0C,
GPIO_PIN_B5 = 0x0D,
GPIO_PIN_B6 = 0x0E,
GPIO_PIN_B7 = 0x0F
};


// Forward reference so we can have circular cross-referencing.
class MCP23017Controller ;

class MCP23017Device {
  public:
    void setPin( MCP23017GpioPinId new_pin );
    void setController( MCP23017Controller * controller );
    MCP23017Controller * getController();
    
    bool isOutputDevice();
    bool isInputDevice();
    void setDeviceDirection(boolean is_output_device);
    
    bool isPullUpResistorEnabled();
    bool setPullUpResistor( bool new_state );
    
    bool isOutputHigh();
    bool isStateLow(); 
    void setState( boolean new_state );


  private:
    bool is_output_device = true;
    MCP23017GpioPinId pin ;
    MCP23017Controller * controller;
    bool is_pullup_resistor_enabled = true ;
    bool current_state = false;
};

class MCP23017Controller {
  public:
    MCP23017Controller( byte i2c_address );

    // Do things to set the I2C bus device up at the start.
    void setup();

    // Attach a device to a pin.
    void attachDevice( MCP23017Device * device , MCP23017GpioPinId pin );

    // Make sure the outputs have transmitted their current in-memory state.
    void loop();

  private:
    // An array of pointers to devices.
    MCP23017Device * device[MCP23017_MAX_GPIO_PINS];
    
    // The i2c address set by the jumpers.
    byte i2c_address ;

    // Tell the board whether each pin is for input or output
    void transmitDevicePinDirection();
    
    // Tell the board whether an input pin needs a pull-up resistor.
    void transmitPullupResistorSettings();
    
    // Tell the board what the state of each output pin should be.
    void transmitOutputs();
};



#endif
