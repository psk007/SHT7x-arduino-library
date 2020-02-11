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
