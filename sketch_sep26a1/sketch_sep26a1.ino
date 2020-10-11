
#include <OneWire.h>
#include <DallasTemperature.h>

/*-----( Declare Constants and Pin Numbers )-----*/
#define ONE_WIRE_BUS_PIN 7

OneWire oneWire(ONE_WIRE_BUS_PIN);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*-----( Declare Variables )-----*/
// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress Probe01 = { 0x28, 0xB1, 0x96, 0xD2, 0x1B, 0x19, 0x01, 0x88 };
DeviceAddress Probe02 = { 0x28, 0x53, 0xA6, 0x31, 0x1A, 0x19, 0x01, 0x21 };
DeviceAddress Probe03 = { 0x28, 0x5B, 0x94, 0x08, 0x1A, 0x19, 0x01, 0x5C };
DeviceAddress Probe04 = { 0x28, 0x07, 0x76, 0x01, 0x1C, 0x19, 0x01, 0x14 };
DeviceAddress Probe05 = { 0x28, 0x17, 0x66, 0x58, 0x1A, 0x19, 0x01, 0xA9 };


void setup()   /****** SETUP: RUNS ONCE ******/
{
  // start serial port to show results
  Serial.begin(9600);
  Serial.println(DALLASTEMPLIBVERSION);

  // Initialize the Temperature measurement library
  sensors.begin();

  pinMode(6, OUTPUT);

  // set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
  sensors.setResolution(Probe01, 10);
  sensors.setResolution(Probe02, 10);
  sensors.setResolution(Probe03, 10);
  sensors.setResolution(Probe04, 10);
  sensors.setResolution(Probe05, 10);

  digitalWrite(6, LOW);

}//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  delay(1000);
  Serial.println();

  sensors.requestTemperatures();

  float temp1 = getTemperature(Probe01);
  float temp2 = getTemperature(Probe02);
  float temp3 = getTemperature(Probe03);
  float temp4 = getTemperature(Probe04);
  float temp5 = getTemperature(Probe05);

  Serial.print("Sensor 1: ");
  Serial.println(temp1);
  Serial.print("Sensor 2: ");
  Serial.println(temp2);
  Serial.print("Sensor 3: ");
  Serial.println(temp3);
  Serial.print("Sensor 4: ");
  Serial.println(temp4);
  Serial.print("Sensor 5: ");
  Serial.println(temp5);

  if(temp1 < 25.5){
    digitalWrite(6, HIGH);
  }
  else {
    
    digitalWrite(6, LOW);
  }

}

float getTemperature(DeviceAddress deviceAddress){
  
  return sensors.getTempC(deviceAddress);
  
}
