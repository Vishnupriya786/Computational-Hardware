#include "dht.h"
#define dht_apin A0 
dht DHT;
void setup(){
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("Humidity Sensor and Motor Integration\n\n");
  pinMode(6, OUTPUT);
  delay(1000);//Wait before accessing Sensor
}//end "setup()"
void loop(){
  //Start of Program
    DHT.read11(dht_apin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("% ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature);
    Serial.println("C ");
    if(DHT.humidity < 55) {
      digitalWrite(6, LOW);
      Serial.println("Motor ON");
    }
    else if(DHT.humidity >= 65) {
      digitalWrite(6, HIGH);
      Serial.println("Motor OFF");
    }
    else {
      Serial.println("Motor in previous state");
    }
    delay(2500);
  
}
