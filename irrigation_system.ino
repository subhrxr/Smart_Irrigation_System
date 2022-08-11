#include "WiFi.h" 
#include <HTTPClient.h> 
int relay1 = 25; 
int relay2 = 26; 
int relay3 = 27; 
int s1 = 34; 
int s2 = 35; 
int s3 = 33; 
int s1val = 0; 
int s2val = 0; 
int s3val = 0; 
int motor = 32; 
bool s1on = false; 
bool s2on = false; 
bool s3on = false;

 
void ConnectToWiFi() { 
 WiFi.mode(WIFI_STA); 
 WiFi.begin("AndroidAPx", "00000000"); 
 Serial.print("Connecting to "); 
 Serial.println("AndroidAPx");
 uint8_t i = 0; 
 while (WiFi.status() != WL_CONNECTED) { 
 Serial.print('.'); 
 delay(500); 
 if ((++i % 16) == 0) { 
 Serial.println(F(" still trying to connect")); 
 } 
 } 
 Serial.print(F("Connected. My IP address is: ")); 
 Serial.println(WiFi.localIP()); 
} 


void setup() { 
 Serial.begin(9600); 
 ConnectToWiFi(); 
 pinMode(s1, INPUT); 
 pinMode(s2, INPUT); 
 pinMode(s3, INPUT); 
 pinMode(relay1, OUTPUT); 
 pinMode(relay2, OUTPUT); 
 pinMode(relay3, OUTPUT); 
 pinMode(motor, OUTPUT);
 delay(200); 
} 


void loop() { 
 s1val = analogRead(s1); 
 s2val = analogRead(s2); 
 s3val = analogRead(s3); 
 HTTPClient http; 
 HTTPClient http2;
 
 http.begin("http://smart-irrigation-tracker.herokuapp.com/api/v1/moisture-ping"); 
 http.addHeader("Content-Type", "application/json"); 
 http2.begin("http://smart-irrigation-tracker.herokuapp.com/api/v1/power-event"); 
 http2.addHeader("Content-Type", "application/json"); 
 http.POST("{\"sensorId\":1,\"value\":" + String(s1val) + "}"); 
 http.POST("{\"sensorId\":2,\"value\":" + String(s2val) + "}"); 
 http.POST("{\"sensorId\":3,\"value\":" + String(s3val) + "}");

 
 if ((s1val >= 3500) || (s2val >= 3500) || (s3val >= 3500)) { 


 if (s1val >= 3500 && !s1on) { 
 s1on = true; 
 digitalWrite(relay1, LOW); 
 http2.POST("{\"motorId\":1,\"event\":\"on\"}"); 
 delay(100); 
 }


if (s2val >= 3500 && !s2on) { 
 s2on = true; 
 digitalWrite(relay2, LOW); 
 http2.POST("{\"motorId\":2,\"event\":\"on\"}"); 
 delay(100); 
 }


 if (s3val >= 3500 && !s3on) { 
 s3on = true; 
 digitalWrite(relay3, LOW); 
 http2.POST("{\"motorId\":3,\"event\":\"on\"}"); 
 delay(100); 
 }


 digitalWrite(motor, HIGH); 
 Serial.println("motor : on"); 
 delay(100); 
 } 


 if ((s1val <= 3000) && (s2val <= 3000) && (s3val <= 3000)) { 
 digitalWrite(motor, LOW); 
 Serial.println("motor : off"); 
 delay(3000); 
 }


if ((s1val <= 3000) || (s2val <= 3000) || (s3val <= 3000)) { 


 if (s1val <= 3000 && s1on) { 
 s1on = false; 
 digitalWrite(relay1, HIGH); 
 http2.POST("{\"motorId\":1,\"event\":\"off\"}"); 
 delay(100); 
 } 


 if (s2val <= 3000 && s2on) { 
 s2on = false; 
 digitalWrite(relay2, HIGH); 
 http2.POST("{\"motorId\":2,\"event\":\"off\"}"); 
 delay(100); 
 } 


 if (s3val <= 3000 && s3on) { 
 s3on = false; 
 digitalWrite(relay3, HIGH); 
 http2.POST("{\"motorId\":3,\"event\":\"off\"}"); 
 delay(100); 
 } 


 delay(100); 
 } 


 delay(2000); 
}
