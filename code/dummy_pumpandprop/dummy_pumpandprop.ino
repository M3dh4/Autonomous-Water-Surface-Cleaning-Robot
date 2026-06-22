// Motor A (Pump)
#define ENA 9
#define IN1 2
#define IN2 3

// Motor B (Propeller)
#define ENB 10
#define IN3 4
#define IN4 5

// Turbidity sensor
#define TURBIDITY_PIN A0

int speedVal = 200;   // default speed for pump/prop
char command;

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopPump();
  stopProp();
}

void loop() {

  // 🔹 Turbidity sensor (unchanged)
  int turbidityValue = analogRead(TURBIDITY_PIN);

  Serial.print("Turbidity: ");
  Serial.println(turbidityValue);

  if(turbidityValue > 700){
    Serial.println("Water is clear.");
  }
  else if(turbidityValue > 300 && turbidityValue < 700){
    Serial.println("Water is turbid.");
  }
  else{
    Serial.println("Water is dirty");
  }

  // 🔹 Serial control
  if (Serial.available()) {
    command = Serial.read();

    // Speed control (0–9)
    if (command >= '0' && command <= '9') {
      int level = command - '0';
      speedVal = map(level, 0, 9, 0, 255);
      Serial.print("Speed: ");
      Serial.println(speedVal);
    }

    // Pump control
    else if (command == 'P') startPump();
    else if (command == 'X') stopPump();   // use X instead of SP

    // Propeller control
    else if (command == 'F') forwardProp();
    else if (command == 'S') stopProp();
  }

  delay(500);
}

// -------- PUMP --------

void startPump() {
  analogWrite(ENA, speedVal);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void stopPump() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// -------- PROPELLER --------

void forwardProp() {
  analogWrite(ENB, speedVal);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopProp() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}