 int lados,r,angulo;


void setup() {
  size(900, 900);
  background(255);
  lados=6;
  r=100;
  angulo=360/lados;
}
void draw() {
  stroke(0);

  line(450, 900, 450, 0);
  line(900, 450, 0, 450);
  translate(width/2, height/2);
  rotate(radians(180));
  stroke(255, 0, 0);
  for (int i=0; i<lados; i++) {
     line(r*cos(radians(angulo*i)),r*sin(radians(angulo*i)),r*cos(radians(angulo*(i+1))),r*sin(radians(angulo*(i+1))));
  }
}