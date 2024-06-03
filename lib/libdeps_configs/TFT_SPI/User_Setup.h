// User_Setup.h

#define ST7796_DRIVER  // Enable ST7796 TFT driver

// Define the pins used for the display
#define TFT_CS   5  // Chip select control pin
#define TFT_DC   2  // Data Command control pin
#define TFT_RST  4  // Reset pin (could connect to Arduino RESET pin)

// Define the pins for SPI communication
#define TFT_SCLK 18  // Clock pin
#define TFT_MOSI 23  // Data out pin
#define TFT_MISO 19  // Data in pin (if needed)

// Optional: LED control pin
#define TFT_BL   -1  // Set to -1 if not used

// Touch screen pins
#define TOUCH_CS 14  // Chip select pin for touch screen
#define TOUCH_IRQ 25 // Touch screen IRQ pin

// Define SPI settings
#define SPI_FREQUENCY  27000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000

// Load the fonts
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

// Define the SPI frequency
#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000

//PINS TO THE BOARD, SOME SHARED
// TIRQ 25
// T_DO 19
// T_DIN 23
// T_CS 14
// T_CLK 18
// SDO(MISO) 19
// LED 3.3
// SCK 18
// SDI(MISO) 23
// DC/RS 2
// RESET 4
// CS 5
// GND GROUND
// VCC 5V