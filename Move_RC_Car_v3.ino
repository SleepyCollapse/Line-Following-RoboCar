const int leftSensorPin = A0;  // Left IR sensor connected to analog pin A0
const int rightSensorPin = A1; // Right IR sensor connected to analog pin A1
const int leftDigitalPin = 7;  // Left IR sensor digital output pin
const int rightDigitalPin = 8; // Right IR sensor digital output pin

// Threshold for analog signal to determine black/white
const int threshold = 500;  // Set according to your sensor's readings

void setup() {
  pinMode(leftDigitalPin, INPUT);   // Left IR sensor digital pin as input
  pinMode(rightDigitalPin, INPUT);  // Right IR sensor digital pin as input

  // Serial monitor for debugging analog values
  Serial.begin(9600);
}

void loop() {
  // Read analog values from both sensors
  int leftSensorValue = analogRead(leftSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);

  // Read digital values from both sensors
  int leftDigitalValue = digitalRead(leftDigitalPin);
  int rightDigitalValue = digitalRead(rightDigitalPin);

  // Debugging - print analog values to serial monitor (optional)
  Serial.print("Left Analog: ");
  Serial.print(leftSensorValue);
  Serial.print("  Right Analog: ");
  Serial.println(rightSensorValue);

  // Decide based on digital sensor values first
  if (leftDigitalValue == LOW && rightDigitalValue == LOW) {
    // Both sensors are on the black line
    // Fine-tune using analog values for more control
    if (leftSensorValue < threshold && rightSensorValue < threshold) {
      // Both sensors detect black strongly, continue straight
      runMotors();
    }
  } 
  else if (leftDigitalValue == LOW && rightDigitalValue == HIGH) {
    // Left sensor detects black, right sensor detects white
    // Turn right (use analog values for fine-tuning)
    if (leftSensorValue < threshold) {
      turnRight();
    }
  } 
  else if (leftDigitalValue == HIGH && rightDigitalValue == LOW) {
    // Right sensor detects black, left sensor detects white
    // Turn left (use analog values for fine-tuning)
    if (rightSensorValue < threshold) {
      turnLeft();
    }
  } 
  else {
    // Both sensors are on white (off the line)
    stopMotors();
  }

  delay(100); // Small delay to avoid excessive readings
}

void runMotors() {
  // Move forward at full speed
  analogWrite(ENA, 200);  // Motor A speed MAX
  analogWrite(ENB, 200);  // Motor B speed MAX

  digitalWrite(IN1, HIGH);  // Motor A forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);  // Motor B forward
  digitalWrite(IN4, LOW);
}

void turnRight() {
  // Adjust motor speeds to turn right
  analogWrite(ENA, 150);  // Slow down Motor A
  analogWrite(ENB, 200);  // Keep Motor B at full speed

  digitalWrite(IN1, LOW);  // Motor A backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);  // Motor B forward
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  // Adjust motor speeds to turn left
  analogWrite(ENA, 200);  // Keep Motor A at full speed
  analogWrite(ENB, 150);  // Slow down Motor B

  digitalWrite(IN1, HIGH);  // Motor A forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Motor B backward
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  // Stop both motors
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
