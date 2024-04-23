#include <LiquidCrystal_74HC595.h>
#include <dht.h>
#include <SD.h>
#include <SPI.h>
#include <ListLib.h>
#include "Plant.h"
#include <U8g2lib.h>
#include <Wire.h>
#include <Grove_LED_Bar.h>

//data that can be changed-----
String current_date = "1204_";          //this need to be short because sd reader can only accept 8 char
const char full_date[] = "04/12/2023";  //for oled display
const int interval = 2;               //range
const int amount_plants = 5;
//MOISTpin; LDRpin; GREENpin; YELLOWpin; REDpin; LED_Bar;
Grove_LED_Bar bar_1(31,30, 0, LED_BAR_10);
Plant plant_1(A0, A1, 34, 35, 36);
Grove_LED_Bar bar_2(29,28, 0, LED_BAR_10);
Plant plant_2(A2, A3, 37, 38, 39);
Grove_LED_Bar bar_3(27,26, 0, LED_BAR_10);
Plant plant_3(A4, A5, 40, 41, 42);
Grove_LED_Bar bar_4(25,24, 0, LED_BAR_10);
Plant plant_4(A6, A7, 43, 44, 45);
Grove_LED_Bar bar_5(23,22, 0, LED_BAR_10);
Plant plant_5(A8, A9, 46, 47, 48);

Plant plant_list[5] = { plant_1, plant_2, plant_3, plant_4, plant_5 };
Grove_LED_Bar bar_list[5] = {bar_1, bar_2, bar_3, bar_4, bar_5};
//-----------------------------

const int ds = 2, sh = 32, st = 33, RS = 1, E = 3, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
LiquidCrystal_74HC595 lcd(ds, st, sh, RS, E, D4, D5, D6, D7);

const int DHTpin = 49;
dht dht;
float temperature;
float humidity;

int interval_time = 0;    //how many minutes have passed
int interval_number = 1;  //how many intervals have passed

//SD card------------
const int SDpin = 53;
//-------------------

String file_list_names[amount_plants];

unsigned long timePassed;

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

char second_int[1];
char third_int[1];

void setup() {
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows
  Serial.begin(9600);

  int readData = dht.read11(DHTpin);
  temperature = dht.temperature;  //read tempearture in degree C
  humidity = dht.humidity;        //read humidity %

  pinMode(SDpin, OUTPUT);                             // chip select pin is set as OUTPUT
  if (!SD.begin(SDpin)) {                             // Initialize SD card
    Serial.println("Could not initialize SD card.");  // if return value is false, something went wrong.
  }

  for (Grove_LED_Bar bar: bar_list) {
    bar.begin();
  }

  for (int i = 0; i < amount_plants; i++) {
    pinMode(plant_list[i].getGreenPin(), OUTPUT);
    pinMode(plant_list[i].getYellowPin(), OUTPUT);
    pinMode(plant_list[i].getRedPin(), OUTPUT);
    pinMode(plant_list[i].getLDRpin(), INPUT);
    segment_leds_on(plant_list[i], bar_list[i]);
    LDR_leds_on(plant_list[i]);
  }

  //create files-------------------------
  String txt = ".txt";
  int y = 0;
  for (int i = 0; i < amount_plants; i++) {
    String string_1 = current_date + (i + 1);
    file_list_names[i] = string_1 + txt;
  }
  for (String name : file_list_names) {
    File file = SD.open(name, FILE_WRITE);
    file.println("time\ttem(C)\thum(%)\tmoist\tlight");
    file.print(interval_time);
    file.print("\t");
    file.print(temperature);
    file.print("\t");
    file.print(humidity);
    file.print("\t");
    file.print(plant_list[y].findMoistValue());
    file.print("\t");
    file.print(plant_list[y].findLDRvalue());
    file.println();
    file.close();
    y += 1;
  }
  //-------------------------------------
  interval_time = interval;
  u8g2.begin();
  //--------------------------------------
}

void loop() {

  int readData = dht.read11(DHTpin);
  temperature = dht.temperature;  //read tempearture in degree C
  humidity = dht.humidity;        //read humidity %

  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.print(humidity);

  //to get text on OLED------------------------
  char first_line[23] = "Start date: ";
  strcat(first_line, full_date);

  char second_line[20] = "Interval: ";
  const char second_min[] = " minutes";
  itoa(interval, second_int, 10);
  strcat(second_line, second_int);
  strcat(second_line, second_min);

  char third_line[20] = "Interval number: ";
  itoa(interval_number, third_int, 10);
  strcat(third_line, third_int);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_squeezed_b7_tr);
    u8g2.drawStr(4, 10, first_line);
    u8g2.drawStr(4, 30, second_line);
    u8g2.drawStr(4, 40, third_line);

  } while (u8g2.nextPage());
  //-----------------------------------------------

  timePassed = millis();


  //write to file------------------
  if (timePassed >= interval_time * (unsigned long)60000) {  //in minutes
    interval_number += 1;
    int i = 0;
    for (String name : file_list_names) {
      File file = SD.open(name, FILE_WRITE);
      if (file) {
        Serial.println("works");
        file.print(interval_time);
        file.print("\t");
        file.print(temperature);
        file.print("\t");
        file.print(humidity);
        file.print("\t");
        file.print(plant_list[i].findMoistValue());
        file.print("\t");
        file.print(plant_list[i].findLDRvalue());
        file.println();
        file.close();
      }
      i += 1;
    }
    interval_time += interval;
  }
  for (int i = 0; i < amount_plants; i++) {
    segment_leds_on(plant_list[i], bar_list[i]);
    LDR_leds_on(plant_list[i]);
  }
}

//for segment bar
void segment_leds_on(Plant plant, Grove_LED_Bar bar) {
  int i = map(plant.findMoistValue(), 390, 800, 10, 0);
  for (int y = 0; y <= i; y++) {
    bar.setLevel(i);
    delay(10);
  }
}

void LDR_leds_on(Plant plant) {
  if (plant.findLDRvalue() < 341) {
    digitalWrite(plant.getRedPin(), HIGH);
    digitalWrite(plant.getGreenPin(), LOW);
    digitalWrite(plant.getYellowPin(), LOW);
  } else if (plant.findLDRvalue() >= 333 && plant.findLDRvalue() < 682) {
    digitalWrite(plant.getYellowPin(), HIGH);
    digitalWrite(plant.getGreenPin(), LOW);
    digitalWrite(plant.getRedPin(), LOW);
  } else {
    digitalWrite(plant.getGreenPin(), HIGH);
    digitalWrite(plant.getYellowPin(), LOW);
    digitalWrite(plant.getRedPin(), LOW);
  }
}
