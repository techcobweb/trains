#include "Lamp.h"

Lamp::Lamp(char * initial_name ) {
  this->name = initial_name;
}

// Tell the lamp which controller it is connected to.
void Lamp::attachToController( MCP23017Controller * controller , MCP23017GpioPinId gpio_pin ) {
  controller->attachDevice( &(this->device) , gpio_pin );
}

void Lamp::setState( bool new_state ) {
  // Delegate the state to the device we have.
  this->device.setState( new_state );
}
