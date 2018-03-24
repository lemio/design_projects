

void doneLightBehaviour(){
  while (true) {
      light = light * 0.85;
      setLightDone(light);

      delay(10);
      if (light < 5.0) {
        while (true) {
          light = light * 1.15;
          if (light > 240.0) {
            while (true) {
              heatingBehaviour();
              if (analogRead(WEIGHT_ELEMENT_PIN) < IS_BOTTLE) {
                while(light >5.0){
                  light = light * 0.8;
                  setLightDone(light);
                  delay(10);
                  }
                asm volatile ("  jmp 0");
              }
              setLightDone(240);
              delay(10);
            };
          }
          setLightDone(light);
          delay(10);
        }
      }
    }
  }
  

void setLightWeighing(float val){
  //white balance
  
  float r = max(0,min(val,256)) * 0.780;
  float g = max(0,min(val,256)) * 0.99;
  float b = max(0,min(val,256)) * 0.56;
  
   float maxnum = (NUMPIXELS*0.5)*((r+g+b)/597.0);
    for(int i=0;i<NUMPIXELS/2;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    if (i<floor(maxnum)){
          /*
          int difference = maxnum-i;
          float num = (difference/maxnum)*0.8;*/
          float num = 0.8;
          int r1 = r*num;
          int g1 = g*num;
          int b1 = b*num;
          pixels.setPixelColor(12+i, pixels.Color(r1,g1,b1)); // Moderately bright green color.
          pixels.setPixelColor(12-i, pixels.Color(r1,g1,b1)); // Moderately bright green color.
      }else if (i==floor(maxnum)){
          /*
          int difference = maxnum-i;
          float num = (difference/maxnum)*0.8;*/
          float num = maxnum-i;
          int r1 = r*num;
          int g1 = g*num;
          int b1 = b*num;
          pixels.setPixelColor(12+i, pixels.Color(r1,g1,b1)); // Moderately bright green color.
          pixels.setPixelColor(12-i, pixels.Color(r1,g1,b1)); // Moderately bright green color.
      }else{
        float num = 0;
          int r1 = r*num;
          int g1 = g*num;
          int b1 = b*num;
          pixels.setPixelColor(12+i, pixels.Color(r1,g1,b1)); // Moderately bright green color.
          pixels.setPixelColor(12-i, pixels.Color(r1,g1,b1)); // Moderately bright green color.

        }



  }
      pixels.show(); // This sends the updated pixel color to the hardware
  }
 
void setLightDone(int val){
  float r = max(0,min(val,256)) * 0.780;
  float g = max(0,min(val,256)) * 0.99;
  float b = max(0,min(val,256)) * 0.56;
   float maxnum = NUMPIXELS*((r+g+b)/597.0);
    for(int i=0;i<NUMPIXELS/2;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255    
        pixels.setPixelColor(12+i, pixels.Color(r,g,b)); // Moderately bright green color.
        pixels.setPixelColor(12-i, pixels.Color(r,g,b)); // Moderately bright green color.
  }
      pixels.show(); // This sends the updated pixel color to the hardware
}
