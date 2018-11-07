// Library
// =============================================
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>


// Settings
// ====================================================================
#include "settings.h"
#include "status.h"


// NeoPixel
// ====================================================================
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_PIXEL, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel statusPixels = Adafruit_NeoPixel(LED_PIXEL_STATUS, LED_PIN_STATUS, NEO_GRB + NEO_KHZ800);


// printerValues
// ====================================================================
bool printingState;
int printerProgress;
double bedActual;
double bedTarget;
double toolActual;
double toolTarget;


// apiStatus
// ====================================================================
bool apiStatus = false;


// SETUP
// ====================================================================
void setup() {

  // Serial
  Serial.begin(115200);

  // pixels begin
  pixels.begin();
  pixels.show();

  // statusPixels begin
  statusPixels.begin();
  statusPixels.show();

  // wifi begin
  WiFi.begin(wlanSSID.c_str(), wlanPASS.c_str());

  // wifi connect
  if ( tryWifi() ) {
    Serial.println("connected!");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
    Serial.println( "===================================" );
    Serial.println("");

    // led wifi status
    ledRGBFlash( wifiSuccessR, wifiSuccessG, wifiSuccessB, wifiSuccessBrightness, wifiSuccessDelayOn, wifiSuccessDelayOff, wifiSuccessInterval );

    return;
  }



    // Status
    Status status;

    // bootscreen
    status.bootscreen();
}







// SETUP
// ====================================================================
void loop() {


  // connection
  if (WiFi.status() == WL_CONNECTED) {

    // update printer status
    Serial.print("Request Printer Status...");
    getPrinter();
    getPrinterJob();


    // api success
    if( apiStatus ) {

      // check printing state
      if( printingState == false ) {

        Serial.println( "" );
        Serial.println( "======  STATUS   ======" );
        Serial.println( "Status: Printer ready!" );

        // led
        ledRGB(0,255,0,100);

        // update interval
        updateInterval = updateIntervalReady;

      } else {


        Serial.println( "" );
        Serial.println( "====== TEMP INFO ======" );

        // bed
        Serial.print("bedActual: ");
        Serial.println( bedActual );
        Serial.print("bedTarget: ");
        Serial.println( bedTarget );

        Serial.println( "" );

        // tool
        Serial.print("toolActual: ");
        Serial.println( toolActual );
        Serial.print("toolTarget: ");
        Serial.println( toolTarget );
        Serial.println( "====== TEMP INFO ======" );
        Serial.println( "" );

        checkPrinterState();
      }

    }




  }
  // restart
  else {
    ESP.restart();
  }

        ledStatus( printerProgress );

  // delay requests
  Serial.println( "" );
  Serial.print( "Next update in: " );
  Serial.print( updateInterval / 1000 );
  Serial.println( "s" );
  Serial.println( "===================================" );
  Serial.println("");
  delay( updateInterval );


}









// ====================================================================
// try wifi
// ====================================================================
bool tryWifi(void) {

  // try to connect
  Serial.println("");
  Serial.print("Connect WiFi... ");
  wifiConnect();

  // try
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {

    Serial.println("WiFi failed!");

    // led wifi status
    ledRGBFlash( wifiFailR, wifiFailG, wifiFailB, wifiFailBrightness, wifiFailDelayOn, wifiFailDelayOff, wifiFailInterval );

    // try reconnect
    Serial.print("Reconnect WiFi... ");
    wifiConnect();

    // fail
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi failed!");

      // led wifi status
      ledRGBFlash( wifiFailR, wifiFailG, wifiFailB, wifiFailBrightness, wifiFailDelayOn, wifiFailDelayOff, wifiFailInterval );


      return false;
    } else {
      return true;
    }

  } else {
    return true;
  }

  delay(2000);

}



// ====================================================================
// wifiConnect
// ====================================================================
bool wifiConnect(void) {
  // try to connect
  WiFi.hostname( wlanHostname );
  WiFi.mode( WIFI_STA );
  WiFi.begin( wlanSSID.c_str(), wlanPASS.c_str() );
}



// ====================================================================
// ledRGB
// ====================================================================
void ledRGB( int r, int g, int b, int brightness) {

  r = brightness * r / 100;
  g = brightness * g / 100;
  b = brightness * b / 100;

  for(int i=0;i < LED_PIXEL;i++){
    pixels.setPixelColor(i, pixels.Color(r,g,b));
  }
  pixels.show();
}


// ====================================================================
// ledRGBFlash
// ====================================================================
void ledRGBFlash( int r, int g, int b, int brightness, int delayOn, int delayOff, int interval) {

  r = brightness * r / 100;
  g = brightness * g / 100;
  b = brightness * b / 100;

  for(int i=0; i < interval; i++){
      ledRGB( r, g, b, brightness);
      delay( delayOn );
      ledRGB( r, g, b, 0);
      delay( delayOff );
    }
}


