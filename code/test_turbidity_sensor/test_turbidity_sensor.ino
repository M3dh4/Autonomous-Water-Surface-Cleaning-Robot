int turbidityPin = 13;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Turbidity sensor test...");
}

void loop() {
  int value = analogRead(turbidityPin);

  Serial.print("Raw Value: ");
  Serial.println(value);

  // Basic interpretation
  if (value > 2500) {
    Serial.println("Water is CLEAR");
  } else if (value > 1500) {
    Serial.println("Water is MEDIUM");
  } else {
    Serial.println("Water is DIRTY");
  }

  Serial.println("----------------------");
  delay(1000);
}