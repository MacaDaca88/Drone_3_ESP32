#include "BluetoothSerial.h"
#include <Wire.h>
#include "SparkFun_MMA8452Q.h"

BluetoothSerial SerialBT;

#define LED_BUILTIN 2
#define RegTemp 33
#define RECEIVER 19

#define Rx2 16
#define Tx2 17

MMA8452Q accel;
float TempRawValue;
float VoltageOut;

float TempRegVIN;
float TempK;
int HalVal = 0;

String data;
String dataNano;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, Rx2, Tx2);
  SerialBT.begin("Esp Drone");

  pinMode(RegTemp, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("MMA8452Q Booting Up!");
  Wire.begin();
  digitalWrite(LED_BUILTIN, LOW);
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  int x = analogRead(RECEIVER);
  Serial.print("RECIVER");
  Serial.println(x);
  /*if (Serial2.readString().toInt() >= 1900) {
    Serial.println("TESTING");
    delay(2000);
  }
*/

  while (Serial2.available()) {
    char a = Serial2.read();
    if (a != -1) {
      dataNano += a;
      if (a == '\n') {
        Serial.print("INCOMING DATA");
        Serial.println(dataNano);
        dataNano = "";
        Serial2.end();
        break;
        
      }
    }
  }

  while (SerialBT.available()) {
    char c = SerialBT.read();
    if (c != -1) {
      data += c;
      if (c == '\n') {
        Serial.println(data);
        SerialBT.println(data);
        data = "";
        break;
      }
    }
    if (SerialBT.read() == 1) {
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (SerialBT.read() == 0) {
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }

  HalVal = hallRead();

  TempRawValue = analogRead(RegTemp);
  VoltageOut = (TempRawValue / 1024) * 5000;
  TempK = VoltageOut / 10;
  TempRegVIN = TempK - 273.15;

  Serial.print("Magnetic Field  == ");
  SerialBT.print("Magnetic Field  == ");
  Serial.println(HalVal);
  SerialBT.println(HalVal);

  Serial.print("TempRawValue  = ");
  SerialBT.print("TempRawValue  = ");
  Serial.println(TempRawValue);
  SerialBT.println(TempRawValue);

  Serial.print("TempRegVIN  = ");
  SerialBT.print("TempRegVIN  = ");
  Serial.print(TempRegVIN);
  SerialBT.print(TempRegVIN);
  Serial.println("(C)");
  SerialBT.println("(C)");

  Serial.print("VoltageOut  = ");
  SerialBT.print("VoltageOut  = ");
  Serial.print(VoltageOut);
  SerialBT.print(VoltageOut);
  Serial.println("(mV)");
  SerialBT.println("(mV)");

  if (HalVal >= 20) {
    // digitalWrite(LED_BUILTIN,LOW);
  } else {
    // digitalWrite(LED_BUILTIN,HIGH);
  }

  if (accel.available()) {
    Serial.print("X");
    SerialBT.print("X");

    Serial.println(accel.getCalculatedX(), 2);
    SerialBT.println(accel.getCalculatedX(), 2);

    Serial.print("Y");
    SerialBT.print("Y");

    Serial.println(accel.getCalculatedY(), 2);
    SerialBT.println(accel.getCalculatedY(), 2);

    Serial.print("Z");
    SerialBT.print("Z");

    Serial.println(accel.getCalculatedZ(), 2);
    SerialBT.println(accel.getCalculatedZ(), 2);
  }
}