// ====================================================================
// ledStatus
// ====================================================================
void ledStatus( int printerProgress ) {
  int stepDelay = 0;
  int statusLastActiveLed = false;
  int statusLastActiveDelay = 555;

  // add 100% delay
  if( printerProgress >= 100 ) {
    stepDelay = 55;

    for(int i = 0; i < LED_PIXEL_STATUS; i++){
      statusPixels.setPixelColor(i, statusPixels.Color( 0, 0, 0));
      statusPixels.show();
      delay(55);
    }
    delay(10);
  } else {

    // loop states
    for( int i = 1; i <= LED_PIXEL_STATUS; i++ ) {
      int steps = 100 / LED_PIXEL_STATUS;
      int stepValue = i * steps;
      int led = i-1;

      // Power LED
      if( printerProgress >= stepValue ) {
        statusPixels.setPixelColor( led, statusPixels.Color(0,255,0) );
        statusPixels.show();
        statusLastActiveLed = led;
      } else {
        statusPixels.setPixelColor( led, statusPixels.Color(255,0,0) );
        statusPixels.show();
      }

      delay( stepDelay );
    }

    if( statusLastActiveLed ) {
        statusPixels.setPixelColor( statusLastActiveLed, statusPixels.Color(0,255,0) );
        statusPixels.show();
        delay(statusLastActiveDelay);
        statusPixels.setPixelColor( statusLastActiveLed, statusPixels.Color(255,0,0) );
        statusPixels.show();
        delay(statusLastActiveDelay);
        statusPixels.setPixelColor( statusLastActiveLed, statusPixels.Color(0,255,0) );
        statusPixels.show();
        delay(statusLastActiveDelay);
        statusPixels.setPixelColor( statusLastActiveLed, statusPixels.Color(255,0,0) );
        statusPixels.show();
        delay(statusLastActiveDelay);
        statusPixels.setPixelColor( statusLastActiveLed, statusPixels.Color(0,255,0) );
        statusPixels.show();
        delay(statusLastActiveDelay);
        statusPixels.setPixelColor( statusLastActiveLed, statusPixels.Color(255,0,0) );
        statusPixels.show();
        delay(statusLastActiveDelay);
    }

  }

}



// ====================================================================
// getPrinter - REST API
// ====================================================================
void getPrinter() {

  // create obj
  HTTPClient http;

  // begin
  http.begin("http://" + octo_ip_adr  + "/api/printer?apikey=" + octo_api_key );

  // send request
  int httpCode = http.GET();

  // print request
  if (httpCode > 0) {

    // success
    Serial.println( "REST API: SUCCESS!" );
    apiStatus = true;

    // Parsing
    const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
    DynamicJsonBuffer jsonBuffer(bufferSize);

    // lvl 0
    JsonObject& parsed = jsonBuffer.parseObject(http.getString());

    // lvl 1
    JsonObject& printerState = parsed["state"];
    JsonObject& printerTemperature = parsed["temperature"];

    // lvl 2
    JsonObject& printerState_flags = printerState["flags"];
    JsonObject& printerTemperature_bed = printerTemperature["bed"];
    JsonObject& printerTemperature_tool0 = printerTemperature["tool0"];

    // printingState
    printingState = printerState_flags["printing"];

    // bed
    bedActual     =     printerTemperature_bed["actual"];
    bedTarget     =     printerTemperature_bed["target"];

    // tool0
    toolActual    =     printerTemperature_tool0["actual"];
    toolTarget    =     printerTemperature_tool0["target"];



  } else {
    Serial.println( "REST API: FAILED!" );

    // led rest failed
    ledRGBFlash( apiFailR, apiFailG, apiFailB, apiFailBrightness, apiFailDelayOn, apiFailDelayOff, apiFailInterval );
  }


  // close
  http.end();



}


// ====================================================================
// getPrinterJob - REST API
// ====================================================================
void getPrinterJob() {

  // create obj
  HTTPClient http;

  // begin
  http.begin("http://" + octo_ip_adr  + "/api/job?apikey=" + octo_api_key );

  // send request
  int httpCode = http.GET();

  // print request
  if (httpCode > 0) {

    // success
    Serial.println( "REST API: SUCCESS!" );
    apiStatus = true;

    // Parsing
    const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
    DynamicJsonBuffer jsonBuffer(bufferSize);

    // lvl 0
    JsonObject& parsed = jsonBuffer.parseObject(http.getString());

    // lvl 1
    JsonObject& progress = parsed["progress"];

    printerProgress = progress["completion"];

    Serial.print("Progress: ");
    Serial.println( printerProgress );




  } else {
    Serial.println( "REST API: FAILED!" );

    // led rest failed
    ledRGBFlash( apiFailR, apiFailG, apiFailB, apiFailBrightness, apiFailDelayOn, apiFailDelayOff, apiFailInterval );
  }


  // close
  http.end();



}



// ====================================================================
// checkPrinterState
// ====================================================================
void checkPrinterState() {
    int bedStatus = 0;
    int toolStatus = 0;

    // bed
    if( bedActual >= bedTarget - bedTolerance && bedTarget != 0 ) {
      // Serial.println( "Bed heated!" );
      bedStatus = 1;
    }

    // tool
    if( bedStatus == 1 ) {

      if( toolActual >= toolTarget - toolTolerance && bedStatus == 1 && toolTarget != 0 ) {
        // Serial.println( "Tool heated!" );
        toolStatus = 1;
      }

    }

    // preheated
    if( bedStatus == 1 && toolStatus == 1 && bedTarget != 0 ) {

      Serial.println( "" );
      Serial.println( "======  STATUS   ======" );
      Serial.println( "Status: Printing..." );

      // led
      ledRGB( printingR, printingG, printingB, printingBrightness);

      // update interval
      updateInterval = updateIntervalPrinting;
    }

    // tool heating
    else if ( bedStatus == 1 && toolStatus == 0 ) {

      Serial.println( "" );
      Serial.println( "======  STATUS   ======" );
      Serial.println( "Status: Tool heating..." );

      // led
      ledRGB( toolHeatingR, toolHeatingG, toolHeatingB, toolHeatingBrightness);

      // update interval
      updateInterval = updateIntervalHeating;
    // bed heating
    } else {

      Serial.println( "" );
      Serial.println( "======  STATUS   ======" );
      Serial.println( "Status: Bed heating..." );

      // led
      ledRGB( bedHeatingR, bedHeatingG, bedHeatingB, bedHeatingBrightness);

      // update interval
      updateInterval = updateIntervalHeating;
    }

}
