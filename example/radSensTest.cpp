#include <Arduino.h>
#include <Wire.h>
#include "radSens1v2.h"

ClimateGuard_RadSens1v2 radSens(RS_DEFAULT_I2C_ADDRESS);

void setup() 
{
  Serial.begin(115200);  
  radSens.radSens_init();
  Serial.print("Chip id: 0x");
  Serial.println(radSens.getChipId(), HEX);
  Serial.print("Firmware version: ");
  Serial.println(radSens.getFirmwareVersion());
  Serial.print("HV generator state: ");
  Serial.println(radSens.getHVGeneratorState());

  Serial.println("-------------------------------------");
  Serial.println("Set Sensitivity example:\n");
  Serial.print("\t getSensitivity(): "); Serial.println(radSens.getSensitivity());
  Serial.println("\t setSensitivity(55)... ");

  radSens.setSensitivity(55);

  Serial.print("\t getSensitivity(): "); Serial.println(radSens.getSensitivity());
  Serial.println("\t setSensitivity(105)... ");

  radSens.setSensitivity(105);

  Serial.print("\t getSensitivity(): "); Serial.println(radSens.getSensitivity());
  Serial.println("\n-------------------------------------");
}

void loop(){
  Serial.print("Rad intensy dyanmic: ");
  Serial.println(radSens.getRadIntensyDyanmic());
  Serial.print("Rad intensy static: ");
  Serial.println(radSens.getRadIntensyStatic());
  delay(2000);
}
