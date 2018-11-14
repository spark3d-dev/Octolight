#ifndef _H_STATUS
#define _H_STATUS
#include <Arduino.h>

// Extern Ventil List
// #include "ventil.h"
// extern Ventil ventilList[4];



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
  void actStatus( int timeNow, int timeLeft, int progress, String filename, double bedActual, double toolActual );                       // display the actual status

};

#endif
