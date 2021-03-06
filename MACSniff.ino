// by Ray Burnette 20161013 compiled on Linux 16.3 using Arduino 1.6.12
// Hacked by Kosme 20170520 compiled on Ubuntu 14.04 using Arduino 1.6.11
// Enhanced by AndreasFischer1985 20200810 compiled on Debian 10.5 using Arduino 1.8.13

unsigned long start = 0;
unsigned int channel = 1;

const char* mynetwork="mynetwork";  
const char* mypassword = "mypassword";

#include <ESP8266WiFi.h>
//#include <PubSubClient.h>
#include "./functions.h"

void setup() {
  Serial.begin(57600);
  Serial.printf("\n\nSDK version:%s\n\r", system_get_sdk_version());
  Serial.println(F("\n\rESP8266 enhanced sniffer by AndreasFischer1986 https://github.com/andreasfischer1985"));  
  Serial.println(F("\n\r        /---------MAC---------/-----WiFi Access Point SSID-----/  /------MAC------/  Chnl  RSSI  APs  DEVs"));

  wifi_set_opmode(STATION_MODE);            // Promiscuous works only with station mode
  wifi_set_channel(channel);
  wifi_promiscuous_enable(0);
  wifi_set_promiscuous_rx_cb(promisc_cb);   // Set up promiscuous callback
  wifi_promiscuous_enable(1);
  start=millis();

}

void loop() {
  channel = 1;
  wifi_set_channel(channel);
  while (true) {
    nothing_new++;                          // Array is not finite, check bounds and adjust if required
    if (nothing_new > 100) {
      nothing_new = 0;
      channel++;
      if (channel == 15) break;             // Only scan channels 1 to 14
      wifi_set_channel(channel);
    }
    delay(1);  // critical processing timeslice for NONOS SDK! No delay(0) yield()

    if(false) //comment out to enable reporting (cf. report-function in functions.h)
    if((millis()-start)>=10*60*1000) {
        report();
        start=millis();
    } 
    
  }
}
