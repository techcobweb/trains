#ifndef LAMP_H_
#define LAMP_H_

/*
 * A Lamp represents a single LED on a single pin.
 */

#include "MCP23017.h"


/*
 * A Lamp. It's a single led controlled from one pin on a controller.
 * 
 * It has a state of ON or OFF. (true or false).
 *
 */
class Lamp  {
  public:
    // Give the lamp a name and an initial state.
    Lamp( char * initial_name );
    
    // Tell the lamp which controller it is connected to.
    void attachToController( MCP23017Controller * controller , MCP23017GpioPinId gpio_pin );
    
    // Sets the state of the lamp to on or off 
    void setState( bool new_state );
    
  private:
    // The name of this lamp
    char * name;
    
    // The device we connect up to a controller on a pin.
    MCP23017Device device;
};

#endif
