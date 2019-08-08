float puntos[];
void setup() {
  size(1280, 720);
  background(0);
  //curveMode(RADIUS);
}

void draw() {
  if (mousePressed) {
    noFill();
    stroke(255);
    strokeWeight(50);

    //CURVE:
    /*La función curve() recibe 8 argumentos float así:  
     -x1,y1(primeros dos argumentos): punto de control inicial de la curva. 
     -x2,y2(tercer y cuarto argumento): primer punto de la curva.
     -x3,y3(quinto y sexto argumento): segundo punto de la curva.
     -x4,y4(séptimo y octavo argumento): punto de control final de la curva.*/
    /*curve(70, 50, 100, 200, 68, 150, 741, 300);*/

    //VERTEX:
    /*La función vertex() recibe dos argumentos "x,y" y crea un vértice que se puede usar como guía para contruir algo a partir de este.*/
    /*beginShape(POINTS);
     vertex(30, 20);
     vertex(85, 20);
     vertex(85, 75);
     vertex(30, 75);
     endShape();*/

    //CURVEVERTEX:
    /*La funcion curveVertex() se usa para dibujar una curva entre dos puntos o más*/
    
    noFill();
    beginShape();
    curveVertex(84, 91);//punto de control inicial de la curva.
    curveVertex(84, 91);//primer punto.
    curveVertex(68, 19);//segundo punto.
    curveVertex(21, 17);//tercer punto.
    curveVertex(32, 100);//cuarto punto.
    curveVertex(32, 100);//punto de control final de la curva.
    endShape();
  }
} 