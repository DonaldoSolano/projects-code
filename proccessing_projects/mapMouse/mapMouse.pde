/*
 * Creative Coding
 * using map() to map mouse co-ordinates to background colour 
 * by Indae Hwang
 * Updated 2016
 * Copyright (c) 2014-2016 Monash University
 *
 * This program allows you to change the background color.
 * Press and hold 'left mouse button' to change color.
 * 
 */

float red;
float green;
float blue;


void setup() {
  size(500, 500);// Tamaño del lienzo.

  // initialise the colour variables
  red = 0;
  blue = 0;
  green = 0;
}


void draw() {
  background(red, green, blue); //El background al recibir estos tres argumentos altera su fondo como si fuera un RGB.

  if (mousePressed) {
    red = map(mouseX, 0, width, 0, 255);//Argumento 1 del background. Mapea el valor del mouseX entre 0 y el valor máximo del ancho, a valores entre 0 y 255.
    green = map(mouseY, 0, height, 0, 255);//Argumento 2 del background. Mapea el valor del mouseY entre 0 y el valor máximo del alto, a valores entre 0 y 255.
    blue = map(mouseX+mouseY, 0, width+height, 255, 0);//Argumento 3 del background. Mapea el valor del mouseX y mouseY entre 0 y el valor máximo del ancho y el alto, a valores entre 255 y 0.
    
    println("red: "+red+", green: "+green+", blue: "+blue);//Muestra el valor entre 0 y 255 de cada color argumento que recibe el background.
    
  }
}