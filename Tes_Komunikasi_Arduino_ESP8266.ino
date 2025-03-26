
#include <SoftwareSerial.h>
SoftwareSerial Serial1(3, 2); // RX, TX 
char c;
void setup() {
  Serial.begin(9600);  
  Serial1.begin(9600);
  delay(100);
  Serial.println("Cek Komunikasi Arduino - ESP8266");
  Serial.println("Ketik AT kemudian klik Send");
}

void loop() {
  if (Serial1.available()){
  c=Serial1.read();
  Serial.write(c);
 }
 if(Serial.available()){
  c=Serial.read();
  Serial1.write(c);
 }
}
