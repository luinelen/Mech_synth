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
}

// the loop function runs over and over again forever
void loop() {
  /* Read the state of all zones.
  */
  pinValues = read_shift_regs();

  for(int i=0; i<DATA_WIDTH; i++)
  {
    if((pinValues >> i) & 1)
      digitalWrite(i+6, HIGH);
  }

  delay(timeOn);

  for(int i=0; i<DATA_WIDTH; i++)
    digitalWrite(i+6, LOW);
}
