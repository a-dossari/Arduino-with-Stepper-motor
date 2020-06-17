#include <Stepper.h> //Arduino stepper motor library
#define STEPS 20 //The stepper motor has 20 steps per one revolution (you can change it)

Stepper stepper(STEPS, 5, 6, 10, 11); //the connection of the stepper motor in the pins of arduino board
const int but =  2; //the button is connected in pin 2 in the arduino board
const int pot = A0; //POT-HG (Potentiometer)is connected in pin A0 in the arduino board


void setup() {
pinMode(but, INPUT_PULLUP); //configure button pin as input with internal pull up enabled
}

int direction_ = 1;
int speed_ = 0;

void loop() {
if ( digitalRead(but) == 0 ) //if the button is pressed
if ( debounce() ) { //debounce button signal
  direction_ *= -1;  //variable of reverse direction
  while ( debounce() ); //wait until the button released
}
int val = analogRead(pot); //read the value from the potentiometer

if ( speed_ != map(val, 0, 1023, 5, 100) ) { //map digital value from [0, 1023] to [5, 100], where 5 is min speed, and 100 is max speed (in rpm)
  speed_ = map(val, 0, 1023, 5, 100);
  stepper.setSpeed(speed_); //set the motor speed
}

stepper.step(direction_); // move the stepper motor
}

bool debounce() { //function for button debounce
  
byte count = 0;
for(byte i = 0; i < 5; i++) {
 if (digitalRead(but) == 0)
  count++;
  delay(10);
}

if(count > 2)  
  return 1;
else           
  return 0;
}
