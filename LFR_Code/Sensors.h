const int sensorPins[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 

const unsigned long TIMEOUT_US = 5000; 
unsigned long sensorValues[12]; // Stores the discharge time for each sensor

void initSensors() {
}

void readRawSensors() {
  bool done[12] = {false};
  int sensorsLeft = 12;

  for (int i = 0; i < 12; i++) {
    pinMode(sensorPins[i], OUTPUT);
    digitalWrite(sensorPins[i], HIGH);
  }
  delayMicroseconds(10); 

  for (int i = 0; i < 12; i++) {
    pinMode(sensorPins[i], INPUT);
  }
  unsigned long startTime = micros();

  while (sensorsLeft > 0) {
    unsigned long elapsed = micros() - startTime;
    
    if (elapsed >= TIMEOUT_US) {
      for (int i = 0; i < 12; i++) {
        if (!done[i]) sensorValues[i] = TIMEOUT_US;
      }
      break; 
    }

    for (int i = 0; i < 12; i++) {
      if (!done[i] && digitalRead(sensorPins[i]) == LOW) {
        sensorValues[i] = elapsed;
        done[i] = true;
        sensorsLeft--;
      }
    }
  }
}


int readLine() {
  readRawSensors();
  
  long weightedSum = 0;
  long totalSum = 0;
  
  for (int i = 0; i < 12; i++) {
    long lineStrength = TIMEOUT_US - sensorValues[i]; 
    
    if (lineStrength < 2000) lineStrength = 0; 
    
    weightedSum += (long)lineStrength * (i * 1000);
    totalSum += lineStrength;
  }

  if (totalSum == 0) return 5500; 

  return weightedSum / totalSum; 
}