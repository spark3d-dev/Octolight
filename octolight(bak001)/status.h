#ifndef _H_STATUS
#define _H_STATUS

// Extern Ventil List
#include "ventil.h"
extern Ventil ventilList[4];



class Status
{
  private:

  public:

  // Contructor
  // ====================================================
  Status( void );

  // M
  // ====================================================
  void initDisplay( void );                     // init the oled display
  void clearDisplay( void );                    // clears the display screen
  void bootscreen( void );                      // show bootscreen
  void actStatus( void );                       // display the actual status
  void wifiEstablished( String ssid, String ip );
  void apEnabled();

};

#endif
