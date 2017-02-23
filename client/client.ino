#include <LWiFi.h>
#include <LWiFiClient.h>
#include <LWiFiServer.h>
#include <LWiFiUdp.h>

void setup() {
  // put your setup code here, to run once:
  
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  delay(1000);
  LWiFi.begin();
  

  while (0 == LWiFi.connectWPA("Max's iPhone","mqxrimmer")) {
    delay(10);
  }
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.write("Hello there");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9, LOW);
  delay(1000);
  digitalWrite(9, HIGH);
  delay(1000);
}
