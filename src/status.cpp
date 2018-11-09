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
  // display.drawBitmap(0, 0, bootscreenLogo, 128, 64, WHITE);
  // display.invertDisplay(true);
  // display.display();

  // delay bootscreen image
  //delay( 5000 );

	// display.setTextSize(1);
	// display.setTextColor(WHITE);
	// display.setCursor(0,0);
	// display.println("Ender 3");
	// display.setCursor(10,0);
	// display.println("Ender 5");
	// display.display();

}
//
// // wifiEstablished
// // ====================================================
// void Status::wifiEstablished( String ssid, String ip )
// {
//
//   #if DEBUG
//     Serial.println("");
//     Serial.println("==================");
//     Serial.println(" WIFI ESTABLISHED ");
//     Serial.println("==================");
//   #endif
//
//
//   // clear display
//   clearDisplay();
//
//   // draw bootscreen image
//   display.drawBitmap(0, 0, wifiLogo, 64, 48, WHITE);
//
//   // line 1
//   display.setCursor(0,0);
//   display.println( ssid );
//
//     // line 5
//   display.setCursor(0,30);
//   display.println( ip );
//
//   // display
//   display.display();
//
//
//   // status led
//   #if RGBW
//     rgbw& rgbw = rgbw::getInstance();
//     rgbw.rgbwShow( 0, 0, 55, 0, 100 );
//     delay( 155 );
//     rgbw.rgbwShow( 0, 0, 0, 0, 0 );
//     delay( 155 );
//     rgbw.rgbwShow( 0, 0, 55, 0, 100 );
//     delay( 155 );
//     rgbw.rgbwShow( 0, 0, 0, 0, 0 );
//     delay( 155 );
//     rgbw.rgbwShow( 0, 0, 55, 0, 100 );
//     delay( 155 );
//     rgbw.rgbwShow( 0, 0, 0, 0, 0 );
//     delay( 155 );
//     rgbw.rgbwShow( 0, 0, 55, 0, 100 );
//     delay( 155 );
//     rgbw.rgbwShow( 0, 0, 0, 0, 0 );
//   #endif
//
//   // delay
//   delay( 5000 );
// }

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
void Status::actStatus( int timeNow, int timeLeft, int progress, String filename, double bedActual, double toolActual )
{

  #if DEBUG
    Serial.println("");
    Serial.println("=================");
    Serial.println("     STATUS      ");
    Serial.println("=================");
  #endif

  // fillscreen
  display.fillScreen( BLACK );

  // Config& config = Config::getInstance();
  //
  // // Wifi indicator
  // if( config.getWlanStatus() == 1 ) {


    // low
    // display.drawLine(116, 4, 116, 6, WHITE);
    // display.drawLine(117, 4, 117, 6, WHITE);
	//
    // // mid
    // display.drawLine(119, 2, 119, 6, WHITE);
    // display.drawLine(120, 2, 120, 6, WHITE);
	//
    // // full
    // display.drawLine(122, 0, 122, 6, WHITE);
    // display.drawLine(123, 0, 123, 6, WHITE);

    // line 1
	display.setTextSize(2);
    // display.setCursor(0,0);
    // display.println("Ender3");
    // // display.drawLine(128, 30, 128, 30, WHITE);
	//
	// if( progress <= 100 ) {
    // 	display.setCursor(90,0);
	// } else {
    // 	display.setCursor(80,0);
	// }
    // display.print( progress );
    // display.println( "%" );
	//
	// display.setTextSize(1);
    // display.setCursor(0,25);
    // display.println("Heizbett:");
	//
    // display.setCursor(116,25);
    // display.println("55");
	//
    // display.setCursor(0,35);
    // display.println("Dauer:");
	//
	// if( timeNowMin <= 100 ) {
    // 	display.setCursor(116,35);
	// } else {
    // 	display.setCursor(110,35);
	// }
    // display.println( timeNowMin );
	//
	// display.setTextSize(1);
    // display.setCursor(0,45);
    // display.println("Verbleibend:");
	//
	// if( timeLeftMin <= 100 ) {
    // 	display.setCursor(115,45);
	// } else {
    // 	display.setCursor(110,45);
	// }
    // display.println( timeLeftMin );
	//
    // // display.setCursor(0,56);
    // // display.println( filename );

	// progress = 55;

	display.setTextSize(1);

	// title
	display.setCursor(0,0);
	display.println( filename );
	display.fillRect(0, 8, 128, 64, BLACK);
	// display.println("Ender-3");
	// display.println("Ender-5");

	// status / ready
	// display.setCursor(84,0);
	// display.println("Heating...");


	// nozzle

	// left right
	display.drawLine(1, 16, 1, 20, WHITE);
	display.drawLine(6, 16, 6, 20, WHITE);

	// left
	display.drawLine(2, 21, 2, 21, WHITE);
	display.drawLine(3, 22, 3, 22, WHITE);

	// mid
	display.drawLine(3, 24, 4, 24, WHITE);
	display.drawLine(1, 26, 2, 26, WHITE);
	display.drawLine(0, 26, 1, 26, WHITE);

	// right
	display.drawLine(4, 22, 4, 22, WHITE);
	display.drawLine(5, 21, 5, 21, WHITE);

	// temp
	display.setCursor(14,17);
	display.println( toolActual, 1 );
	display.drawCircle(48, 19, 2, WHITE);


	// heatbed
	display.drawLine(0, 38, 7, 38, WHITE);

	// heat 1
	display.drawLine(2, 35, 2, 35, WHITE);
	display.drawLine(1, 34, 1, 34, WHITE);
	display.drawLine(2, 33, 2, 33, WHITE);
	display.drawLine(1, 32, 1, 32, WHITE);

	// heat 2
	display.drawLine(6, 35, 6, 35, WHITE);
	display.drawLine(5, 34, 5, 34, WHITE);
	display.drawLine(6, 33, 6, 33, WHITE);
	display.drawLine(5, 32, 5, 32, WHITE);

	// temp
	display.setCursor(14,32);
	display.println( bedActual, 1 );
	display.drawCircle(42, 34, 2, WHITE);




	// timeLeft
	display.setCursor(84,17);

	// calc timeLeft
	int timeLeftMinutes = timeLeft / 60;
	int hoursLeft = timeLeftMinutes / 60;
	int minutesLeft = timeLeftMinutes - hoursLeft * 60;

	// hours
	if( hoursLeft >= 1 ) {
		display.print( hoursLeft );
		display.print( "h " );
		display.print( minutesLeft );
		display.println( "m" );
	} else {
		display.print( minutesLeft );
		display.println( "m" );
	}

	// icon
	display.drawCircle(74, 20, 4, WHITE);
	display.drawLine(74, 17, 74, 20, WHITE);
	display.drawLine(74, 20, 76, 20, WHITE);





	// timeNow
	display.setCursor(84,32);

	// calc timeNow
	int timeNowMinutes = timeNow / 60;
	int hoursNow = timeNowMinutes / 60;
	int minutesNow = timeNowMinutes - hoursNow * 60;

	// hours
	if( hoursNow >= 1 ) {
		display.print( hoursNow );
		display.print( "h " );
		display.print( minutesNow );
		display.println( "m" );
	} else {
		display.print( minutesNow );
		display.println( "m" );
	}

	// icon / play
	display.drawLine(73, 32, 73, 38, WHITE);
	display.drawLine(74, 33, 74, 37, WHITE);
	display.drawLine(75, 34, 75, 36, WHITE);
	display.drawLine(76, 35, 76, 35, WHITE);







	// progress
	if( progress < 10 ) {
		display.setCursor(60,50);
	} else if( progress < 100 )  {
		display.setCursor(58,50);
	} else {
		display.setCursor(54,50);
	}
    display.print( progress );
    display.println( "%" );


	// progressbar
    display.setCursor(4,58);

	// calc and draw
	int progressFull = progress / 5;
	for (int i=0; i <= 20; i++){
		if( progressFull > i ) {
			display.print( "=" );
		} else {
			display.print( " " );
		}
  	}

	// left cut
	display.drawLine(0, 59, 0, 64, WHITE);

	// right cut
	display.drawLine(127, 59, 127, 64, WHITE);






  //
  // } else {
  //   display.drawCircle(60, 4, 3, WHITE);
  //   display.drawLine(57, 7, 64, 0, WHITE);
  //
  //   // line 1
  //   display.setCursor(0,0);
  //   display.println("AP-Mode");
  // }


  //
  // // line 2
  // display.setCursor(0,10);
  // display.println( ventilList[0].getName() );
  // display.setCursor(58,10);
  // display.println( ventilList[0].getStatus() );
  //
  // // line 3
  // display.setCursor(0,20);
  // display.println( ventilList[1].getName() );
  // display.setCursor(58,20);
  // display.println( ventilList[1].getStatus() );
  //
  // // line 4
  // display.setCursor(0,30);
  // display.println( ventilList[2].getName() );
  // display.setCursor(58,30);
  // display.println( ventilList[2].getStatus() );
  //
  // // line 5
  // display.setCursor(0,40);
  // display.println( ventilList[3].getName() );
  // display.setCursor(58,40);
  // display.println( ventilList[3].getStatus() );

  // display show
  display.display();

}
