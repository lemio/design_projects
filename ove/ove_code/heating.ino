boolean heatingButtonPressed() {
  return !digitalRead(HEATING_BUTTON_PIN);
}

void heatingBehaviour() {
  if (heatingButtonPressed()) {
    Serial.println("HEATING BUTTON PRESSED");
    int i = 0;
    playHeatingStartSound();
    while (i < 100) {
      light = light * 0.80 + 150.0 * 0.20;
      setLightDone(light);
      delay(10);
      i++;
    }
    i = 0;
    modeTimer = millis();
    float lastLight = light;
    while (modeTimer + 11 * 1000 > millis()) {
      light = 150 + sin(i * 0.04) * 100;
      if (lastLight > 150.0 && light < 150.0) {
        startHeatingSound();
      }
      if (lastLight < 150.0 && light > 150.0) {
        stopHeatingSound();
      }
      lastLight = light;
      setLightDone(light);
      delay(10);
      i++;
    }
    stopHeatingSound();
    delay(100);
    playDone();
    doneLightBehaviour();
  }
}
