#define ldir 29
#define rdir 30
#define lspd 40
#define rspd 39
#define lslp 31
#define rslp 11

#define trigPin 9
#define echoPin 8
#define distanceThreshold 20 // Distance threshold in centimeters

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
  digitalWrite(lslp, HIGH);
  digitalWrite(rslp, HIGH);
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Convert duration to distance in cm

  if (distance < distanceThreshold) {
    // Stop the robot
    analogWrite(lspd, 0);
    analogWrite(rspd, 0);
    Serial.println("Obstacle detected! Stopping.");
    digitalWrite(ldir,HIGH);
    analogWrite(lspd, 50);
    analogWrite(rspd, 50);
    
    
  } else {
    // Move the robot forward
    digitalWrite(ldir, HIGH);
    digitalWrite(rdir, HIGH);
    analogWrite(lspd, 50);
    analogWrite(rspd, 50);
    Serial.println("Moving BACKWARD.");
  }
  
  
  delay(100); // Delay to prevent excessive pinging
}
