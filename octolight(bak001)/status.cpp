#include "status.h"
#include <Arduino.h>

// Settings
// =============================================
#define DEBUG 1


// OLED Libraries
// ====================================================
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Adafruit oled
// ====================================================
// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);



// bootscreenLogo
// ====================================================
const unsigned char bootscreenLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x60, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x40, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x02, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x30, 0x0c, 0x10, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0xc0, 0x60, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xc0, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x80, 0x20, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x19, 0x00, 0x20, 0x00, 0x00, 0x00, 0x78, 0xf9, 0x39, 0x3e, 0x79, 0xe3, 0x80,
  0x00, 0xc8, 0x89, 0xa9, 0x02, 0x21, 0x12, 0x00, 0x00, 0x88, 0x88, 0xab, 0x1e, 0x21, 0xf2, 0x00,
  0x00, 0x88, 0x88, 0xae, 0x32, 0x21, 0xf2, 0x00, 0x00, 0x88, 0x88, 0xe6, 0x22, 0x21, 0x02, 0x00,
  0x00, 0x78, 0x88, 0xc6, 0x3e, 0x39, 0xf2, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// wifiLogo
// ====================================================
const unsigned char wifiLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8f, 0xf1, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x1c, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Contructor
Status::Status( void )
{

}


// initOLED
// ====================================================
void Status::initDisplay( void ) {

  #if DEBUG
    Serial.println("");
    Serial.println("=================");
    Serial.println("    OLED INIT    ");
    Serial.println("=================");
  #endif

  // display begin
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // display defaults
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // clear display
  clearDisplay();

  // small display delay
  delay( 100 );
}

// clearDisplay
// ====================================================
void Status::clearDisplay( void )
{

  #if DEBUG
    Serial.println("=================");
    Serial.println("  CLEAR DISPLAY  ");
    Serial.println("=================");
  #endif

  // clear display
  display.clearDisplay();
  display.display();

}


// bootscreen
// ====================================================
void Status::bootscreen( void )
{

  // display init
  initDisplay();

  #if DEBUG
    Serial.println("=================");
    Serial.println("    BOOTSCREEN   ");
    Serial.println("=================");
  #endif

  // draw bootscreen image
  display.drawBitmap(0, 0, bootscreenLogo, 64, 48, WHITE);
  display.display();

  // delay bootscreen image
  //delay( 5000 );


}

// wifiEstablished
// ====================================================
void Status::wifiEstablished( String ssid, String ip )
{

  #if DEBUG
    Serial.println("");
    Serial.println("==================");
    Serial.println(" WIFI ESTABLISHED ");
    Serial.println("==================");
  #endif


  // clear display
  clearDisplay();

  // draw bootscreen image
  display.drawBitmap(0, 0, wifiLogo, 64, 48, WHITE);

  // line 1
  display.setCursor(0,0);
  display.println( ssid );

    // line 5
  display.setCursor(0,30);
  display.println( ip );

  // display
  display.display();


  // status led
  #if RGBW
    rgbw& rgbw = rgbw::getInstance();
    rgbw.rgbwShow( 0, 0, 55, 0, 100 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 0, 0, 0 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 55, 0, 100 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 0, 0, 0 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 55, 0, 100 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 0, 0, 0 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 55, 0, 100 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 0, 0, 0 );
  #endif

  // delay
  delay( 5000 );
}

// apEnabled
// ====================================================
void Status::apEnabled( void )
{

  #if DEBUG
    Serial.println("");
    Serial.println("==================");
    Serial.println("    AP ENABLED    ");
    Serial.println("==================");
  #endif


  // clear display
  clearDisplay();

  // draw bootscreen image
  display.drawBitmap(0, 0, wifiLogo, 64, 48, WHITE);

  // line 1
  display.setCursor(12,0);
  display.println( "AP MODE" );

    // line 5
  display.setCursor(10,30);
  display.println( "192.168." );
  display.setCursor(25,40);
  display.println( "4.1" );

  // display
  display.display();


  // status led
  #if RGBW
    rgbw& rgbw = rgbw::getInstance();
    rgbw.rgbwShow( 55, 15, 0, 0, 100 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 0, 0, 0 );
    delay( 155 );
    rgbw.rgbwShow( 55, 15, 0, 0, 100 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 0, 0, 0 );
    delay( 155 );
    rgbw.rgbwShow( 55, 15, 0, 0, 100 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 0, 0, 0 );
    delay( 155 );
    rgbw.rgbwShow( 55, 15, 0, 0, 100 );
    delay( 155 );
    rgbw.rgbwShow( 0, 0, 0, 0, 0 );
  #endif

  // delay
  delay( 25000 );
}




// actStatus
// ====================================================
void Status::actStatus( void )
{

  #if DEBUG
    Serial.println("");
    Serial.println("=================");
    Serial.println("     STATUS      ");
    Serial.println("=================");
  #endif

  // fillscreen
  display.fillScreen( BLACK );

  Config& config = Config::getInstance();

  // Wifi indicator
  if( config.getWlanStatus() == 1 ) {

    // low
    display.drawLine(56, 4, 56, 6, WHITE);
    display.drawLine(57, 4, 57, 6, WHITE);

    // mid
    display.drawLine(59, 2, 59, 6, WHITE);
    display.drawLine(60, 2, 60, 6, WHITE);

    // full
    display.drawLine(62, 0, 62, 6, WHITE);
    display.drawLine(63, 0, 63, 6, WHITE);

    // line 1
    display.setCursor(0,0);
    display.println("qnWater");

  } else {
    display.drawCircle(60, 4, 3, WHITE);
    display.drawLine(57, 7, 64, 0, WHITE);

    // line 1
    display.setCursor(0,0);
    display.println("AP-Mode");
  }



  // line 2
  display.setCursor(0,10);
  display.println( ventilList[0].getName() );
  display.setCursor(58,10);
  display.println( ventilList[0].getStatus() );

  // line 3
  display.setCursor(0,20);
  display.println( ventilList[1].getName() );
  display.setCursor(58,20);
  display.println( ventilList[1].getStatus() );

  // line 4
  display.setCursor(0,30);
  display.println( ventilList[2].getName() );
  display.setCursor(58,30);
  display.println( ventilList[2].getStatus() );

  // line 5
  display.setCursor(0,40);
  display.println( ventilList[3].getName() );
  display.setCursor(58,40);
  display.println( ventilList[3].getStatus() );

  // display show
  display.display();

}
