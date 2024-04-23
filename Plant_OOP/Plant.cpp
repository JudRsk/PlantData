#include "Plant.h"
Plant::Plant(byte MOISTpin, byte LDRpin, int GREENpin, int YELLOWpin, int REDpin) {
  this->MOISTpin = MOISTpin;
  this->LDRpin = LDRpin;
  this->GREENpin = GREENpin;
  this->YELLOWpin = YELLOWpin;
  this->REDpin = REDpin;
}
int Plant::findMoistValue() {
  return analogRead(MOISTpin);
}
int Plant::findLDRvalue() {
  return analogRead(LDRpin);
}

byte Plant::getMoistPin() {
  return MOISTpin;
}

byte Plant::getLDRpin() {
  return LDRpin;
}

int Plant::getGreenPin(){
  return GREENpin;
}
int Plant::getYellowPin(){
  return YELLOWpin;
}
int Plant::getRedPin(){
  return REDpin;
}


