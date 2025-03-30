/*
 * This file is for assignment 2: immersion of Experiences & Interfaces.
 * It controls a lantern hanging in the cocoon as both an invitation to participants and a safety measure.
 * The light sensor reads the ambient lightness and dims up the LED strips when it is too dark and dims down when it is bright enough.
 * Working by itself, or combining with the brightness of the screen, the lantern provides a "breathing" effect, calling participants to come into the cocoon. 
*/

// settings
const int ledPins[] = {2, 3, 5}; // output pins for LED stripe
const int ledNumber = 3; // the number of LED strips
const int inputPin = A7; // input pin for light senor

const int readInterval = 2000; // how long between each reading of light; deside the length of each wave

int sensorValue = 0; // the initial value of light sensor; the light will turn on at least once since this value is definitely lower than the threshold
int threshold = 320; // on which brightness the light will turn on
int output = 0; // set the intial brightness of LED strips to 0, so that the lantern will have a dim-up effect
int current = 0; // record each reading time 

void setup() {

  Serial.begin(9600); // for debugging

  for (int i=0; i<ledNumber; i++){ // set up the output pins
  pinMode(ledPins[i], OUTPUT);   
  };

  current = millis(); // record the current time

}

void loop() {

  // reading the light value 
  if(millis()-current > readInterval ){ 
  sensorValue = analogRead(inputPin);
  current = millis();
}

  Serial.println(sensorValue); // for debugging

  // change the output value based on whether the light value is greater than the threshold or not
  if(sensorValue<threshold){
    output ++;
  }else{
    output --;
  }

  // constrain the output value so it won't be too high or too low to change back to the valid range
  output = constrain(output, 0, 255);

  // set the LED strips
  for (int i=0; i<ledNumber; i++){
  analogWrite(ledPins[i], output);
  };

  // wait 100ms before adjust the output value to create the dim-up or dim-down effect
  delay(100);

}
