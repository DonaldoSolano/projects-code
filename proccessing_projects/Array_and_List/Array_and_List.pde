/*
 * Creative Coding
 * Foldout 01: Arrays and Lists
 * Updated 2016
 * by Indae Hwang and Jon McCormack
 * Copyright (c) 2014-2016 Monash University
 *
 * This program introduces the array and list collections
 * See the foldout associated with this sketch for more details
 * 
 */

// array declaration
float[] grayValueForArray;

int columns;
color uno= color(255, 0, 0), dos=color(0, 0, 235), tres=color(145, 178, 54), cuatro=color(78, 69, 123), cinco=color(200, 12, 125), seis=color(58, 10, 200);
color[] arregloColor= {uno, dos, tres, cuatro, cinco, seis};
// list declaration
FloatList grayValueForList;

float spacing;

void setup() {
  size(400, 300);

  columns = 5;  // number of columns of circles
  float brightnessStep = 255/float(columns);
  spacing = (width-100)/float(columns-1);  
  //Initialise Array 
  grayValueForArray = new float[columns];

  //Input values into the Array
  /*for (int i=0; i<4; i++) {
   arregloColor[i] = uno;
   }*/

  //Initialise list
  grayValueForList = new FloatList();

  //Input values into the List
}


  void draw() {
    background(255);
    noStroke();

    //Use values from the array 
    for (int i=0; i<5; i++) {
      fill( arregloColor[i] );
      ellipse(50+spacing*i, 100, 40, 40);
    }

    //Use values from the list 
    for (int i=0; i<5; i++) {
      fill( arregloColor[i] );
      ellipse(50+spacing*i, 200, 40, 40);
    }
  }