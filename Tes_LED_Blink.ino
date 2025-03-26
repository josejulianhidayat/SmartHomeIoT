
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH); // LED on 
  delay(1000);            // tunggu 1 detik
  digitalWrite(13, LOW);  // LED off 
  delay(1000);            // tunggu 1 detik
}

