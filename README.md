# Luminateer
An Arduino-powered software that makes PattonRobotics OneBot follows the tricolor LED signal.

The color of the LED will control the robot respect to these commands:
Red => moves the robot forward
Green => turns the robot toward the light
Blue => both moves and turns (in other words, moves the robot toward the light)
Used Pixy2 camera to track the light (Pixy2: https://pixycam.com/pixy2/);
