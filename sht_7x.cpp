#include "Arduino.h"
#include "sht_7x.h"

void SHT_7x::clock(){
      digitalWrite(this->sck,HIGH);
      delayMicroseconds(10);
      digitalWrite(this->sck,LOW);
      
}
void SHT_7x::start(){
    digitalWrite(this->sck,HIGH);
    delayMicroseconds(10);
    digitalWrite(this->sda,LOW);
    delayMicroseconds(10);
    digitalWrite(this->sck,LOW);
    delayMicroseconds(10);
    digitalWrite(this->sck,HIGH);
    delayMicroseconds(10);
    digitalWrite(this->sda,HIGH);
    delayMicroseconds(10);
    digitalWrite(this->sck,LOW);
    delayMicroseconds(10);
}

bool SHT_7x::sendCommand(uint8_t sh_cmd){
    uint8_t i;
    bool ret;
    this->start();
    for(i=128; i>=1; i = i>>1){
        digitalWrite(this->sda, i & sh_cmd);
        this->clock();
    }
    pinMode(this->sda,INPUT);
    ret = !digitalRead(this->sda);
    this->clock();
    return ret;
}


uint16_t SHT_7x::getReadout(){
        
    uint8_t dataH=0, dataL=0, CRC=0;
    int i;
    while(digitalRead(this->sda));
    for(i=7; i>=0; i--){
        dataH |= (digitalRead(this->sda) << i);
        this->clock();
    }
    //ack
    pinMode(this->sda,OUTPUT);
    digitalWrite(this->sda,LOW);
    this->clock();
    pinMode(this->sda,INPUT);
    for(i=7; i>=0; i--){
        dataL |= (digitalRead(this->sda) << i);
		this->clock();
    }
    
    //ack and terminate connection
    pinMode(this->sda,OUTPUT);
    digitalWrite(this->sda,HIGH);
    this->clock();

    return (uint16_t)dataH << 8 | (uint16_t) dataL; 
}

 

SHT_7x::SHT_7x(uint8_t sck_pin, uint8_t data_pin){
    this->sck = sck_pin;
    this->sda = data_pin;
}
    
    
bool SHT_7x::setAccuracy(Accuracy a){
    
    bool temp1,temp2;
    if(a== Accuracy::low){
        temp1 = this->sendCommand(6);
        temp2 = this->sendCommand(1);
    }else{
        temp1 = this->sendCommand(6);
        temp2 = this->sendCommand(0);
    }
    if(temp1 && temp2){
        this-> accuracy = a;
        return true;
    }else {
        return false;
    }
}

    
void SHT_7x::init(){
    Serial.print("init");
    pinMode(this->sck,OUTPUT);
    pinMode(this->sda,OUTPUT);
    digitalWrite(this->sda,HIGH);
    
}

float SHT_7x::getHumidity(){
	
    if (!this->sendCommand(5)){
        return 0;
    }
    uint16_t result = this->getReadout();

    if (this->accuracy == Accuracy::low ){
        return (float) (-2.0468 + 0.5872 * result + (-4.0845E-4) * pow(result,2));
    }else{
        return (float) (-2.0468 + 0.0367 * result +(-1.5955E-6 )* pow(result,2));
    }
    
}

float SHT_7x::getTemperature(){
    uint16_t result=0;

    if (!this->sendCommand(3)){
        return 0;
    }
    result = this->getReadout();
   
    if (this->accuracy == Accuracy::low ){
        return (float) (-39.7 + 0.04 * result);
    }else{
        return (float) (-39.7+ 0.01 * result);
    }
      
} 
