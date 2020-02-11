# sht_7x for arduino
Repository for Sensirion humidity and temperature sensor support on Arduino

## Supported sensors:
- SHT71
- SHT75
## Installation

Download arduino-sht either via git or from the releases page and place it in
your Arduino/libraries directory. After restarting the Arduino IDE, you will see
the new SHTSensor menu items under libraries and examples.

## Integrating it into your sketch

Assuming you installed the library as described above, the following steps are
necessary:


1. Import the arduino-sht library: From the menu bar, select Sketch >Import Library > sht_7x_for_arduino
2. Create an instance of the `SHT_7x` class and pass SCK and DATA pins numbrs as augument to consructor (`SHT_7x sht(A3,A4);`)
3. In `setup()`, make sure to init the library with `sht.init()`
4. If you want to use the serial console, remember to initialize the Serial library with `Serial.begin(9600)`
5. Call `sht.readSample()` in the `loop()` function, which reads a temperature and humidity sample from the sensor
6. Use `sht.getHumidity()` and `sht.getTemperature()` to read the values the sensor


### Sample code
```c++
#include <sht_7x.h>

//create an instace of sensor for read from PB7 and PB7 in stm32 micoconroller

SHT_7x sht(PB6,PB7);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sht.init();

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Temperature: ");
  Serial.println(sht.getTemperature());
  Serial.print("Humidity: ");
  Serial.println(sht.getHumidity());


}

```
