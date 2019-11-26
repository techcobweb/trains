
#include <Wire.h>
#include "MCP23017.h"
#include "Lamp.h"

Lamp planFrontMainlineGreen( "/plan/front/mainline/lamp/green" , true );
Lamp planFrontMainlineRed( "/plan/front/mainline/lamp/red" , true );
Lamp planFrontSidelineGreen( "/plan/front/sideline/lamp/green" , true );
Lamp planFrontSidelineRed( "/plan/front/sideline/lamp/red" , true );

MCP23017Controller planBoardController( 0x20 );

void setup() {
  // put your setup code here, to run once:
  planFrontMainlineGreen.attachToController( planBoardController , GPIO_PIN_B0 );
  planFrontMainlineRed.attachToController( planBoardController , GPIO_PIN_B1 );
  planFrontSidelineGreen.attachToController( planBoardController , GPIO_PIN_B2 );
  planFrontSidelineRed.attachToController( planBoardController , GPIO_PIN_B3 );

  planBoardController.setup();
}

void loop() {
  planFrontMainlineRed.setState( true );
  planBoardController.loop();
  delay(1000);
  
  planFrontMainlineRed.setState( false );
  planBoardController.loop();
  delay(1000);
}
