/*
 * Creative Coding
 * Week 2, 03 - n squares
 * by Indae Hwang and Jon McCormack
 * Updated 2016
 * Copyright (c) 2014-2016 Monash University
 *
 * In the next iteration of the square drawing sketch, this version selects a random number of squares
 * and a random gap between them. From this it calculates the width of each square then draws the squares
 * using two nested for loops.
 *
 * A simple drop shadow is also drawn to give the illusion of depth.
 * 
 */

void setup() {
  size(800, 600);
  rectMode(CORNER);
  noStroke();
  frameRate(1);  // set the frame rate to 1 draw() call per second
}

void draw() {

  background(180); // clear the screen to grey
   
  int gridSize = (int) random(3, 12);   // select a random number of squares each frame
  int gap = (int) random(5, 50); // select a random gap between each square
  
  // calculate the size of each square for the given number of squares and gap between them
  float cellsizeX = ( width - (gridSize + 1) * gap  ) / (float)gridSize;
  float cellsizeY = ( height - (gridSize + 1) * gap  ) / (float)gridSize;
  // print out the size of each square
  println("cellsize = " + cellsizeX);
  
  // calculate shadow offset
  float offsetX = cellsizeX/16.0;
  float offsetY = cellsizeY/16.0; 
 


    for (int i=0; i<gridSize; i++) {
      for (int j=0; j<gridSize; j++) {

        fill(140, 180); // shadow
        rect(gap * (i+1) + cellsizeX * i + offsetX, gap * (j+1) + cellsizeY * j + offsetY, cellsizeX, cellsizeY);

        fill(247, 57, 57, 180); // rectangle
        rect(gap * (i+1) + cellsizeX * i, gap * (j+1) + cellsizeY * j, cellsizeX, cellsizeY);
      }
    }
} //end of draw 