// Functions
bool matchesColour(uint8_t value, uint8_t colour);
void processSlider();
void setSliderButtons(uint8_t input);


// Limits for the analog outputs on the virtual gamepad,
// defined as uint16_t by the PicoGamepad library
const int16_t ANALOG_MIN = std::numeric_limits<int16_t>::min();
const int16_t ANALOG_MAX = std::numeric_limits<int16_t>::max();

// Values for the neck slider
uint8_t sliderMap[10][2] = {
  {120, 126}, // no touch
  {29, 35}, // green
  {79, 85}, // red
  {145, 159}, // yellow
  {186, 200}, // blue
  {252, 255}, // orange
  {54, 60}, // green + red
  {95, 109}, // red + yellow
  {161, 175}, // yellow + blue
  {210, 225} // blue + orange
};

// Some defines to make it easier to reference
#define START 0
#define END 1

#define OPEN 0

#define GREEN 1
#define RED 2
#define YELLOW 3
#define BLUE 4
#define ORANGE 5

#define GREEN_RED 6
#define RED_YELLOW 7
#define YELLOW_BLUE 8
#define BLUE_ORANGE 9
