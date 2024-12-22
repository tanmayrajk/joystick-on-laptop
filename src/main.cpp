#include <Arduino.h>
#include <vector>
#include <Bounce2.h>

int X_PIN = A3;
int Y_PIN = A0;
int BTN = 19;

std::vector<int> prevBtnValues = {};

Bounce btnDebouncer = Bounce();

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(BTN, INPUT_PULLUP);
  btnDebouncer.attach(BTN);
  btnDebouncer.interval(50);
}

bool isWithinRange(double value, double min, double max) {
  return value > min && value < max;
};

float getVectorLength(float x, float y) {
  return sqrtf((x*x) + (y*y));
}

void loop() {
  btnDebouncer.update();

  float y_val = (analogRead(Y_PIN) / (4095.0/2)) - 1.0;
  if (isWithinRange(y_val, -0.12, 0)) {
    y_val = 0;
  }
  float x_val = (analogRead(X_PIN) / (4095.0/2)) - 1.0;
  if (isWithinRange(x_val, -0.12, 0)) {
    x_val = 0;
  }

  if (btnDebouncer.fell()) {
    Serial.println("click");
  }
  
  Serial.print(x_val);
  Serial.print(",");
  Serial.print(y_val);
  Serial.println();
}
