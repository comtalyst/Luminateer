// SonicRangerModule.ino by Robin D. on 5/18/2019
// Modified from SonicRangerModule.ino by c.d.odom on 8.16.17
// The robot that responds to commands signaled by LED(s)
/*
  Copyright Rawin Deeboonchai 2019.
  All Rights Reserved. No part of these contents
  may be reproduced, copied, modified or adapted,
  without the prior written consent of the author(s),
  unless when used for educational and non-profit purposes.
*/

float sonicRange(byte trigPin, byte echoPin, float maxRange) {
  // function, with arguments: (trigger pin, echo pin, maximum range (in cm))
  float timeout;                      // # of microseconds sensor will search for object
  long timeRoundTrip;                 // total time (from echo pin) for sound to travel
  float distanceToObject;             // the calculated distance to the object (in cm)
  float const Vs_cmpus = 0.034524;    // speed of sound in centimeters per microseconds

  // calculate the sensor’s timeout value using the maxRange argument and Equation xxx
  timeout = 2.0 * maxRange / Vs_cmpus;

  // DEBUG ONLY: Print the timeout value to the Serial Monitor:
  //  Serial.println("Sensor will time-out in " + (String) timeout + " us.");

  // make sure the trigger pin starts in the LOW state:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1500);        // delay to prevent over-sampling (may be smaller)

  // tell SR04 to begin data collection by sending a 10us-pulse to trigger pin:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);        // 10us is the minimum trigger pulse width
  digitalWrite(trigPin, LOW);

  // grab the pulse width from echo pin (i.e., sound’s total travel time from Tx to Rx):
  timeRoundTrip = pulseIn(echoPin, HIGH, timeout);

  // DEBUG ONLY: Print the round-trip time to the Serial Monitor:
  //   Serial.println("Round-trip time = " + (String) timeRoundTrip + " us");

  // calculate distance to the object (in cm) using Equation xxx:
  distanceToObject = Vs_cmpus * (float)timeRoundTrip / 2.0;

  return distanceToObject;
}

void sonicGraphPlotter(int trigPin, int echoPin, int maxExpectedRange) {
  // sonic ranger trigger pin, echo pin, and maximum expected range (in cm)
  float range = sonicRange(trigPin, echoPin, maxExpectedRange);      // open the Serial Plotter to check if your sonion ranger is working.
  Serial.println((String)range + ", 0, maxExpectedRange + 10");
}

void sonicDistanceTest(int trigPin, int echoPin, int maxExpectedRange) {
  // sonic ranger trigger pin, echo pin, and maximum expected range (in cm)
  // take a distance reading from ultrasonic sensor by calling the sonicRange()

  float distance = sonicRange(trigPin, echoPin, maxExpectedRange);   // (trigger, echo, maxRange in cm)

  // Print the distance to the object on the Serial Monitor:
  Serial.println("Distance = " + (String)distance + " cm");

  // Act on the distance reading:
  if (distance == 0) {
    Serial.println("No object is detected.");
    //    digitalWrite(LEDPin, LOW);     // turn OFF the LED
  }
  else if (distance < 15) {
    Serial.println("Object is near!");
    //    digitalWrite(LEDPin, HIGH);    // turn ON the LED
  }
  else {
    // object detected between 15cm and maxExpectedRange, therefore blink the LED:
    //    digitalWrite(LEDPin, HIGH);    // turn ON the LED
    delay(100);                    // some arbitrary delay time
    //    digitalWrite(LEDPin, LOW);     // turn OFF the LED
    delay(100);                    // some arbitrary delay time
  }

  delay(200);      // pause so user can visualize the data
}

float getRangeLeft() {
  float s1 = sonicRange(leftSonicTrigPin, leftSonicEchoPin, minFar);
  float s2 = sonicRange(leftSonicTrigPin, leftSonicEchoPin, minFar);
  float s3 = sonicRange(leftSonicTrigPin, leftSonicEchoPin, minFar);
  float range = selectRange(s1, s2, s3);
  if (range == 0) {
    return 999.0;
  }
  return range;
}
float getRangeRight() {
  float s1 = sonicRange(rightSonicTrigPin, rightSonicEchoPin, minFar);
  float s2 = sonicRange(rightSonicTrigPin, rightSonicEchoPin, minFar);
  float s3 = sonicRange(rightSonicTrigPin, rightSonicEchoPin, minFar);
  float range = selectRange(s1, s2, s3);
  if (range == 0) {
    return 999.0;
  }
  return range;
}
float selectRange(float s1, float s2, float s3) {
  if (s3 < s2) {
    float tmp = s2;
    s2 = s3;
    s3 = tmp;
  }
  if (s2 < s1) {
    float tmp = s1;
    s1 = s2;
    s2 = tmp;
  }
  if (s3 < s2) {
    float tmp = s2;
    s2 = s3;
    s3 = tmp;
  }
  if (s2 - s1 < s3 - s2) {
    return s1;
  }
  else {
    return s3;
  }
}
