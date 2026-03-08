float Kp = 0.08;
float Ki = 0.00;
float Kd = 0.50;

int lastError = 0;
int integral = 0;

int calculatePID(int currentPosition) {
  int error = 5500 - currentPosition;
  
  float P = error * Kp;
  
  integral = integral + error;
  float I = integral * Ki;
  
  float D = (error - lastError) * Kd;
  
  lastError = error;
  
  return (int)(P + I + D);
}