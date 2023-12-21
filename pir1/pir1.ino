#include <ESP8266WiFi.h>

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define BLYNK_TEMPLATE_ID "TMPLYBiBP5Z9"
#define BLYNK_DEVICE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "jOMQo1rwoPsKPjb5DQeavU4V9q_9b-z1"
#include <BlynkSimpleEsp8266.h>


/* WiFi credentials */
char ssid[] = "Galaxy M31639C";
char pass[] = "nitin123";

WidgetLED led1(V1);
int switchstate = 0;



#define Status D0 
#define sensor D7 // Input for HC-S501
int pirValue; // Place to store read PIR Value
int counter =0;
BLYNK_WRITE(V0){
    switchstate = param.asInt();
    Serial.println("switchstate = "+switchstate); 
}
void setup()
{
  led1.off();
  Serial.begin(115200);
  delay(10);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(Status, OUTPUT);
  pinMode(sensor, INPUT);
  digitalWrite(Status, LOW);
}

void loop()
{
  getPirValue();
  Blynk.run();
}

/***************************************************
 * Get PIR data
 **************************************************/
void getPirValue(void)
{
  if(switchstate == 0){
    long state = digitalRead(sensor);
      if(state == HIGH) {
        counter = 0;
        digitalWrite (Status, LOW);
        Blynk.virtualWrite(V1,1);
        led1.on();
        Serial.println("Motion detected!");
        
      }
      else {
        if(counter == 10){
          digitalWrite (Status, HIGH);
          Blynk.virtualWrite(V1,0);
          led1.off();
          counter =0;
        }
        Serial.println("Motion absent!");
        counter = counter+1;
        }
  }
  else{
      digitalWrite (Status, LOW);
        Blynk.virtualWrite(V1,1);
        led1.on();
  }
   delay(1000);
}
