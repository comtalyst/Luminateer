// Luminateer by Robin_D on 4.8.19
// For GS Robotics Final Project
// Main Frame for the Robot

const int leftServoPin = 0, rightServoPin = 1, LEDPin = 13;
const int redPin = 23;     // tricolor LED board
const int greenPin = 22;
const int bluePin = 21;
const byte IRSensorPin = A0;
const byte leftIRLineSensorPin = A1;
const byte rightIRLineSensorPin = A2;
const int IRLMaxWhite = 100;
const int IRLMaxBlack = 1050;
const byte lightPin = A3;
const byte potentioPin = A4;
const byte echoPin = 3;
const byte trigPin = 2;

void setup() {
  Serial.begin(9600);       // Open the serial port
  delay(100);
  pinMode(leftServoPin, OUTPUT);   // yellowy wheel
  pinMode(rightServoPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);                // onboard LED
  pinMode(redPin, OUTPUT);                // Colored LED
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
//  pinMode(leftIRLineSensorPin, INPUT);    // left Infrared Line Sensor
//  pinMode(rightIRLineSensorPin, INPUT);   // right Infrared Line Sensor
//  pinMode(lightPin, INPUT_PULLUP);        // Photoresistor
//  pinMode(potentioPin, INPUT);            // Potentiometer
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  blinkOK(3);
  digitalWrite(bluePin, HIGH);
}

void loop() {
  
}
