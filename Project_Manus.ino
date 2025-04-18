#include <AccelStepper.h>
#include <IBusBM.h>
#include <Servo.h>
#include <TMCStepper.h>

// Stepper2 TMC2209 Config
#define STEP_PIN_2 4
#define DIR_PIN_2 5
#define EN_PIN_2 13
#define R_SENSE 0.11f
#define DRIVER_ADDRESS 0b00

// Serial1 used for UART to TMC2209
TMC2209Stepper driver2(&Serial1, R_SENSE, DRIVER_ADDRESS);

// AccelStepper setup
AccelStepper stepper1(1, 2, 3);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN_2, DIR_PIN_2); // updated for TMC2209
AccelStepper stepper3(1, 6, 7);
AccelStepper stepper4(1, 8, 9);
AccelStepper stepper5(1, 10, 11);

Servo myservo;
IBusBM ibus;

void setup() {
  delay(500);

  // Enable pin for stepper2
  pinMode(EN_PIN_2, OUTPUT);
  digitalWrite(EN_PIN_2, LOW); // Enable driver

  // Start UART for TMC2209
  Serial1.begin(115200);
  driver2.begin();
  delay(500);
  driver2.rms_current(1850);        // Set motor current in mA
  delay(500);
  driver2.microsteps(16);          // Optional
  driver2.en_spreadCycle(true);   // Enable StealthChop
  //driver2.TPOWERDOWN(255); // Disables automatic power down when idle
  driver2.pdn_disable(true);       // Use UART
  driver2.I_scale_analog(false);   // Use digital current scaling
  driver2.TPOWERDOWN(255); // Disables automatic power down when idle

  // Set max speeds
  stepper1.setMaxSpeed(650);
  stepper2.setMaxSpeed(650); // Right Y (TMC2209)
  stepper3.setMaxSpeed(650);
  stepper4.setMaxSpeed(900);
  stepper5.setMaxSpeed(650);

  myservo.attach(12);
  Serial.begin(115200);
  ibus.begin(Serial1);

  delay(500);
}

void loop() {
  controlStep(stepper1, 0); // Right X
  controlStep(stepper2, 1); // Right Y (TMC2209)
  controlStep(stepper3, 2); // Left Y
  controlStep(stepper4, 3); // Left X
  controlStep(stepper5, 4); // Dial
  controlServo(5);          // Claw
}

void controlStep(AccelStepper &stepper, int channel) {
  int chVal = ibus.readChannel(channel) - 1502;

  if (chVal > -50 && chVal < 50) {
    stepper.setSpeed(0);
  } else {
    int jVal = -chVal;
    stepper.setSpeed(jVal);
    Serial.print("Channel "); Serial.print(channel);
    Serial.print(": "); Serial.println(jVal);
  }

  stepper.runSpeed();
}

void controlServo(int channel) {
  static int prevAngle = -1;
  int chVal = ibus.readChannel(channel) - 1502;
  int jVal = -(chVal * 1.5);
  int angle = map(jVal, -755, 755, 0, 180);

  if (angle != prevAngle) {
    Serial.print("Channel "); Serial.print(channel);
    Serial.print(": "); Serial.print(jVal);
    Serial.print(" Degrees: "); Serial.print(angle); Serial.println("°");
    myservo.write(angle);
    prevAngle = angle;
  }
}
