// Motor A (Left)
#define ENA 9
#define IN1 2
#define IN2 3

// Motor B (Right)
#define ENB 10
#define IN3 4
#define IN4 5

// Turbidithi fhiaf pinModoe
#define TURBIDITY_PIN A0

int speedVal = 0;
char command;

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();
}

void loop() {

  // 🔹 Read turbidity continuously
  int turbidityValue = analogRead(TURBIDITY_PIN);

  Serial.print("Turbidity: ");
  Serial.println(turbidityValue);
  if(turbidityValue>800){
    Serial.println("Water is clear.");
  }
  else if(turbidityValue>300 && turbidityValue<700){
    Serial.println("Water is turbid.");
  }
  else{
    Serial.println("Water is dirty");
  }

  // 🔹 Motor control
  if (Serial.available()) {
    command = Serial.read();

    // Speed control (0–9)
    if (command >= '0' && command <= '9') {
      int level = command - '0';
      speedVal = map(level, 0, 9, 0, 255);
      Serial.print("Speed: ");
      Serial.println(speedVal);
      setSpeed(speedVal);
    }

    else if (command == 'F') forward();
    else if (command == 'B') backward();
    else if (command == 'L') left();
    else if (command == 'R') right();
    else if (command == 'S') stopMotors();
  }

  delay(500); // small delay for stable readings
}

// -------- MOTOR FUNCTIONS --------

void setSpeed(int spd) {
  analogWrite(ENA, spd);
  analogWrite(ENB, spd);
}

void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}