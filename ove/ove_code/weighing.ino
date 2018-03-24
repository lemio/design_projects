/*
This is the code for the moving average
*/
void measureScale(){
  mov = mov*0.9+0.1*analogRead(WEIGHT_ELEMENT_PIN);
  }
boolean isPowderBottle(){
     return !digitalRead(REED_SWITCH_PIN); 
}
/*
This is the code to adjust the 'raw' value from the sensor to a range from 0 (empty) - 255 (full)
*/
float convertBottle(int analogRawValue){
  
  }
float convertPowder(int analogRawValue){
  
  }
