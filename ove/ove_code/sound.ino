
int currentInc = 0;
void resetIncrease(){
  currentInc = 0;
  }

void initSoundPins(){
  for (int i=0;i<sizeof(weighingSoundPins);i++){
      digitalWrite(weighingSoundPins[i],HIGH);
      pinMode(weighingSoundPins[i],OUTPUT);
    }
    digitalWrite(doneSoundPin,HIGH);
    pinMode(doneSoundPin,OUTPUT);
    digitalWrite(startSoundPin,HIGH);
    pinMode(startSoundPin,OUTPUT);
    digitalWrite(heatingSoundPin,HIGH);
    pinMode(heatingSoundPin,OUTPUT);
    digitalWrite(heatingStartSoundPin,HIGH);
    pinMode(heatingStartSoundPin,OUTPUT);
  }
  void doResetTimer(){
  if ((resetTimer + 200) < millis()) {
    initSoundPins();
  }
  }
void playIncrease(int num){
  //Serial.print("num:");
  //Serial.println(num);
  if (num > currentInc){
    initSoundPins();
    resetTimer = millis();
    digitalWrite(weighingSoundPins[num],LOW);
    Serial.print(num);
    Serial.println("sound played");
    currentInc = num;
    }
  }
  void playHeatingStartSound(){
    digitalWrite(heatingStartSoundPin,LOW);
    delay(150);
    digitalWrite(heatingStartSoundPin,HIGH);
    }
void startHeatingSound(){
  
  digitalWrite(heatingSoundPin,LOW);
  }
void stopHeatingSound(){
  digitalWrite(heatingSoundPin,HIGH);
  }
void playDone(){
  initSoundPins();//MUTE ALL OTHER SOUNDS
   digitalWrite(doneSoundPin,LOW);
   delay(150);
   digitalWrite(doneSoundPin,HIGH);
   
}
boolean recognized = false;
void playRecognize(){
  if (! recognized){
  digitalWrite(startSoundPin,LOW);
   delay(150);
   digitalWrite(startSoundPin,HIGH);
    recognized = true;
  }
  //sfx.playTrack("START    .OGG");
  }
