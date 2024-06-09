;k#define ldir 29
#define rdir 30
#define lspd 40
#define rspd 39
#define lslp 31
#define rslp 11

#define trigPin 9
#define echoPin 8
#define distanceThreshold 20 // Distance threshold in centimeters

#define leftBumperPin 7
#define rightBumperPin 6

void setup() {
  // put your setup code here, to run once:
  pinMode(ldir, OUTPUT);
  pinMode(rdir, OUTPUT);
  pinMode(lspd, OUTPUT);
  pinMode(rspd, OUTPUT);
  pinMode(lslp, OUTPUT);
  pinMode(rslp, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(leftBumperPin, INPUT_PULLUP);
  pinMode(rightBumperPin, INPUT_PULLUP);
  digitalWrite(lslp, HIGH);
  digitalWrite(rslp, HIGH);
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  // Check for obstacles using the ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Convert duration to distance in cm

  // Check bumper switches
  bool leftBumperTriggered = !digitalRead(leftBumperPin);
  bool rightBumperTriggered = !digitalRead(rightBumperPin);

  if (distance < distanceThreshold || leftBumperTriggered || rightBumperTriggered) {
    // Stop the robot
    analogWrite(lspd, 0);
    analogWrite(rspd, 0);
    if (distance < distanceThreshold) {
      Serial.println("Obstacle detected! Stopping.");
    }
    if (leftBumperTriggered) {
      Serial.println("Left bumper triggered! Stopping.");
    }
    if (rightBumperTriggered) {
      Serial.println("Right bumper triggered! Stopping.");
    }
  } else {
    // Move the robot forward
    digitalWrite(ldir, LOW);
    digitalWrite(rdir, LOW);
    analogWrite(lspd, 50);
    analogWrite(rspd, 50);
    Serial.println("Moving forward.");
  }

  delay(100); // Delay to prevent excessive checking
}
