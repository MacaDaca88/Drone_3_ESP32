
#include "ppm.h"

#define THROTTLE 5
#define ROLL 1
#define PITCH 6
#define YAW 4
#define SWITCH3WAY_1 3
#define SWITCH 2


const long interval = 50;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);

  ppm.begin(A0, false);
}

void loop() {
  Serial.begin(9600);
  unsigned long currentMillis = millis();
  digitalWrite(LED_BUILTIN, LOW);

  short throttle = ppm.read_channel(THROTTLE);
  short roll = ppm.read_channel(ROLL);
  short pitch = ppm.read_channel(PITCH);
  short yaw = ppm.read_channel(YAW);
  short switch3way_1 = ppm.read_channel(SWITCH3WAY_1);
  short Switch = ppm.read_channel(SWITCH);


  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.print("Throttle:");
    Serial.print(throttle);
    Serial.print(" ");
    Serial.print("Roll:");
    Serial.print(roll);
    Serial.print(" ");
    Serial.print("Pitch:");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.print("Yaw:");
    Serial.print(yaw);
    Serial.print(" ");
    Serial.print("Switch_3way_1:");
    Serial.print(switch3way_1);
    Serial.print(" ");
    Serial.print("Switch:");
    Serial.print(Switch);
    Serial.print(" ");
    Serial.println();
    Serial.flush();
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
