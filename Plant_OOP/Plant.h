#ifndef MY_PLANT_H
#define MY_PLANT_H
#include <Arduino.h>

class Plant {
  
  private:

    byte MOISTpin;
    byte LDRpin;
    int GREENpin;
    int YELLOWpin;
    int REDpin;

  public:
    Plant(byte MOISTpin, byte LDRpin, int GREENpin, int YELLOWpin, int REDpin);
    int findMoistValue();
    int findLDRvalue();
    byte getMoistPin();
    byte getLDRpin();
    int getGreenPin();
    int getYellowPin();
    int getRedPin();

};
#endif