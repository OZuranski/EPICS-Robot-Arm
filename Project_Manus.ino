#include <AccelStepper.h>
#include <IBusBM.h>
#include <Servo.h>

// Define the stepper motors and their pins, -> stepper'n'(1, step pin, dir pin)
AccelStepper stepper1(1, 2, 3);
AccelStepper stepper2(1, 4, 5);
AccelStepper stepper3(1, 6, 7);
AccelStepper stepper4(1, 8, 9);
AccelStepper stepper5(1, 10, 11);

Servo myservo; // Servo for claw

IBusBM ibus;   // for controller comms

void setup() {
  delay(500);
  stepper1.setMaxSpeed(650);  // Right X
  stepper2.setMaxSpeed(650);  // Right Y
  stepper3.setMaxSpeed(650);  // Left Y
  stepper4.setMaxSpeed(900);  // Left X
  stepper5.setMaxSpeed(650);  // Left? dial
  myservo.attach(12);         // Servo should be plugged into 12 pmw pin 
  Serial.begin(115200);       // baud rate for serial comm with the controller
  ibus.begin(Serial1);
  delay(500);
}

void loop() {
  controlStep(stepper1, 0); // Control stepper1 with channel 0 - Right X
  controlStep(stepper2, 1); // Control stepper2 with channel 1 - Right Y
  controlStep(stepper3, 2); // Control stepper3 with channel 2 - Left Y
  controlStep(stepper4, 3); // Control stepper4 with channel 3 - Left X
  controlStep(stepper5, 4); // Control stepper5 with channel 4 - Left dial
  controlServo(5);          // Control myservo  with channel 5 - Right dial  
}

void controlStep(AccelStepper &stepper, int channel) {

  int chVal = ibus.readChannel(channel) - 1502; // centers value, so base position value = 0
  
  // Deadzone logic
  if (chVal > -50 && chVal < 50) {
    stepper.setSpeed(0); // Stop motor if in deadzone
  } 
  else {
    int jVal = -(chVal);
    
    stepper.setSpeed(jVal); // Set motor speed
    Serial.print("Channel "); Serial.print(channel); // print which channel with corresponding value being read, ONLY PRINTS IF THERE IS A READING
    Serial.print(": "); Serial.println(jVal);
  }

  stepper.runSpeed(); // Move motor
}

void controlServo(int channel) {
  
  static int prevAngle = -1; // used to store previous angle so that (on line 65) we don't print or try to move servo -
  // - if values aren't actually being changed.

  int chVal = ibus.readChannel(channel) - 1502;
  
  int jVal = -(chVal * 1.5);
  int angle = map(jVal, -755, 755, 0, 180); // Convert joystick val to angle from 0 to 180

  //if (abs(prevAngle - angle) < 2) return;

  if (angle != prevAngle) {   
    Serial.print("Channel "); Serial.print(channel); // print which channel with corresponding value being read, ONLY PRINTS IF THERE IS A READING
    // Prints joystick value and corresponding channel, but also the correlating angle for the servo to go to
    Serial.print(": "); Serial.print(jVal); Serial.print(" Degrees: "); Serial.print(angle); Serial.println("°");  

    myservo.write(angle); // Move servo to correct angle
    prevAngle = angle;
  }  
}
