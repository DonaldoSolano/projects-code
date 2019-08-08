int r=200;
void setup() {
  size(900, 900);
  background(255);
}
void draw() {
  stroke(0);

  line(450, 900, 450, 0);
  line(900,450 , 0, 450);
  noFill();
  ellipse(450, 450, 400, 400);
  
  translate(width/2, height/2);
  rotate(radians(180));
  stroke(255, 0, 0);
  line(r*cos(210), r*sin(radians(210)), r*cos(radians(330)), r*sin(radians(330)));
  line(r*cos(radians(90)), r*sin(radians(90)), r*cos(radians(330)), r*sin(radians(330)));
  line(r*cos(radians(90)), r*sin(radians(90)), r*cos(radians(210)), r*sin(radians(210)));
}