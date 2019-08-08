/*
 * Creative Coding
 * Week 1, 02 - Draw your name! (part 2)
 * by Indae Hwang and Jon McCormack
 * Updated 2016
 * Copyright (c) 2014-2016 Monash University
 
 * This program allows you to draw using the mouse.
 * Press 's' to save your drawing as an image.
 * Press 'r' to erase your drawing and start with a blank screen
 * 
 */

// variables for the angle (in radians) and increment 
float angle;
float inc;
float counterClockwiseBranchX, counterClockwiseBranchY;
float clockwiseBranchX, clockwiseBranchY;

void setup() {
  size(1080, 720);
  background(200);
  rectMode(CENTER);  // rectangles drawn from the centre

  // initialise angle and inc to 0
  angle = 0;
  inc = 0;
}


void draw() {

  /* draw a rectangle at your mouse point while you are pressing 
   the left mouse button */

  // map the mouse x position to the range (0.01, 0.08)
  inc = map(mouseX, 0, width, 0.01, 0.08);

  // incremment the current angle
  angle = angle + inc;

  if (mousePressed) {

    stroke(170); 
    fill(120, 60, 75);

    ellipse(mouseX, mouseY, 10, 50);

    line(mouseX, mouseY, pmouseX, pmouseY); // pmouse is the mouse position at the previous frame

    // oscillate the radius over time
    float radius = 20 * abs( cos(frameCount) );

    //Counter-clockwise branch
    //Look at https://commons.wikimedia.org/wiki/File:Circle_cos_sin.gif to remind yourself on the use of sin and cos
    counterClockwiseBranchX = mouseX + radius * sin( angle);
    counterClockwiseBranchY = mouseY + radius * tan( angle);

    //clockwise branch
    clockwiseBranchX = mouseX + radius * sin( -angle);
    clockwiseBranchY = mouseY + radius * cos( -angle);

    //set the brush to translucent white
    stroke(110, 100, 150);

    // draw branches
    line(mouseX, mouseY, clockwiseBranchX, clockwiseBranchY);
    line(mouseX, mouseY, counterClockwiseBranchX, counterClockwiseBranchY);

    //draw randomly sized circles at the end of each branch
    float circleSize = random(3);
    rect(clockwiseBranchX, clockwiseBranchY, circleSize, circleSize);
    rect(counterClockwiseBranchX, counterClockwiseBranchY, circleSize, circleSize);
  }


  // save your drawing when you press keyboard 's'
  if (keyPressed == true && key == 's') {
    saveFrame("yourName.jpg");
  }

  // erase your drawing when you press keyboard 'r'
  if (keyPressed == true && key == 'r') {
    background(0);
  }
}