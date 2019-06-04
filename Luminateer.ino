// Luminateer.ino by Robin D. on 5/18/2019
// The robot that responds to commands signaled by LED(s)
/*
  Copyright Rawin Deeboonchai 2019.
  All Rights Reserved. No part of these contents
  may be reproduced, copied, modified or adapted,
  without the prior written consent of the author(s),
  unless when used for educational and non-profit purposes.
*/
/*
  Special thanks to Brian Patton for porting Pixy2 to Teensy!
  Instructions video link: https://www.youtube.com/watch?v=OqZ9gPFoNl8

  Pixy2 Libraries could be downloaded from here:
  https://pixycam.com/downloads-pixy2/
*/


#include <Pixy2SPI_SS.h>
#include <PIDLoop.h>

const byte leftServoPin = 1, rightServoPin = 2;
const byte rightSonicEchoPin = 8;
const byte rightSonicTrigPin = 7;
const byte leftSonicEchoPin = 6;
const byte leftSonicTrigPin = 5;

const int forwardSig = 2;
const int followSig = 3;
const int faceSig = 1;

const int minWalkable = 10;
const int stepsPerTick = 1;
const int turnSteps = 25;
const int minFar = 50;
const int maxFollowShift = 20;

Pixy2SPI_SS pixy;
PIDLoop panLoop(400, 0, 400, true);
PIDLoop tiltLoop(500, 0, 500, true);

int gloveX, gloveY;
int32_t panOffset, tiltOffset;

void setup() {
  Serial.begin(115200);       // Open the serial port
  delay(100);
  pinMode(leftServoPin, OUTPUT);
  pinMode(rightServoPin, OUTPUT);
  pinMode(rightSonicTrigPin, OUTPUT);
  pinMode(rightSonicEchoPin, INPUT);
  pinMode(leftSonicTrigPin, OUTPUT);
  pinMode(leftSonicEchoPin, INPUT);
  pixy.init();
  pixy.changeProg("color_connected_components");
  panTiltReset();
}

void loop() {
  pixy.ccc.getBlocks();                           // look for the LED
  if (!pixy.ccc.numBlocks) {                      // Not found? --> cease the movement
    panTiltReset();
    robotStop(stepsPerTick);
  }
  else {                                          // Found
    int sig = pixy.ccc.blocks[0].m_signature;
    panTiltFollow1();
    if (sig == forwardSig) {                      // Signal ID indicates "Forward"
      panTiltFollow2();
      if (getRangeLeft() >= minWalkable && getRangeRight() >= minWalkable) {
        forwardFast(stepsPerTick);
      }
      else {                                      // Sonic Ranger Sensor detects a wall --> turn around
        leftFast(turnSteps);
        leftFast(turnSteps);
      }
    }
    else if (sig == faceSig) {                    // Signal ID Indicates "Face the signal"
      if ((int)panOffset > maxFollowShift) {
        leftFast(stepsPerTick);
      }
      else if ((int)panOffset < -maxFollowShift) {
        rightFast(stepsPerTick);
      }
    }
    else if (sig == followSig) {                  // Signal ID Indicates "Moves toward the signal"
      panTiltFollow2();
      if ((int)panOffset > maxFollowShift) {
        leftFast(stepsPerTick);
      }
      else if ((int)panOffset < -maxFollowShift) {
        rightFast(stepsPerTick);
      }
      if (getRangeLeft() >= minWalkable && getRangeRight() >= minWalkable) {
        forwardFast(stepsPerTick);
      }
    }
  }
}

void panTiltReset() {
  panLoop.reset();
  tiltLoop.reset();
  pixy.setServos(panLoop.m_command, tiltLoop.m_command);
}
void panTiltFollow1() {                   // prepare to follow
  gloveX = pixy.ccc.blocks[0].m_x;
  gloveY = pixy.ccc.blocks[0].m_y;
  panOffset = (int32_t)pixy.frameWidth / 2 - (int32_t)gloveX;
  tiltOffset = (int32_t)gloveY - (int32_t)pixy.frameHeight / 2;
  panLoop.update(panOffset);
  tiltLoop.update(tiltOffset);
}

void panTiltFollow2() {                   // execute
  pixy.setServos(panLoop.m_command, tiltLoop.m_command);
}
