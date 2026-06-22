#include <Servo.h>

Servo myServo;

const int SERVO_PIN = 8;

bool sweepMode = false;
int angle = 0;
int stepDir = 1;

String input = "";  // to store full number

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  myServo.write(0);
}

void loop() {

  // 🔹 Read full number from Serial
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {   // end of input
      int value = input.toInt();

      Serial.print("Received: ");
      Serial.println(value);

      if (value < 10) {
        sweepMode = true;
        Serial.println("Sweep ON");
      } else {
        sweepMode = false;
        Serial.println("Sweep OFF");
      }

      input = ""; // reset
    } else {
      input += c;
    }
  }

  // 🔹 Sweep logic
  if (sweepMode) {
    myServo.write(angle);
    angle += stepDir;

    if (angle >= 90) stepDir = -1;
    if (angle <= 0)  stepDir = 1;

    delay(20);
  }
}