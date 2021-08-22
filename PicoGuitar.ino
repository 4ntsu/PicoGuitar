#include <PicoGamepad.h>
#include <WiiChuck.h>

Accessory guitar;
PicoGamepad gamepad;

// limits for the analog outputs on the virtual gamepad, used for the map function. Do not change.
const int ANALOG_MIN = -32767;
const int ANALOG_MAX = 32767;

// min/max whammy values as returned by WiiChuck, adjust as needed
const int WHAMMY_MIN = 16;
const int WHAMMY_MAX = 29;

// min/max X/Y joystick axis values as returned by WiiChuck, adjust as needed
const int STICK_X_MIN = 5;
const int STICK_X_MAX = 62;
const int STICK_Y_MIN = 5;
const int STICK_Y_MAX = 62;

void setup() {  

  guitar.begin();
  guitar.type = GuitarHeroController;

}

void loop() {
  
  guitar.readData(); // read inputs from guitar

  gamepad.SetZ(map(guitar.getWhammyBar(), WHAMMY_MIN, WHAMMY_MAX, 0, ANALOG_MAX));            // whammy
  gamepad.SetButton(1, guitar.getGreenButton());                                              // green
  gamepad.SetButton(2, guitar.getRedButton());                                                // red
  gamepad.SetButton(0, guitar.getYellowButton());                                             // yellow
  gamepad.SetButton(3, guitar.getBlueButton());                                               // blue
  gamepad.SetButton(4, guitar.getOrangeButton());                                             // orange
  gamepad.SetRz(guitar.getStrumUp()?ANALOG_MIN:(guitar.getStrumDown()?ANALOG_MAX:0));         // strum
  gamepad.SetX(map(guitar.getStickXGuitar(),STICK_X_MIN,STICK_X_MAX,ANALOG_MIN,ANALOG_MAX));  // joystick X axis
  gamepad.SetY(map(guitar.getStickYGuitar(),STICK_Y_MIN,STICK_Y_MAX,ANALOG_MAX,ANALOG_MIN));  // joystick Y axis
  gamepad.SetButton(8, guitar.getMinusButtonGuitar());                                        // star power
  gamepad.SetButton(9, guitar.getPlusButtonGuitar());                                         // plus buttons
  
  gamepad.send_update(); // send inputs to USB gamepad

}
