#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Flex sensor pins
const int flexPin1 = A0;
const int flexPin2 = A1;
const int flexPin3 = A2;
const int flexPin4 = A3;

// Base (straight hand) values from calibration
int baseF1=764, baseF2=757, baseF3=729, baseF4= 739;

float prevPitch = 0;
float prevRoll = 0;
unsigned long prevTime = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050
  mpu.initialize();
  mpu.setSleepEnabled(false);  // Wake up MPU6050

  delay(100);

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected");
  } else {
    Serial.println("MPU6050 Connection Failed");
    while (1);
  }

  Serial.println("Starting gesture detection...");
}

void loop() {
  // Read flex sensor values
  int f1 = analogRead(flexPin1);
  int f2 = analogRead(flexPin2);
  int f3 = analogRead(flexPin3);
  int f4 = analogRead(flexPin4);

  // Calculate bent values
  int bentF1 = max(0, baseF1 - f1);
  int bentF2 = max(0, baseF2 - f2);
  int bentF3 = max(0, baseF3 - f3);
  int bentF4 = max(0, baseF4 - f4);

  // Read accelerometer values
  int ax = mpu.getAccelerationX();
  int ay = mpu.getAccelerationY();
  int az = mpu.getAccelerationZ();

  // Calculate pitch and roll
  float pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  float roll  = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI;

  // Shake detection
  unsigned long currentTime = millis();
  float deltaPitch = abs(pitch - prevPitch);
  float deltaRoll = abs(roll - prevRoll);
  float deltaTime = (currentTime - prevTime) / 1000.0;
  bool shakeDetected = (deltaPitch > 20 || deltaRoll > 20) && deltaTime < 0.3;

  // Print all sensor values
  Serial.print("Flex: ");
  Serial.print(f1); Serial.print(" ");
  Serial.print(f2); Serial.print(" ");
  Serial.print(f3); Serial.print(" ");
  Serial.print(f4);

  Serial.print(" | Bent: ");
  Serial.print(bentF1); Serial.print(" ");
  Serial.print(bentF2); Serial.print(" ");
  Serial.print(bentF3); Serial.print(" ");
  Serial.print(bentF4);

  Serial.print(" | Pitch: ");
  Serial.print(pitch, 1);
  Serial.print(" | Roll: ");
  Serial.println(roll, 1);

  // Gesture Detection
  if (bentF1 < 20 && bentF2 < 6 && bentF3 < 6 && bentF4 < 6 && (roll < 50 || isnan(roll)) && (pitch < 50 || isnan(pitch))){
    Serial.println("GESTURE DETECTED: HELLO");
  } else if (bentF1 > 10 && bentF2 > 4 && bentF3 > 6 && bentF4 > 6 && (roll < 20 || isnan(roll))) {
    Serial.println("GESTURE DETECTED: Water");
  } else if (bentF1 < 20 && bentF2 > 4 && bentF3 > 6 && bentF4 < 4) {
    Serial.println("GESTURE DETECTED: OK");
  }  else if (bentF1 > 5 && bentF2 < 2 &&  bentF3 < 3 && bentF4 < 5) {
    Serial.println("GESTURE DETECTED: Good");
  }  else if (bentF1 > 5 && bentF2 > 2 &&  bentF3 > 3 && bentF4 < 5) {
    Serial.println("GESTURE DETECTED: washroom");
  } else if (bentF1 < 10  && bentF2 < 10 && bentF3 > 6 && bentF4 > 10) {
    Serial.println("GESTURE DETECTED: Peace");
  } else if (bentF1 < 10  && bentF2 > 10 && bentF3 > 6 && bentF4 > 4) {
    Serial.println("GESTURE DETECTED: medicine");
  } else if (bentF1 < 10 && bentF2 < 10 && bentF3 < 10 && bentF4 < 10 && pitch > 50 && (roll < 20 || isnan(roll))) {
    Serial.println("GESTURE DETECTED: Stop ");
  } else if (bentF1 > 10 && bentF2 > 4 && bentF3 > 6 && bentF4 > 5 && roll > 20) {
    Serial.println("GESTURE DETECTED: Hungry ");
  } else if (bentF1 < 10 && bentF2 < 10 && bentF3 < 5 && bentF4 <7  && roll > 20) {
    Serial.println("GESTURE DETECTED: Sleep ");
  } else if (shakeDetected) {
    Serial.println("GESTURE DETECTED: Shake");
  } else {
    Serial.println("GESTURE DETECTED: UNKNOWN");
  }

  // Update for next shake comparison
  prevPitch = pitch;
  prevRoll = roll;
  prevTime = currentTime;

  delay(3000);  // Adjust for stability
}
