# Arduino Dino

## Overview

The Arduino Dinosaur Display Control repository contains Arduino sketches for controlling a wooden dinosaur display inside a store. The sketches enable the dinosaur's eyeballs to follow kids as they interact with it and "roar" in response to kids' roars.

## Sketches

### 1. huskylensANDservo.ino

**Overview:** This Arduino sketch controls the movements of the dinosaur's eyeballs using servos and a HuskyLens. It communicates with the HuskyLens through I2C and adjusts the servos' positions based on the detected object's position on the HuskyLens screen, allowing the dinosaur's eyes to follow kids' movements.

**Usage:** Upload this sketch to your Arduino connected to the Raspberry Pi. Ensure the HuskyLens is properly connected via I2C. Configure the servos and HuskyLens placement according to your wooden dinosaur's design.

### 2. soundANDspeaker.ino

**Overview:** This Arduino sketch detects sound using a sound sensor and triggers a sound response (e.g., a dinosaur "roar") when a loud noise (e.g., kids' roars) is detected, enhancing the interactive experience.

**Usage:** Upload this sketch to your Arduino connected to the Raspberry Pi. Connect a sound sensor to the specified pin (soundSensorPin), and connect a speaker or sound module to the playerPin for the dinosaur's "roar." Adjust the sound sensor's sensitivity as needed.

### 3. both.ino

**Overview:** This Arduino sketch combines both eyeball control using a HuskyLens and sound detection functionalities. It allows the dinosaur's eyes to follow kids as they interact with it using the HuskyLens and "roar" back at them if they make a loud noise detected by the sound sensor.

**Usage:** Upload this sketch to your Arduino connected to the Raspberry Pi. Ensure the HuskyLens is properly connected via I2C. Connect a sound sensor to the specified pin (soundSensorPin), and connect a speaker or sound module to the playerPin for the dinosaur's "roar." Configure the servos and HuskyLens placement to match your wooden dinosaur's design.

## Getting Started

1. **Prerequisites**: Ensure that you have the necessary hardware components, including a Raspberry Pi, Arduino, HuskyLens, sound sensor, servos, and a speaker or sound module.

2. **Installation**:

   - Clone this GitHub repository to your local machine.

3. **Usage**:

   - Upload the desired Arduino sketch to your Arduino board using the Arduino IDE.
   - Make the necessary hardware connections as described in the sketch documentation.

## Dependencies

These Arduino sketches may require the following libraries:

- HuskyLens library (for HuskyLens control)
- SoftwareSerial library (for communication)
- Servo library (for servo control)

Please refer to the specific sketch documentation for detailed information on dependencies.

## License

This project is open-source and provided under the MIT License. See the [LICENSE](LICENSE) file for detailed information.

## Enjoy Your Dinosaur Display Control

Create an engaging and interactive experience with your wooden dinosaur display by using these Arduino sketches. Kids will be delighted as the dinosaur's eyes follow their movements, and they hear a thunderous "roar" in response to their own. For detailed information on how to use and configure each sketch, refer to their respective sections above.
