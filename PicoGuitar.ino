#include <PicoGamepad.h>
#include <WiiChuck.h>

Accessory guitar;
PicoGamepad gamepad;

// limits for the analog outputs on the virtual gamepad, used for the map function. Do not change.
const int ANALOG_MIN = -32767;
const int ANALOG_MAX = 32767;

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

  gamepad.SetZ(map(guitar.values[0], 0, 255, ANALOG_MIN, ANALOG_MAX));  // whammy
  gamepad.SetButton(1, guitar.values[10]);                              // green
  gamepad.SetButton(2, guitar.values[11]);                              // red
  gamepad.SetButton(0, guitar.values[12]);                              // yellow
  gamepad.SetButton(3, guitar.values[13]);                              // blue
  gamepad.SetButton(4, guitar.values[14]);                              // orange
  gamepad.SetButton(5, guitar.values[9]);                               // pedal
  gamepad.SetRz(map(guitar.values[7], 0, 255, ANALOG_MIN, ANALOG_MAX)); // strum
//gamepad.SetRx(map(guitar.values[3], 0, 255, ANALOG_MIN, ANALOG_MAX)); // neck slider - WIP, not yet supported by WiiChuck
  gamepad.SetX(map(guitar.values[1],0,255,ANALOG_MIN,ANALOG_MAX));      // joystick X axis
  gamepad.SetY(map(guitar.values[2],0,255,ANALOG_MIN,ANALOG_MAX));      // joystick Y axis
  gamepad.SetButton(8, guitar.values[5]);                               // star power
  gamepad.SetButton(9, guitar.values[6]);                               // plus buttons

  gamepad.send_update(); // send inputs to USB gamepad

}
