
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <M5Cardputer.h>
#include <stdint.h>

// --- IR Pins ---

const int irRxPin = 1;         
const int irTxPin = 44; 

//IR Protocols

/* Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols (except BEO / Bang&Olufsen) are active.
 * This must be done before the #include <IRremote.hpp>
 * In alphabetic order
 */

//#define DECODE_DENON        // Includes Sharp - requires around 250 bytes of program memory on ATmega328
//#define DECODE_JVC          // ~ 200 bytes
//#define DECODE_KASEIKYO     // Includes Panasonic ~ 300 bytes
//#define DECODE_LG           // ~ 400 bytes
//#define DECODE_NEC          // Includes Apple and Onkyo ~ 250 bytes
//#define DECODE_SAMSUNG      // ~ 300 bytes
//#define DECODE_SONY         // ~ 175 bytes
//#define DECODE_RC5          // RC5 + MARANTZ: ~ 425 bytes
//#define DECODE_RC6          // ~ 375 bytes

// Universal protocol decoder
//#define DECODE_DISTANCE_WIDTH // Universal decoder for pulse distance width protocols ~ 2275 bytes
//#define DECODE_HASH         // special decoder for all protocols ~ 250 bytes

// Exotic protocol decoder
//#define DECODE_BOSEWAVE     // ~ 140 bytes
//#define DECODE_FAST         // ~ 135 bytes
//#define DECODE_LEGO_PF      // ~ 300 bytes
//#define DECODE_MAGIQUEST    // ~ 270 bytes
//#define DECODE_MARANTZ      // RC5 + MARANTZ: ~ 425 bytes
//#define DECODE_OPENLASIR    // Modified NEC with 8-bit validated address + 16-bit command. ~ 175 bytes
//#define DECODE_WHYNTER      // ~ 90 bytes

//#define DECODE_ONKYO        // Decodes NEC and Apple as Onkyo - saves around 90 bytes of program memory, if activated
//#define DECODE_BEO          // This protocol must always be enabled manually, i.e. it is NOT enabled if no protocol is defined. It prevents decoding of SONY! ~ 430 bytes
#if FLASHEND >= 0x7FFF  // For 16k flash or more, like ATtiny1604. Code does not fit in program memory of ATtiny85 etc.
// Do not enable any protocol explicitly => all protocols are enabled automatically.
// !!! Enabling B&O disables detection of Sony, because the repeat gap for SONY is smaller than the B&O frame gap :-( !!!
//#define DECODE_BEO // Bang & Olufsen protocol always must be enabled explicitly. It has an IR transmit frequency of 455 kHz! It prevents decoding of SONY! ~ 430 bytes
#else
// for 8k flash
//#define DECODE_DENON        // Includes Sharp - requires around 250 bytes of program memory on ATmega328
//#define DECODE_JVC          // ~ 200 bytes
#define DECODE_KASEIKYO     // Includes Panasonic ~ 300 bytes
#define DECODE_LG           // ~ 400 bytes
#define DECODE_NEC          // Includes Apple and Onkyo ~ 250 bytes
#define DECODE_SAMSUNG      // ~ 300 bytes
#define DECODE_SONY         // ~ 175 bytes
//#define DECODE_RC5          // RC5 + MARANTZ: ~ 425 bytes
//#define DECODE_RC6          // ~ 375 bytes
#define DECODE_DISTANCE_WIDTH // Universal decoder for pulse distance width protocols ~ 2275 bytes
#define DECODE_HASH         // special decoder for all protocols ~ 250 bytes
#define EXCLUDE_EXOTIC_PROTOCOLS

#endif

// --- Key Mappings (Cardputer Specific) ---

#define KEY_BACK   '`'  
#define KEY_ENTER  0x28
#define KEY_UP     ';'   
#define KEY_DOWN   '.'

// --- SD PINS ---

#define SD_SPI_SCK_PIN 40
#define SD_SPI_MISO_PIN 39
#define SD_SPI_MOSI_PIN 14
#define SD_SPI_CS_PIN 12

// --- UI Element Positions ---
const int headerTextXPosition = 10;
const int headerTextYPosition = 5;
const int bodyTextXPosition = 10;
const int bodyTextYPosition = 35;
const int bodyTextMarginLeft = 10;
const int bodyTextMarginTop = 35;
const int menuSpacing = 25;

// --- Theme Colors ---

const uint16_t fillScreenColor = 0x0000;       
const uint16_t headerTextColor = 0xFFE0;       
const uint16_t bodyTextColor = 0x07E0;      
const uint16_t highlightedTextColor = 0xF800;  
const uint16_t inputTextColor = 0xFFFF;

// --- Overlay Colors ---

const uint16_t overlayBgColor = 0x0000;
const uint16_t overlayBorderColor = 0x07E0;
const uint16_t buttonBgColor = 0x0000;
const uint16_t buttonTextColor = 0x07E0;

// --- UI Scaling ---

const int headerFontSize = 2;
const int bodyFontSize = 1;

#endif