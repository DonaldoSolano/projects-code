/*
 * Creative Coding
 * array with sin()
 * by Indae Hwang and Jon McCormack
 * Updated 2016
 * Copyright (c) 2014-2016 Monash University
 *
 * This program demonstrates the use of arrays.
 * It creates three arrays that store the y-position, speed and phase of some oscillating circles.
 * You can change the number of circles by changing the value of num in setup()
 * You can change the background colour by holding the left mouse button and dragging.
 * 
 */

int     noCircles;    // the number of items in the array (# of circles)
float[] y;      // y-position of each circle (fixed), contiene las alturas(posición con repecto al eje y) de cada una de las esferas.
float[] speed;  // speed of each circle, contiene la velocidad de cada esfera.
float[] phase;  // phase of each circle, contiene la posición con respecto al eje x.

float red = 120; //Valor para el color rojo..
float green = 120;// Valor para el color verde.
float blue = 120;// Valor para el color azul.

void setup() {
  size(500, 500); //Tamaño del lienzo.

  noCircles = 5;

  // allocate space for each array
  y = new float[noCircles];
  speed = new float[noCircles];
  phase = new float[noCircles]; 

  // calculate the vertical gap between each circle based on the total number of circles
  float gap = height / (noCircles + 1);

  //setup an initial value for each item in the array
  for (int i=0; i<noCircles; i++) {
    y[i] = gap * (i + 1);      // y is constant for each so can be calculated once
    speed[i] = random(10);//Genera los valores de velocidades para cada posición del arreglo.
    phase[i] = random(TWO_PI);//Genera los valores de alturas(eje y) para cada posición del arreglo.
  }
}


void draw() {
  background(red, green, blue);//El background al recibir estos tres argumentos altera su fondo como si fuera un RGB.


  for (int i=0; i<noCircles; i++) {
    // calculate the x-position of each ball based on the speed, phase and current frame
    float x = width/2 + sin(radians(frameCount*speed[i] ) + phase[i])* 10; 
    ellipse(x, y[i], 20, 20);
  }
  float interac=dist(mouseX, mouseY, pmouseX, pmouseY);
  if (interac>=10) {
    fill(255, 0, 0);
  } else
  {
    fill(0, 255, 0);
  }
}


// change the background colour if the mouse is dragged
void mouseDragged() {
  red = map(mouseX, 0, width, 0, 255);//Argumento 1 del background. Mapea el valor del mouseX entre 0 y el valor máximo del ancho, a valores entre 0 y 255.
  green = map(mouseY, 0, height, 0, 255);//Argumento 2 del background. Mapea el valor del mouseY entre 0 y el valor máximo del alto, a valores entre 0 y 255.
  blue = map(mouseX+mouseY, 0, width+height, 255, 0);//Argumento 3 del background. Mapea el valor del mouseX y mouseY entre 0 y el valor máximo del ancho y el alto, a valores entre 255 y 0.
}