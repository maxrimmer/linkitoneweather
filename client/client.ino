#include <LWiFi.h>
#include <LWiFiClient.h>
#include <LWiFiServer.h>
#include <LWiFiUdp.h>

#define WIFI_AP "Max's iPhone"
#define WIFI_PASSWORD "mqxrimmer" 
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP. 
#define SITE_URL "anderledes.net" 

LWiFiClient c;
boolean disconnectedMsg = false;
const int B=4275;                 // B value of the thermistor
const int R0 = 100000;            // R0 = 100k


void setup() {
  // put your setup code here, to run once:
  // LED to test if the connection is up
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);


  // Temperature sensor
  pinMode(A1, INPUT);

  
  LWiFi.begin();
  
  Serial.begin(115200);
  Serial.println("Connection to AP");
  while (0 == LWiFi.connectWPA("Max's iPhone","mqxrimmer")) {
    delay(((((((100)))))));
  }
  
  
  Serial.write("Hello there");


  Serial.println("Connecting to the interweb");
  while (0 == c.connect(SITE_URL, 80)) {
    Serial.println("Re-connecting to website");
    delay(1000);
  }

  Serial.println("send HTTP GET request");
  c.println("GET /dev/index.php?test=hello HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Connection: close");
  c.println();

    Serial.println("waiting HTTP response:");
    while (!c.available())
    {
      delay(100);
    }

  while (c)
    {
      int v = c.read();
      if (v != -1)
      {
        Serial.print((char)v);
      }
      else
      {
        Serial.println("no more content, disconnect");
        c.stop();
        while (1)
        {
          delay(1);
        }
      }
  }

      if (!disconnectedMsg)
      {
         Serial.println("disconnected by server");
          disconnectedMsg = true;
       }
        delay(500);
      
    
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9, LOW);
  delay(100);
  digitalWrite(9, HIGH);
  delay(100);

    int a = analogRead(A1);

    float R = 1023.0/((float)a)-1.0;
    R = 100000.0*R;

    float temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;//convert to temperature via datasheet ;

    Serial.print("temperature = ");
    Serial.println(temperature);

    delay(100);
}
