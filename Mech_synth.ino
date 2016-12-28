int timeOn = 100;
int timeOff = 500;

// the setup function runs once when you press reset or power the board
void setup() {
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
  digitalWrite(13, HIGH);   // turn on (HIGH is the voltage level)
  delay(timeOn);              // wait
  digitalWrite(13, LOW);    // turn off by making the voltage LOW
  delay(timeOff);              // wait

  digitalWrite(12, HIGH);   // turn on (HIGH is the voltage level)
  delay(timeOn);              // wait
  digitalWrite(12, LOW);    // turn off by making the voltage LOW
  delay(timeOff);              // wait

  digitalWrite(11, HIGH);   // turn on (HIGH is the voltage level)
  delay(timeOn);              // wait
  digitalWrite(11, LOW);    // turn off by making the voltage LOW
  delay(timeOff);              // wait

  digitalWrite(10, HIGH);   // turn on (HIGH is the voltage level)
  delay(timeOn);              // wait
  digitalWrite(10, LOW);    // turn off by making the voltage LOW
  delay(timeOff);              // wait

  digitalWrite(9, HIGH);   // turn on (HIGH is the voltage level)
  delay(timeOn);              // wait
  digitalWrite(9, LOW);    // turn off by making the voltage LOW
  delay(timeOff);              // wait

  digitalWrite(8, HIGH);   // turn on (HIGH is the voltage level)
  delay(timeOn);              // wait
  digitalWrite(8, LOW);    // turn off by making the voltage LOW
  delay(timeOff);              // wait

  digitalWrite(7, HIGH);   // turn on (HIGH is the voltage level)
  delay(timeOn);              // wait
  digitalWrite(7, LOW);    // turn off by making the voltage LOW
  delay(timeOff);              // wait

  digitalWrite(6, HIGH);   // turn on (HIGH is the voltage level)
  delay(timeOn);              // wait
  digitalWrite(6, LOW);    // turn off by making the voltage LOW
  delay(timeOff);              // wait

}
