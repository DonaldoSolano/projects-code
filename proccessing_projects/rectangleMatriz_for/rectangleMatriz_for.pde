void setup() {
  size(1280, 720);
}
void draw() {

  for (int i=0; i<3; i++) {
  for(int j=0; j<3; j++){rect(150+(150*i),150+(150*j),100,100);}
  }
  /* for (int i=0; i<3; i++) {
   fill(255, 0, 0);
   rect(150+(150*i), 300, 100, 100);
   }
   for (int i=0; i<3; i++) {
   fill(255, 0, 0);
   rect(150+(150*i), 450, 100, 100);
   }*/
}