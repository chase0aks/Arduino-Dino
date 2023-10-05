#include "HUSKYLENS.h"               // Include the HuskyLens library
#include "SoftwareSerial.h"          // Include the SoftwareSerial library for communication
#include <Servo.h>                   // Include the Servo library for controlling servos

HUSKYLENS huskylens;                 // Create a HuskyLens object for communication
Servo servoX;                        // Create a servo object for X-axis movement
Servo servoY;                        // Create a servo object for Y-axis movement

const int servoXPin = 10;            // Pin for controlling the X-axis servo
const int servoYPin = 9;             // Pin for controlling the Y-axis servo
const int centerPos = 90;            // Center position for servos
const int minPos = 0;                // Minimum position for servos
const int maxPos = 180;              // Maximum position for servos

int soundSensorPin = 7;              // Pin for sound sensor
int playerPin = 5;                   // Pin for player

unsigned long previousCheckTime = 0;          // Variable to store the previous check time
const unsigned long checkInterval = 500;      // Interval for checking HuskyLens in milliseconds

bool isSoundDetected = false;        // Flag for sound detection
bool isPlayingSound = false;         // Flag for sound playing

void setup() {
  pinMode(soundSensorPin, INPUT);       // Set the sound sensor pin as input
  pinMode(playerPin, OUTPUT);           // Set the player pin as output

  Serial.begin(115200);                  // Initialize the serial communication
  Wire.begin();                          // Initialize the I2C communication

  while (!huskylens.begin(Wire)) {        // Check if the HuskyLens communication is successful
    Serial.println(F("Begin failed!"));
    Serial.println(F("1. Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings >> Protocol Type >> I2C)"));
    Serial.println(F("2. Please recheck the connection."));
    delay(100);
  }

  servoX.attach(servoXPin);               // Attach the X-axis servo to its pin
  servoY.attach(servoYPin);               // Attach the Y-axis servo to its pin
  moveServos(centerPos, centerPos);       // Move servos to the center position at startup
}

void loop() {
  unsigned long currentTime = millis();       // Get the current time
  checkSoundSensor();                          // Check the sound sensor

  if (currentTime - previousCheckTime >= checkInterval) {   // Check if it's time to request data from HuskyLens
    previousCheckTime = currentTime;
    checkHuskyLens();                          // Check the HuskyLens for object detection
  }
}

void checkSoundSensor() {
  int soundState = digitalRead(soundSensorPin);   // Read the state of the sound sensor

  if (soundState == LOW) {          // Check if the sound state is LOW (sound detected)
    digitalWrite(playerPin, HIGH);  // Turn on the player
    delay(200);                     // Delay for 200 milliseconds
    digitalWrite(playerPin, LOW);   // Turn off the player
  }
}

void checkHuskyLens() {
  if (!huskylens.request()) {                      // Request data from HuskyLens
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  }
  else if (!huskylens.isLearned()) {                // Check if HuskyLens has learned any objects
    Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
  }
  else if (!huskylens.available()) {                // Check if any object is detected by HuskyLens
    Serial.println(F("No block or arrow appears on the screen!"));
  }
  else {
    Serial.println(F("###########"));
    // Process the first object only
    HUSKYLENSResult result = huskylens.read();
    printResult(result);                          // Print the result
    moveServos(result.xCenter, result.yCenter);    // Move servos based on the HuskyLens center position
  }
}

void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block: xCenter=") + result.xCenter + F(", yCenter=") + result.yCenter + F(", width=") + result.width + F(", height=") + result.height + F(", ID=") + result.ID);
  }
  else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow: xOrigin=") + result.xOrigin + F(", yOrigin=") + result.yOrigin + F(", xTarget=") + result.xTarget + F(", yTarget=") + result.yTarget + F(", ID=") + result.ID);
  }
  else {
    Serial.println("Object unknown!");
  }
}

void moveServos(int xPos, int yPos) {
  int servoXAngle = map(xPos, 0, 320, minPos, maxPos);    // Map the HuskyLens X-axis position to servo angle
  int servoYAngle = map(yPos, 0, 240, minPos, maxPos);    // Map the HuskyLens Y-axis position to servo angle

  servoX.write(servoXAngle);                  // Set the X-axis servo angle
  servoY.write(servoYAngle);                  // Set the Y-axis servo angle
}