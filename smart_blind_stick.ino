// --- Advanced Blind Stick Code (Sound + Vibration) ---

// Define Pin Numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 11;
const int motorPin = 6;  // New pin for Vibration Motor

// Define variables
long duration;
int distance;

void setup() {
  Serial.begin(9600); 

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT); // Configure motor pin
}

void loop() {
  // --- ULTRASONIC SENSOR LOGIC ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // --- SMART FEEDBACK LOGIC ---

  // ZONE 1: CRITICAL DANGER (< 10cm)
  // Continuous Buzz + Continuous Vibrate
  if (distance > 0 && distance <= 10) {
    tone(buzzerPin, 2000);       
    digitalWrite(motorPin, HIGH); // Turn motor ON full power
  }
  
  // ZONE 2: WARNING (10cm - 50cm)
  // Beeping + Pulsing Vibration (Speed depends on distance)
  else if (distance > 10 && distance <= 50) {
    
    // ON Cycle
    tone(buzzerPin, 1000);
    digitalWrite(motorPin, HIGH); // Vibrate
    delay(50);                    // Duration of the pulse
    
    // OFF Cycle
    noTone(buzzerPin);
    digitalWrite(motorPin, LOW);  // Stop Vibrating
    
    // Smart Delay: The closer the object, the shorter the pause
    // 50cm = 300ms pause (Slow pulse)
    // 11cm = 66ms pause (Fast pulse)
    delay(distance * 6);   
  }
  
  // ZONE 3: SAFE (> 50cm)
  // Silence + No Vibration
  else {
    noTone(buzzerPin);
    digitalWrite(motorPin, LOW);
    delay(100);
  }
}