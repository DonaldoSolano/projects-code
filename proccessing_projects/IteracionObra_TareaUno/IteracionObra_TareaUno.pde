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
  size(600, 600);
  rectMode(CORNER);
  noStroke();
  frameRate(1);  // set the frame rate to 1 draw() call per second
}

void draw() {

  background(180); // clear the screen to grey
float Color1= random(0,255);
float Color2= random(0,255);
float Color3= random(0,255);

  int gridSize = (int) 5;   // select a random number of squares each frame
  int gap = (int) random(5, 50); // select a random gap between each square

  // calculate the size of each square for the given number of squares and gap between them
  float cellsize = ( width - (gridSize + 1) * gap ) / (float)gridSize;

  // print out the size of each square
  println("cellsize = " + cellsize);

  // calculate shadow offset
  float offsetX = cellsize/16.0;
  float offsetY = cellsize/16.0; 

  for (int i=0; i<gridSize; i++) {
    for (int j=0; j<gridSize; j++) {
      int cambioColor=(int)random(5);
      if(cambioColor==1){
      
        fill(Color1,Color2,Color3,220);
      }
      else{ 
        fill(255,0,0,220);
        
      }
      int x = (int)random(0, 30);
      int y = (int)random(0, 30);


      
      rect(gap * (i+1) + cellsize * i + offsetX + x, gap * (j+1) + cellsize * j + offsetY + y, cellsize, cellsize);

      
      rect(gap * (i+1) + cellsize * i + x, gap * (j+1) + cellsize * j+ y, cellsize, cellsize);
    }
  }
} //end of draw 