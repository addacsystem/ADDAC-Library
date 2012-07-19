/*he setup function is only called only once, 
usually is here that you give values to variables.*/
void setup(){
  //define the serial speed to communicate with your computer
  Serial.begin(115200);
}

/*the loop function, as it name suggests is a loop, 
 when the compiler reaches here it enter in a loop*/
void loop(){
  Serial.println("HELLO WORLD");
}


