// code for one display, tested //
#include <SPI.h>
#include "Ap_29demo_1.h"

// IO settings
const int BUSY_Pin = 7; 
const int RES_Pin = 8; 
const int DC_Pin = 9; 
const int CS_Pin = 10; 

// Command definitions
// Defining macros for controlling the pins and checking the busy status of the display
#define EPD_W21_CS_0 digitalWrite(CS_Pin, LOW)
#define EPD_W21_CS_1 digitalWrite(CS_Pin, HIGH)
#define EPD_W21_DC_0 digitalWrite(DC_Pin, LOW)
#define EPD_W21_DC_1 digitalWrite(DC_Pin, HIGH)
#define EPD_W21_RST_0 digitalWrite(RES_Pin, LOW)
#define EPD_W21_RST_1 digitalWrite(RES_Pin, HIGH)
#define isEPD_W21_BUSY digitalRead(BUSY_Pin)

// Function prototypes
void SPI_Write(unsigned char value);
void Epaper_Write_Command(unsigned char command);
void Epaper_Write_Data(unsigned char command);
void EPD_HW_Init(void);
void EPD_WhiteScreen(const unsigned char *data, unsigned char color);
void EPD_DeepSleep(void);


// Function called; initializes the pins and begins SPI communication
void setup() {
  pinMode(BUSY_Pin, INPUT); 
  pinMode(RES_Pin, OUTPUT);  
  pinMode(DC_Pin, OUTPUT);    
  pinMode(CS_Pin, OUTPUT);    
  
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
  SPI.begin();  
}


void loop() {
  // Called repeatedly in a loop
  // Initialize display
  EPD_HW_Init();

  // Show the image
  EPD_WhiteScreen(gImage_6, 0xFF); // Display the image
  
// Enter deep sleep
  EPD_DeepSleep(); 
}


// SPI communication
void SPI_Write(unsigned char value) {                                                           
  SPI.transfer(value);
}

void Epaper_Write_Command(unsigned char command) {
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}

void Epaper_Write_Data(unsigned char command) {
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // data write
  SPI_Write(command);
  EPD_W21_CS_1;
}


// EPD settings Functions
void EPD_HW_Init(void) {
  
  // Additional initialization commands can be added here if necessary

  Epaper_Write_Command(0x12);  // SWRESET
  while (isEPD_W21_BUSY == HIGH); // Wait until module is ready

  // Add further initialization commands here if needed
}

void EPD_WhiteScreen(const unsigned char *data, unsigned char color) {
  Epaper_Write_Command(0x24);   // Write RAM for black(0)/white (1)
  for (unsigned int i = 0; i < 5000; i++) {               
    Epaper_Write_Data(pgm_read_byte(&data[i]) & color); // Apply color mask
  }
  Epaper_Write_Command(0x22); // Display Update Control
  Epaper_Write_Data(0xF7);   
  Epaper_Write_Command(0x20); // Activate Display Update Sequence
  while (isEPD_W21_BUSY == HIGH); // Wait until update is complete
}

void EPD_DeepSleep(void) {  
  Epaper_Write_Command(0x10); // Enter deep sleep
  Epaper_Write_Data(0x01); 
  delay(100);
}
