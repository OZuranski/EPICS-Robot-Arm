#include <AccelStepper.h>
#include <IBusBM.h>

// Define the stepper motors and their pins
AccelStepper stepper1(1, 2, 3);
AccelStepper stepper2(1, 4, 5);
AccelStepper stepper3(1, 6, 7);
AccelStepper stepper4(1, 8, 9);

IBusBM ibus;

void setup() {
  delay(500);
  stepper1.setMaxSpeed(800);
  stepper2.setMaxSpeed(800);
  stepper3.setMaxSpeed(800);
  stepper4.setMaxSpeed(800);

  Serial.begin(115200);
  ibus.begin(Serial1);
  delay(500);
}

void loop() {
  control(stepper1, 0); // Control stepper1 with channel 0
  control(stepper2, 1); // Control stepper2 with channel 1
  control(stepper3, 2); // Control stepper3 with channel 2
  control(stepper4, 3); // Control stepper4 with channel 3
}

void control(AccelStepper &stepper, int channel) {
  int chVal = ibus.readChannel(channel) - 1502;
  
  // Deadzone logic
  if (chVal > -100 && chVal < 100) {
    stepper.setSpeed(0); // Stop motor if in deadzone
  } else {
    int jVal = chVal * 1.5;
    stepper.setSpeed(jVal); // Set motor speed
    Serial.print("Channel "); Serial.print(channel);
    Serial.print(": "); Serial.println(jVal);
  }

  stepper.runSpeed(); // Move motor
}
