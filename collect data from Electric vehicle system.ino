// Voltage slave
#include <Wire.h>
#define sensorIp A0
void setup()
{
  Serial.begin(9600);
  Wire.begin(3);
  Wire.onRequest(DataRequest);
}
void loop()
{
 //empty
}
void DataRequest()
{
  int sensorVal = analogRead(sensorIp);
  Serial.println(sensorVal);
  int voltage=map(sensorVal,0,511,0,9);
  Serial.print("Voltage: ");
  Serial.println(voltage);
  Wire.write(voltage);
}

// Motor Slave:
#include <Wire.h>
int a;
void setup()
{
  Wire.begin(8);                // join i2c bus with address 
  Wire.onRequest(requestEvent); // register event
}
void loop()
{
  delay(100);
}

void requestEvent()
  
{
  a=(map(analogRead(A0), 0, 1023, 0, 255));
  Wire.write(a); 
  
}

// LCD Slave:
#include<LiquidCrystal.h>
#include <Wire.h>

int joystick_x;
int joystick_y,voltage;
int motor_rpm;
int x,y,z,z1,x1;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
 lcd.begin(16,2);
  Wire.begin(4);                // join i2c bus with address #4
  Serial.begin(9600);
}

void loop()
{
    Wire.onReceive(receiveEvent); // register event

  joystick_x = map(y,0,255,0,1024); // receive byte as a character
    joystick_y = map(z,0,255,0,1024);
    motor_rpm = map(x,0,255,0,10000);
   
    Serial.println(joystick_x);
    Serial.println(joystick_y);
    Serial.println(motor_rpm);
   delay(100);
   //print to LCD
  
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motor RPM");
  lcd.setCursor(0, 1);
  lcd.print(motor_rpm);
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Joystick X");
  lcd.setCursor(0, 1);
  lcd.print(joystick_x);
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Joystick Y");
  lcd.setCursor(0, 1);
  lcd.print(joystick_y);
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Battery Voltage");
  lcd.setCursor(0, 1);
  lcd.print(z1);
  delay(500);
  
  
  
 
  }


void receiveEvent(int howMany)
{
  
       x = Wire.read();
       y = Wire.read(); 
       z = Wire.read(); 
       z1 = Wire.read();
        
     Serial.println(x); 
      Serial.println(y); 
      Serial.println(z); 
  Serial.println(z1);
      
}

// Joystick Slave:

#include <Wire.h>
const int X_pin = 0;
const int Y_pin = 1;
void setup()
{
  pinMode(X_pin,INPUT);
  pinMode(Y_pin,INPUT);
  Wire.begin(9);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}
void loop()
{
  delay(100);
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write(analogRead(X_pin)); 
  Wire.write(analogRead(Y_pin));// respond with message of 6 bytes
  // as expected by master
}

// Master:

#include <Wire.h>
int motor;
int X_pin;
int Y_pin;
byte X,Y,c,h;

void setup() {
  Wire.begin();        
  Serial.begin(9600);  
}
void loop() {
  
  //here
  
  
  Wire.requestFrom(8, 4);    
  if (Wire.available()) { 
    c = Wire.read(); 
    motor=map(c,0,255,0,9999);
    Serial.print(motor);     
    Serial.println(" rpm ");
  }
  delay(500);
  Wire.requestFrom(9, 4);    
  if (Wire.available()) { 
    X= Wire.read(); 
    Y= Wire.read(); 
    X_pin=map(X,0,255,0,1023);
    Y_pin=map(Y,0,255,0,1023);
    Serial.print("X-os : ");
    Serial.print(X_pin);
    Serial.print(" - ");
    Serial.print("Y-os : ");
    Serial.println(Y_pin);
    
  }
  delay(500);
  
   Wire.requestFrom(3, 2);   
  if (Wire.available()) { 
    h = Wire.read(); 
    Serial.print(" Battery voltage: ");
    Serial.println(h);     
  }
  delay(500);
   
   
   Wire.beginTransmission(4);     
   Wire.write(c);
   Wire.write(X);
   Wire.write(Y);
   Wire.write(h);
   Wire.endTransmission();
  
  delay(500);
 
  
 
}
