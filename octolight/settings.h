// LED
// ====================================================================
#define LED_PIN D8
#define LED_PIXEL 6

// OCTOPRINT
// ====================================================================
const char* octo_api_key    = "enterOctoprintApiKeyHere";
String octo_ip_adr          = "enterOctoprintIpAdressHere";

// WLAN
// ====================================================================
String wlanSSID             = "enterYourSSIDHere";
String wlanPASS             = "enterYourPasswordHere";
const char* hostname        = "enterYourHostnameHere";

// UPDATE
// ====================================================================
int updateInterval          = 0;
int updateIntervalReady     = 5000;
int updateIntervalHeating   = 2000;
int updateIntervalPrinting  = 30000;

// TOLERANCE
// ====================================================================
double bedTolerance         = 1.5;
double toolTolerance        = 3;

// LED - BED heating
// ====================================================================
int bedHeatingR             = 255;
int bedHeatingG             = 0;
int bedHeatingB             = 0;
int bedHeatingBrightness    = 100;

// LED - TOOL heating
// ====================================================================
int toolHeatingR             = 255;
int toolHeatingG             = 55;
int toolHeatingB             = 0;
int toolHeatingBrightness    = 100;

// LED - printing
// ====================================================================
int printingR                = 255;
int printingG                = 255;
int printingB                = 255;
int printingBrightness       = 100;

// LED - WIFI success
// ====================================================================
int wifiSuccessR            = 0;
int wifiSuccessG            = 255;
int wifiSuccessB            = 0;
int wifiSuccessBrightness   = 100;
int wifiSuccessDelayOn      = 155;
int wifiSuccessDelayOff     = 155;
int wifiSuccessInterval     = 5;

// LED - WIFI fail
// ====================================================================
int wifiFailR              = 255;
int wifiFailG              = 0;
int wifiFailB              = 0;
int wifiFailBrightness     = 100;
int wifiFailDelayOn        = 155;
int wifiFailDelayOff       = 155;
int wifiFailInterval       = 5;

// LED - API fail
// ====================================================================
int apiFailR                = 255;
int apiFailG                = 55;
int apiFailB                = 0;
int apiFailBrightness       = 100;
int apiFailDelayOn          = 55;
int apiFailDelayOff         = 55;
int apiFailInterval         = 15;
