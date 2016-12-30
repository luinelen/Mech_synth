#include <Adafruit_NeoPixel.h>

int timeOn = 100;
int timeOff = 500;

/* How many shift register chips are daisy-chained.
*/
#define NUMBER_OF_SHIFT_CHIPS   1

/* Width of data (how many ext lines).
*/
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC   5

/* Optional delay between shift register reads.
*/
#define POLL_DELAY_MSEC   1

int ploadPin        = 5;  // Connects to Parallel load pin the 165
int clockEnablePin  = 2;  // Connects to Clock Enable pin the 165
int dataPin         = 4; // Connects to the Q7 pin the 165
int clockPin        = 3; // Connects to the Clock pin the 165

unsigned int pinValues;

#define PIXEL_PIN 1

#define BUTTON_PIN 0

#define POT_PIN 0

int activeStep = 0;

int currentStep = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

/* This function is essentially a "shift-in" routine reading the
 * serial Data from the shift register chips and representing
 * the state of those pins in an unsigned integer (or long).
*/
unsigned int read_shift_regs()
{
  long bitVal;
  unsigned int bytesVal = 0;

  /* Trigger a parallel Load to latch the state of the data lines,
  */
  digitalWrite(clockEnablePin, HIGH);
  digitalWrite(ploadPin, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC);
  digitalWrite(ploadPin, HIGH);
  digitalWrite(clockEnablePin, LOW);

  /* Loop to read each bit value from the serial out line
   * of the SN74HC165N.
  */
  for(int i = 0; i < DATA_WIDTH; i++)
  {
    bitVal = digitalRead(dataPin);

    /* Set the corresponding bit in bytesVal.
    */
    bytesVal |= (bitVal << ((DATA_WIDTH-1) - i));

    /* Pulse the Clock (rising edge shifts the next bit).
    */
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(clockPin, LOW);
  }

  return(bytesVal);
}

// the setup function runs once when you press reset or power the board
void setup() {
  /* Initialize our digital pins...
  */
  pinMode(ploadPin, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);

  digitalWrite(clockPin, LOW);
  digitalWrite(ploadPin, HIGH);
  
  // initialize digital pin as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  currentStep++;
  if(currentStep>7)
    currentStep=0;

  timeOff = analogRead(POT_PIN);

  if(digitalRead(BUTTON_PIN) == LOW)
  {
    activeStep++;

    if(activeStep>8)
      activeStep=0;
  }
  
  /* Read the state of all zones.
  */
  pinValues = read_shift_regs();

  for(int i=0; i<DATA_WIDTH; i++)
  {
    if((pinValues >> i) & 1)
    {
      digitalWrite(i+6, HIGH);
      if(i==activeStep)
        strip.setPixelColor(7-i, strip.Color(15,15,0));//yellow
      else
        strip.setPixelColor(7-i, strip.Color(15,0,0));//red
    }
    else if(i==activeStep)
      strip.setPixelColor(7-i, strip.Color(0,15,0));//green
    else if(i==currentStep)
      strip.setPixelColor(7-i, strip.Color(0,0,15));//blue
  }
  strip.show();

  delay(timeOn);

  for(int i=0; i<DATA_WIDTH; i++)
  {
    digitalWrite(i+6, LOW);
    if(i==activeStep)
      strip.setPixelColor(7-i, strip.Color(0,15,0));//green
    else
      strip.setPixelColor(7-i, strip.Color(0,0,0));
  }
  strip.show();

  delay(timeOff);
}
