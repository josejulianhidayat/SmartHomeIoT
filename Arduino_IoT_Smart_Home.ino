 //---GANTI DEVICE NAME
 //---GANTI TOKEN BLYNK ANDA
#define BLYNK_TEMPLATE_ID "TMPL6i1QRdoTI"
#define BLYNK_TEMPLATE_NAME "SmartGasDetected"
#define BLYNK_AUTH_TOKEN "ST9z9_kaLOVRJkWvmX3X8AkTtmhAWlvZ" 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "Universitas Pelita Bangsa New";
char pass[] = "megah123";
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTTYPE DHT11

SoftwareSerial EspSerial(3,2); // RX, TX
ESP8266 wifi(&EspSerial);
char auth[] = BLYNK_AUTH_TOKEN;

#define DHTPIN 4
#define RL1 A0 
#define RL2 A1
#define RL3 A2
#define RL4 A3
#define LT 9
#define SW 10
#define bell 11
#define MQ2_SENSOR 12

DHT dht(DHTPIN, DHTTYPE);
int MQ2_SENSOR_Value = 0;
boolean st,fg,fu;
int humi, temp,i; 

//==============================
void cek_DHT11(){
  humi = dht.readHumidity();  
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)) {
    Serial.println("DHT11 tidak terbaca... !");
    return;
  }
  else{   
    Serial.print("Temp=");
    Serial.println(temp);
    Serial.print("Humi=");
    Serial.println(humi);
    Blynk.virtualWrite(V0, temp);  
    Blynk.virtualWrite(V1, humi);  
  }  
}
//==============================
BLYNK_WRITE(V2)//RL1
{ 
  int value1 = param.asInt();
  digitalWrite(RL1,!value1);  
}
//==============================
BLYNK_WRITE(V3)//RL2
{ 
  int value2 = param.asInt();
  digitalWrite(RL2,!value2);  
}
//==============================
BLYNK_WRITE(V4)//RL3
{ 
  int value3 = param.asInt();
  digitalWrite(RL3,!value3);  
}
//==============================
BLYNK_WRITE(V5)//RL4
{ 
  int value4 = param.asInt();
  digitalWrite(RL4,!value4);  
}
//==============================
BLYNK_WRITE(V6)//Bright Lampu 4
{ 
  int value5 = param.asInt();
  analogWrite(LT,value5);  
}
//==============================
BLYNK_WRITE(V7)//Bell
{ 
  int value6 = param.asInt();
  digitalWrite(bell,value6);  
}
//==============================
void cek_SW(){  
    if(digitalRead(SW)==LOW){
      Blynk.logEvent("awas", "Ada pencuri...");
      Serial.println("Sensor thief ON...");
      delay(500);
    }
}
//==============================
void cekSensorGas(){
   MQ2_SENSOR_Value = digitalRead(MQ2_SENSOR);
    if ((MQ2_SENSOR_Value==0)&&(fg==0)) 
       { 
         Serial.println("Gas  bocorterdeteksi");
         Blynk.logEvent("awas", "Gas bocor terdeteksi!");
         fg=1;         
         delay(1000);
        }
     else if((MQ2_SENSOR_Value==1)&&(fg==1)) 
       {                
        fg=0;
        delay(1000);
       }
 }
 //==============================================

void setup(){ 
  Serial.begin(9600); 
  EspSerial.begin(9600);
  pinMode(SW,INPUT_PULLUP);
  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);
  pinMode(RL4, OUTPUT);
  pinMode(LT, OUTPUT);
  pinMode(bell, OUTPUT);  
  pinMode(MQ2_SENSOR, INPUT);
  digitalWrite(RL1,HIGH);
  digitalWrite(RL2,HIGH);
  digitalWrite(RL3,HIGH);
  digitalWrite(RL4,HIGH);
  delay(10);  
  Blynk.begin(auth, wifi, ssid, pass);   
  delay(1000);  
  dht.begin();
}
//===============================
void loop(){
  cekSensorGas();
  cek_SW();
  cek_DHT11();
  Blynk.run(); 
  delay(200);
}
