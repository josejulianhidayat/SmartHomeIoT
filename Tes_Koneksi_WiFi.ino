#include "WiFiEsp.h"
#include "SoftwareSerial.h"
SoftwareSerial Serial1(3,2); // RX, TX
// Ganti dengan jaringan WiFi anda
char ssid[] = "ArdutechWiFi";           
char pass[] = "12345678";        
int status = WL_IDLE_STATUS;     

void setup()
{ 
  Serial.begin(9600);  
  Serial1.begin(9600); 
  WiFi.init(&Serial1);
 if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Modul WiFi ESP8266 tidak ditemukan.!");
    while (true);
  }
  while ( status != WL_CONNECTED) {
    Serial.print("Mencoba koneksi ke WiFi : ");
    Serial.println(ssid);    
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("Arduino terhubung ke WiFi");
}
//======================
void loop()
{
  
}
