// Notes.h tab in Arduino IDE is only for comments and references!

// based on RandDruid/esp8266-deauth (MIT) https://github.com/RandDruid/esp8266-deauth
// inspired by kripthor/WiFiBeaconJam (no license) https://github.com/kripthor/WiFiBeaconJam
// https://git.schneefux.xyz/schneefux/jimmiejammer/src/master/jimmiejammer.ino
// requires SDK v1.3: install esp8266/Arduino from git and checkout commit 1c5751460b7988041fdc80e0f28a31464cdf97a3
// Modified by M. Ray Burnette for publication as WiFi Sniffer 20161013
// Modified by Kosme for publication
// Adapted by AndreasFischer1985

/*
   Arduino 1.6.12 on Linux Mint 17.3
    Sketch uses 264,164 bytes (27%) of program storage space. Maximum is 958,448 bytes.
    Global variables use 440,336 bytes (49%) of dynamic memory, leaving 41,584 bytes for local variables. Maximum is 81,920 bytes.
*/

/*
  // beacon template
  uint8_t template_beacon[128] = { 0x80, 0x00, 0x00, 0x00,
                                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                /*22*/  0xc0, 0x6c,
                                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,
                                /*32*/  0x64, 0x00,
                                /*34*/  0x01, 0x04,
                                /* SSID */
                                /*36*/  0x00, 0x06, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                                        0x01, 0x08, 0x82, 0x84,
                                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01,
                                /*56*/  0x04
  };
*/

/*    Notes:
  Ref: http://www.esp8266.com/viewtopic.php?f=32&t=7025
  In the ESP8266WiFi.h, there is the function getNetworkInfo() which I presume allows you to get
  info for hidden AP.

  bool getNetworkInfo(uint8_t networkItem, String &ssid, uint8_t &encryptionType, int32_t &RSSI, uint8_t* &BSSID, int32_t &channel, bool &isHidden);
  CODE: SELECT ALL
    /**
       loads all infos from a scanned wifi in to the ptr parameters
       @param networkItem uint8_t
       @param ssid  const char*
       @param encryptionType uint8_t
       @param RSSI int32_t
       @param BSSID uint8_t *
       @param channel int32_t
       @param isHidden bool
       @return (true if ok)
*/

/*    Serial Console Sample Output:
  
  ESP8266 enhanced sniffer by AndreasFischer1985 https://github.com/andreasfischer1985

          /---------MAC---------/-----WiFi Access Point SSID-----/  /------MAC------/  Chnl  RSSI APs DEVs
  BEACON: <==================== [                      TardisTime]  1a:fe:34:a0:8b:c9    8    -76   1    0
  BEACON: <==================== [                     xfinitywifi]  56:57:1a:07:30:c0   11    -90   2    0
  BEACON: <==================== [                      ATTGH6Gs22]  10:05:b1:d6:ff:90   11    -95   3    0
  BEACON: <==================== [                      ATT4P3G9f8]  1c:14:48:77:74:20   11    -92   4    0
  BEACON: <==================== [                       HOME-30C2]  5c:57:1a:07:30:c0   11    -91   5    0
  BEACON: <==================== [                      ATT8Q4z656]  b0:77:ac:c4:df:d0   11    -92   6    0
  BEACON: <==================== [                       HOME-B1C2]  94:87:7c:55:b1:c0   11    -94   7    0
  BEACON: <==================== [                        HUXU2012]  0c:54:a5:d6:e4:80    6    -94   8    0
  DEVICE: 18:fe:34:fd:c2:b8 ==> [                      TardisTime]  1a:fe:34:a0:8b:c9    8    -79   8    1
  DEVICE: 18:fe:34:f9:77:a0 ==> !                      AP UNKNOWN!                ???  ???    -76   8    2
  DEVICE: 60:02:b4:48:4f:2d ==> [                      ATTGH6Gs22]  01:80:c2:00:00:00   11    -98   8    3
  BEACON: <==================== [                   HOME-01FC-2.4]  84:00:2d:a2:51:d8    6   -100   9    3
  DEVICE: 50:39:55:d3:48:34 ==> [                      ATT8Q4z656]  01:00:5e:7f:ff:fa   11    -87   9    4  
  BEACON: <==================== [           Verizon-SM-G935V-6526]  a6:08:ea:30:65:26   11    -92  10    4
*/
