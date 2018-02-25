# OctoLight
OctoLight is a automatic and easy to use light system for your 3D printer. Just set up your Octoprint API Key, LED settings and your WLAN credentials in the settings file and flash your ESP8266 with the OctoLight Firmware. Connect the digital LEDs (WS2812) and let the Show begin.
(No Octoprint Plugin needed.)

Your printer will be lit in different colors:
 * WiFi connected (flashing GREEN)
 * Ready (GREEN)
 * Heating your bed (RED)
 * Heating your tool (ORANGE)
 * Print in progress (WHITE)

The default colors can also be modified in the settings file.


## Software setup

  1. Download the latest zip
  2. Configure API Key, LED and WLAN settings in settings.h file
  3. Upload to your ESP8266


## Hardware setup

* Get an ESP8266 (here: NODEMCU 12e)
* Connect your WS2812 with your ESP8266
  (by default: LED_PIN = D8; LED_PIXEL = 10;)
* Let the show begin


## Settings.h

* OCTOPRINT REST API
```sh
octo_api_key    = "enterOctoprintApiKeyHere";
octo_ip_adr     = "enterOctoprintIpAdressHere";
```

* WLAN
```sh
wlanSSID        = "enterYourSSIDHere";
wlanPASS        = "enterYourPasswordHere";
Hostname        = "enterYourHostnameHere";
```

* LED
```sh
LED_PIN D8
LED_PIXEL 6
```

* LED Settings
```sh
toolHeatingR             = 255;		// red (0-255)
toolHeatingG             = 55;		// green (0-255)
toolHeatingB             = 0;		// blue (0-255)
toolHeatingBrightness    = 100;		// brightness
```

## Libraries

  * ESP8266WiFi.h
  * ESP8266HTTPClient.h
  * ArduinoJson.h
  * Adafruit_NeoPixel.h

## Troubleshooting

  * LED flashing RED 5 times = WiFi Connection failed
  * LED fast flashing ORANGE 15 times = API Connection failed

