
#include "BluetoothSerial.h"
#include <Wire.h>               // I2C Library
#include "SparkFun_MMA8452Q.h"  //Accelerometer Library

BluetoothSerial SerialBT;

#define LED_BUILTIN 2
#define RegTemp 33
#define RECIVER A4

#define Rx2 16
#define Tx2 17

MMA8452Q accel;      // create instance of the MMA8452 class
float TempRawValue;  // a home for the Temp data
float VoltageOut;

float TempRegVIN;  // Temp sensor reading Voltage reg VIN 18v Litium to LM7805 to 5v ESP32
float TempK;
int HalVal = 0;

String data;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, Rx2, Tx2);

  SerialBT.begin("Esp Drone");

  pinMode(RegTemp, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("MMA8452Q Booting Up!");
  Wire.begin();
  digitalWrite(LED_BUILTIN, 0);
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    // while (1)
    //   ;
  }
  digitalWrite(LED_BUILTIN, 0);
}

void loop() {
  int x = analogRead(RECIVER);
  Serial.print("RECIVER");
  Serial.println(x);

  while (Serial2.available()) {
    Serial.print("INCOMING DATA");
    Serial.println(Serial2.readString());
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
      digitalWrite(LED_BUILTIN, 0);
    }
    if (SerialBT.read() == 0) {
      digitalWrite(LED_BUILTIN, 1);
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
    //  digitalWrite(LED_BUILTIN,0);
  } else {
    // digitalWrite(LED_BUILTIN,1);
  }
  if (accel.available()) {  // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    Serial.print("X");
    SerialBT.print("X");

    Serial.println(accel.getCalculatedX(), 2);
    SerialBT.println(accel.getCalculatedX(), 2);

    //Serial.print("\t");
    Serial.print("Y");
    SerialBT.print("Y");

    Serial.println(accel.getCalculatedY(), 2);
    SerialBT.println(accel.getCalculatedY(), 2);

    //Serial.print("\t");
    Serial.print("Z");
    SerialBT.print("Z");

    Serial.println(accel.getCalculatedZ(), 2);
    SerialBT.println(accel.getCalculatedZ(), 2);
  }
  delay(1000);
}
