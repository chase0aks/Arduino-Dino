int soundSensorPin = 7;        // Pin for sound sensor
int playerPin = 5;             // Pin for player

void setup() {
  pinMode(soundSensorPin, INPUT);   // Set the sound sensor pin as input
  pinMode(playerPin, OUTPUT);       // Set the player pin as output
}

void loop() {
  int soundState = digitalRead(soundSensorPin);   // Read the state of the sound sensor

  if (soundState == LOW) {          // Check if the sound state is LOW (sound detected)
    digitalWrite(playerPin, HIGH);  // Turn on the player
    delay(200);                     // Delay for 200 milliseconds
    digitalWrite(playerPin, LOW);   // Turn off the player
  }
}
