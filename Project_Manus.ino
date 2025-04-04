#include <AccelStepper.h>
#include <IBusBM.h>

// Define the stepper motors and their pins, -> stepper'n'(1, step pin, dir pin)
AccelStepper stepper1(1, 2, 3);
AccelStepper stepper2(1, 4, 5);
AccelStepper stepper3(1, 6, 7);
AccelStepper stepper4(1, 8, 9);


IBusBM ibus;

void setup() {
  delay(500);
  stepper1.setMaxSpeed(650);  // Right X
  stepper2.setMaxSpeed(650);  // Right Y
  stepper3.setMaxSpeed(650);  // Left Y
  stepper4.setMaxSpeed(900);  // Left X
  
  Serial.begin(115200);        // baud rate for serial comm with the controller
  ibus.begin(Serial1);
  delay(500);
}

void loop() {
  controlStep(stepper1, 0); // Control stepper1 with channel 0 - Right X
  controlStep(stepper2, 1); // Control stepper2 with channel 1 - Right Y
  controlStep(stepper3, 2); // Control stepper3 with channel 2 - Left Y
  controlStep(stepper4, 3); // Control stepper4 with channel 3 - Left X
  // controlServo call would go here. I was going to write it but it wouldn't be worth it until I have an actual servo to test as I write  
}

void controlStep(AccelStepper &stepper, int channel) {
  int chVal = ibus.readChannel(channel) - 1502;
  
  // Deadzone logic
  if (chVal > -100 && chVal < 100) {
    stepper.setSpeed(0); // Stop motor if in deadzone
  } else {
    int jVal = -(chVal * 1.5);
    
    stepper.setSpeed(jVal); // Set motor speed
    Serial.print("Channel "); Serial.print(channel); // print which channel with corresponding value being read, ONLY PRINTS IF THERE IS A READING
    Serial.print(": "); Serial.println(jVal);
  }

  stepper.runSpeed(); // Move motor
}

/*void controlServo(int channel) {

}*/
