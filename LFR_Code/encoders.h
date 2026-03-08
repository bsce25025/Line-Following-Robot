const int ENCODER_LEFT_A = 12;
const int ENCODER_RIGHT_A = 14;

volatile long leftTicks = 0;
volatile long rightTicks = 0;

void leftEncoderISR() {
  leftTicks++;
}

void rightEncoderISR() {
  rightTicks++;
}

void initEncoders() {
  pinMode(ENCODER_LEFT_A, INPUT_PULLUP);
  pinMode(ENCODER_RIGHT_A, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A), rightEncoderISR, RISING);
}