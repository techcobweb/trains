#ifndef LAMP_H_
#define LAMP_H_

/*
 * A Lamp represents a single LED on a single pin.
 */

class Lamp : public MCP23017Device {
  public:
    Lamp( char * initial_name , MCP23017GpioPin initial_pin , boolean initial_state );
}

#endif
