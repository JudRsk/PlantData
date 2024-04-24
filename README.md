# PlantData
Arduino project to record soil moisture content and intensity of ambient light data up to 5 plants. The humidity and temperature of the environment is also measured. The data is saved to an SD card. A time interval can be chosen that determines how often the data is saved. The LCD display shows the humidity and temperature of the environment. The OLED display shows the date the experiment started and how many intervals have passed. The green, yellow and red LEDs shows the light intensity in the environment of the plant. It is measured by an LDR sensor that is present in the soil of the plant. If the red led lights up, there is not a lot of light present, when the yellow led lights up, there is medium amount of light present and when the green led lights up, there is a lot of light present. The amount of moisture in the soil of each plant is represented by a 10 led segment bar. The amount of bars that are on, indicate the amount of moisture present in the soil. 

![ArduinoCircuit_plant](https://github.com/JudRsk/PlantData/assets/79409725/9d3b20d9-217b-42dd-98c5-362c4a9b3add)

Supplies:
- Arduino Mega 2560 Rev3
- 5x red led 5mm
- 5x yellow led 5mm
- 5x green led 5mm
- LCD 16x2
- IC 74HC595
- 100 nf capacitator
- 10k potentiometer
- 5x Grove led bar v2.0
- 5x soil moisture sensor
- 5x LDR sensor
- DHT11 humidity and temperature sensor
- SD card module
- 128X64 OLED wit i2c display module (not in figure)
- wires
