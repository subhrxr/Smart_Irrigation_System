#include <Servo.h>
#include "WiFi.h"
#include <HTTPClient.h>

int servopin1 = 25;
int servopin2 = 26;
int servopin3 = 27;
Servo servo1;
Servo servo2;
Servo servo3;

int s1 = 34;
int s2 = 35;
int s3 = 33;
int s1val = 0;
int s2val = 0;
int s3val = 0;
int motor = 32;

void ConnectToWiFi()
{
 
  WiFi.mode(WIFI_STA);
  WiFi.begin("AndroidAPx", "00000000");
  Serial.print("Connecting to "); Serial.println("AndroidAPx");
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
 
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }
 
  Serial.print(F("Connected. My IP address is: "));
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ConnectToWiFi();
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(motor,OUTPUT);

  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servo3.attach(servopin3);

}

void loop() {
  // put your main code here, to run repeatedly:
  s1val = analogRead(s1);
  s2val = analogRead(s2);
  s3val = analogRead(s3);
  Serial.print("Moisture Sensor 1(port 34) = ");
  Serial.println(s1val);
  Serial.print("Moisture Sensor 2(port 35) = ");
  Serial.println(s2val);
  Serial.print("Moisture Sensor 3(port 33) = ");
  Serial.println(s3val);
  Serial.println();

  
  
  
  
  if((s1val>=3500)|| (s2val>=3500) || (s3val>=3500))
  {
    if(s1val>=3500)
    {
      servo1.write(90);
      delay(100);
    }

    if(s2val>=3500)
    {
     servo2.write(90);
     delay(100);
    }

    if(s3val>=3500)
    {
      servo3.write(90);
      delay(100);
    }

    
    digitalWrite(motor,HIGH);
    
    delay(100);
  }






  

if((s1val<=3000)|| (s2val<=3000) || (s3val<=3000))
  {
    if(s1val<=3000)
    {
      servo1.write(0);
      Serial.println(s1val);
      delay(100);
    }

    if(s2val<=3000)
    {
      servo2.write(0);
      delay(100);
    }

    if(s3val<=3000)
    {
     servo3.write(0);
      delay(100);
    }
    delay(100);
  }





  
  
  if((s1val<=3000)&&(s2val<=3000)&&(s3val<=3000))
  {
    digitalWrite(motor,LOW);
    delay(100);
  }





  

delay(400);
}
