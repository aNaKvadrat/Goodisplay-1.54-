#include <SPI.h>

// Pin Definitions
#define BUSY_Pin 7
#define RES_Pin 8
#define DC_Pin 9
#define CS_Pin 10

void EPD_SendCommand(uint8_t command) {
  digitalWrite(CS_Pin, LOW); // Select E-paper Display
  digitalWrite(DC_Pin, LOW); // Command mode
  SPI.transfer(command); // Send command byte
  digitalWrite(CS_Pin, HIGH); // Deselect E-paper Display
}

void EPD_SendData(uint8_t data) {
  digitalWrite(CS_Pin, LOW); // Select E-paper Display
  digitalWrite(DC_Pin, HIGH); // Data mode
  SPI.transfer(data); // Send data byte
  digitalWrite(CS_Pin, HIGH); // Deselect E-paper Display
}

void EPD_Init() {
  // Initialize SPI
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  // Set pin modes
  pinMode(BUSY_Pin, INPUT);
  pinMode(RES_Pin, OUTPUT);
  pinMode(DC_Pin, OUTPUT);
  pinMode(CS_Pin, OUTPUT);

  // Send initialization commands
  digitalWrite(RES_Pin, LOW); // Reset the display
  delay(100);
  digitalWrite(RES_Pin, HIGH); // Release reset
  delay(100);

  // Send additional initialization commands here if needed

  // End SPI communication
  SPI.endTransaction();
  SPI.end();
}

void EPD_SendBitmapData(const unsigned char *bitmap, int dataSize) {
  for (int i = 0; i < dataSize; i++) {
    EPD_SendData(pgm_read_byte(bitmap + i)); // Send bitmap data byte by byte
  }
}

void setup() {
  EPD_Init(); // Initialize the E-paper Display
}

void loop() {
  // Your main code logic here

  // Example bitmap data for the letters "Hello" (5x8 font)
  const unsigned char myBitmap[1][5000] PROGMEM = {
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 
	0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xcc, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0x01, 0x8e, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x80, 0x0f, 0x04, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf8, 0x00, 0x0f, 0x83, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0xc1, 0x00, 
	0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xe0, 0x01, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x00, 0x7f, 
	0xf0, 0x00, 0x31, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x3f, 0xfc, 0x00, 0x0c, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0x00, 0x79, 0xfe, 0x02, 0x03, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0x03, 0x01, 0x9f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xe0, 0x03, 0xfe, 0x5f, 0xc1, 0xa0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x3f, 0xf3, 0x80, 0xa0, 
	0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0xce, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xc0, 0x3f, 
	0xe7, 0x01, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0xc0, 0x73, 0xe3, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
	0xe0, 0x1c, 0x18, 0x08, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0xc0, 0x5f, 0x80, 0x00, 0x01, 0xbf, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x80, 0x00, 0x00, 0x3f, 0x80, 0x06, 0x78, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 
	0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 
	0xff, 0xff, 0x00, 0x00, 0xf0, 0x00, 0x03, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x1f, 0xff, 0xff, 0x00, 0x00, 0xff, 0xc0, 0x04, 
	0x00, 0x07, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xc9, 0x87, 0xff, 0xff, 0x00, 0x00, 0x07, 0xf8, 0x70, 0x00, 0x00, 0x70, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 0x21, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x01, 0x80, 0x00, 0x00, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc8, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0x06, 0x00, 0x00, 0x00, 0x00, 0xe1, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x00, 0x01, 0xf0, 0x00, 
	0x00, 0xff, 0x18, 0x00, 0x00, 0x00, 0x00, 0x38, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe4, 0x00, 0x07, 0x03, 0xff, 0xff, 0xc3, 0x40, 0x00, 0x00, 0x00, 0x00, 
	0x0e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0x00, 0x1c, 
	0x00, 0x01, 0xff, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x00, 0x03, 0x80, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 
	0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe7, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x80, 0x00, 0x0e, 0x00, 0x0c, 0x0f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xf8, 0xc0, 0x00, 0x00, 0x03, 0xf0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x60, 0x00, 0x00, 0xff, 0xc3, 
	0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x20, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x12, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10, 0x00, 0x01, 
	0xff, 0xff, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x3b, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x88, 0x00, 0x01, 0xff, 0xfe, 0x03, 0xa0, 0x00, 0x40, 0x00, 
	0x00, 0x00, 0x3d, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc4, 
	0x00, 0x00, 0x1f, 0xfe, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x9f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe6, 0x00, 0x00, 0x07, 0xfe, 0x3e, 0x10, 0x00, 
	0x28, 0x00, 0x00, 0x00, 0x00, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xf2, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x10, 0x02, 0x18, 0x00, 0x00, 0x00, 0x00, 0x4f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x01, 0xf1, 0xff, 0xfc, 
	0x00, 0x02, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xff, 0xf0, 0x00, 0x02, 0x0c, 0x00, 0x00, 0x00, 0x00, 
	0x2f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0x83, 
	0xff, 0xf0, 0x00, 0x02, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x27, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x01, 0xff, 0xe6, 0x00, 0x00, 0x06, 0x00, 0x00, 
	0x00, 0x00, 0x27, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
	0x00, 0x00, 0xff, 0xe0, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x67, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x20, 0x00, 0xbf, 0xf0, 0x7e, 0x01, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xf0, 0x20, 0x20, 0xbf, 0xff, 0xff, 0x01, 0x00, 0x82, 0x00, 0x00, 0x03, 0xe7, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x03, 0xbf, 0xff, 0xff, 
	0x81, 0x00, 0xc2, 0x00, 0x00, 0x03, 0x67, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x00, 0x0f, 0xbf, 0xff, 0xff, 0x80, 0x00, 0x42, 0x00, 0x00, 0x00, 0x6f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0x1f, 
	0xff, 0xff, 0x80, 0x80, 0x33, 0x00, 0x00, 0x00, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0x7f, 0xff, 0xff, 0xc0, 0x80, 0x11, 0x00, 0x00, 
	0x00, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x80, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xfd, 0xfb, 0xff, 0xff, 0xc0, 0x00, 0x09, 
	0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x01, 0xfd, 0xff, 0xff, 0xff, 0x80, 0x00, 0x04, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x11, 0xfc, 0xef, 0xff, 0xff, 0x80, 
	0x00, 0x04, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x0d, 0xfe, 0xe3, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x89, 0xfc, 0x73, 0xff, 
	0xff, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x89, 0xf8, 0xff, 0xff, 0xff, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xfc, 
	0xff, 0xff, 0xff, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa0, 0xff, 0xdf, 0xff, 0xff, 0x8c, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xc0, 0xff, 0xff, 0xff, 0xff, 0x86, 0x03, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0x07, 0xff, 0xff, 0xaa, 0x01, 
	0x80, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0x00, 0x7e, 0x3f, 0xff, 0xff, 0xed, 0x00, 0xc0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xc0, 0x7e, 0x7f, 0xff, 0xff, 
	0xf4, 0x00, 0x60, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfd, 0xf0, 0x00, 0x3c, 0x00, 0x3f, 0xff, 0xf6, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xe0, 0x40, 0x3c, 0x18, 
	0x07, 0xfb, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfb, 0xc0, 0x00, 0x1c, 0x3c, 0x07, 0xfb, 0xff, 0x00, 0x00, 0x00, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x80, 0x00, 
	0x1e, 0x03, 0xff, 0xfd, 0xfc, 0x00, 0x20, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x00, 0x00, 0x1e, 0x7f, 0xff, 0x7d, 0xfc, 0x00, 0x08, 
	0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xee, 
	0x20, 0x00, 0x0e, 0x7e, 0xff, 0xff, 0xfc, 0x00, 0x06, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x40, 0x00, 0x0f, 0x81, 0xff, 0xff, 0xf8, 
	0x00, 0x03, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc8, 0xc0, 0x00, 0x07, 0x81, 0xff, 0xff, 0xf8, 0x00, 0x80, 0x80, 0x03, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0x80, 0x00, 0x07, 0x03, 0xff, 
	0xff, 0xf0, 0x00, 0x00, 0x20, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x91, 0x40, 0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x0c, 0x18, 0x03, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x13, 0x00, 0x00, 0x03, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x06, 0x04, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x22, 0x80, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x03, 0x01, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xa4, 0x00, 
	0x00, 0x00, 0xff, 0xff, 0xf0, 0x06, 0x00, 0x01, 0xc1, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xa4, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x0e, 0x00, 
	0x00, 0x68, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x80, 0x00, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x3c, 0x00, 0x00, 0x24, 0x00, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x48, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 
	0x75, 0x80, 0x08, 0x02, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfd, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x0c, 0x01, 0x00, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x40, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0xff, 0x00, 0x04, 0xc0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfd, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x01, 
	0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x40, 0x02, 0x00, 
	0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x02, 0x00, 0x01, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x40, 0x24, 0x02, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x01, 
	0x00, 0x01, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x40, 
	0x04, 0x06, 0x80, 0x00, 0x01, 0xff, 0xfe, 0x80, 0x00, 0xc0, 0x00, 0xc7, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x40, 0x04, 0x27, 0x00, 0x00, 0x01, 0xff, 0xfe, 
	0x00, 0x00, 0x70, 0x00, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfc, 0x20, 0x48, 0x2d, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x38, 0x00, 0xa7, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x20, 0x08, 0x4f, 0x00, 0x08, 0x30, 
	0xff, 0xfc, 0x00, 0x00, 0x0c, 0x00, 0xb3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x20, 0x10, 0x5f, 0x00, 0x08, 0x38, 0xff, 0xfc, 0x00, 0x00, 0x07, 0x00, 0x93, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10, 0x10, 0x9e, 0x08, 
	0x08, 0x3c, 0x7f, 0xfe, 0x00, 0x01, 0x03, 0xc0, 0x89, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x90, 0x10, 0xbe, 0x10, 0x08, 0x3f, 0x3f, 0x7c, 0x00, 0x00, 0x80, 
	0xf0, 0xcc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 0x01, 
	0xbe, 0x10, 0x08, 0x3f, 0x9e, 0xfc, 0x04, 0x00, 0x50, 0x48, 0x44, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x21, 0xfe, 0x10, 0x08, 0x3f, 0xc3, 0xfe, 0x04, 
	0x00, 0x68, 0x24, 0x46, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xe0, 0x23, 0x7c, 0x00, 0x08, 0x3f, 0xff, 0xf6, 0x24, 0x00, 0x2c, 0x00, 0x42, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x03, 0xfc, 0x00, 0x08, 0x1f, 0xff, 
	0xfc, 0x24, 0x00, 0x16, 0x00, 0x20, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf8, 0x03, 0xf8, 0x00, 0x08, 0x1f, 0xff, 0xec, 0x24, 0x00, 0x02, 0x00, 0x20, 0x1f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xf8, 0x00, 0x08, 
	0x1f, 0xff, 0xfc, 0x24, 0x00, 0x03, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xf1, 0x01, 0x00, 0x5f, 0xff, 0xfc, 0x22, 0x00, 0x01, 0x80, 
	0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xc3, 
	0x03, 0x00, 0x5f, 0xff, 0xf8, 0x22, 0x00, 0x00, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xc3, 0x06, 0x00, 0x7f, 0xff, 0xd8, 0x22, 0x00, 
	0x00, 0x60, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
	0x1f, 0x06, 0x0e, 0x00, 0x7f, 0xe7, 0xc8, 0x22, 0x00, 0x00, 0x30, 0x00, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0x0c, 0x1c, 0x00, 0x7f, 0xff, 0xfc, 
	0x22, 0x00, 0x40, 0x18, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc0, 0x3e, 0x08, 0x38, 0x02, 0x7f, 0xff, 0xfc, 0x22, 0x00, 0x20, 0x0c, 0x04, 0x03, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x7e, 0x18, 0x70, 0x03, 0x5f, 
	0xff, 0xfc, 0x02, 0x00, 0x18, 0x04, 0x00, 0x13, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x30, 0x7c, 0x31, 0xe0, 0x0f, 0xbf, 0xff, 0xfc, 0x02, 0x00, 0x0c, 0x02, 0x02, 
	0x1b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x61, 0xe8, 0x63, 0xe0, 
	0x07, 0xf7, 0xff, 0xfc, 0x00, 0x00, 0x06, 0x01, 0x00, 0x09, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x61, 0xe8, 0x47, 0xc0, 0x1f, 0xff, 0xfb, 0xfe, 0x01, 0x00, 0x03, 
	0x00, 0x01, 0x09, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc3, 0xe0, 
	0x8e, 0x40, 0x1f, 0xff, 0xff, 0xfe, 0x01, 0x00, 0x01, 0x80, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc3, 0xe0, 0x0e, 0x41, 0x3f, 0xff, 0xff, 0xfe, 0x11, 
	0x00, 0x00, 0x80, 0x00, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
	0x83, 0x60, 0x1e, 0x02, 0x3f, 0xff, 0xff, 0xfe, 0x11, 0x00, 0x00, 0x40, 0x00, 0x81, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xb2, 0x40, 0x1c, 0x86, 0x7f, 0xff, 0xff, 
	0xfe, 0x11, 0x00, 0x00, 0x20, 0x08, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfd, 0x22, 0xc0, 0x3c, 0x84, 0xff, 0xff, 0xff, 0xfe, 0x11, 0x00, 0x00, 0x00, 0x08, 0x41, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x22, 0xc1, 0xb8, 0x84, 0xff, 
	0xff, 0xe7, 0xfe, 0x09, 0x00, 0x00, 0x10, 0x08, 0x43, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf9, 0x22, 0x01, 0x78, 0x04, 0xff, 0xff, 0xef, 0xff, 0x09, 0x80, 0x00, 0x00, 
	0x08, 0x43, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0x20, 0x03, 0xf9, 
	0x14, 0xff, 0xff, 0xef, 0xff, 0x08, 0x80, 0x00, 0x08, 0x08, 0x47, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x20, 0x07, 0xf1, 0x35, 0xbf, 0xff, 0xcf, 0xff, 0x00, 0x80, 
	0x00, 0x0c, 0x18, 0x47, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x20, 
	0x07, 0xe1, 0x35, 0xff, 0xff, 0xc7, 0xff, 0x80, 0x80, 0x00, 0x04, 0x18, 0x47, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe4, 0x00, 0x07, 0xc0, 0x3d, 0xff, 0xff, 0xc7, 0xff, 
	0xc0, 0x00, 0x00, 0x04, 0x10, 0x47, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xe4, 0x00, 0x07, 0x80, 0x0d, 0xff, 0xff, 0xcf, 0xff, 0xc0, 0x00, 0x48, 0x04, 0x10, 0x4b, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 0x00, 0x0f, 0x00, 0x0d, 0xff, 0xff, 
	0xef, 0xff, 0xe0, 0x00, 0xcc, 0x04, 0x30, 0x4b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc8, 0x00, 0x1c, 0x00, 0x1d, 0xff, 0xff, 0xc7, 0xff, 0xe0, 0x00, 0xc4, 0x04, 0x20, 
	0x4b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 0x00, 0x38, 0x00, 0x1d, 
	0xff, 0xff, 0xc7, 0xff, 0xe0, 0x00, 0xc4, 0x04, 0x60, 0x5b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc8, 0x00, 0xe0, 0x18, 0x25, 0xff, 0xff, 0x87, 0xff, 0xf0, 0x00, 0x44, 
	0x04, 0x60, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x03, 0x80, 
	0x38, 0x66, 0xff, 0xff, 0xcf, 0xff, 0xe0, 0x00, 0x42, 0x0c, 0xc0, 0xc7, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x0e, 0x03, 0x30, 0x46, 0xff, 0xff, 0xff, 0xff, 0xe2, 
	0x00, 0x40, 0x08, 0xc0, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xec, 
	0x38, 0x0e, 0x70, 0xc2, 0xff, 0xff, 0xff, 0xff, 0xc2, 0x00, 0x20, 0x08, 0x81, 0x8f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xec, 0x70, 0x38, 0x70, 0x82, 0xff, 0xff, 0xff, 
	0xff, 0xc3, 0x00, 0x20, 0x09, 0x01, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xe9, 0xc6, 0x70, 0x61, 0x83, 0x7f, 0xff, 0xff, 0xff, 0x83, 0x00, 0x20, 0x11, 0x03, 0x3f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x09, 0xe2, 0x61, 0x01, 0x7f, 
	0xff, 0xff, 0xff, 0x63, 0x00, 0x20, 0x00, 0x04, 0x7d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe2, 0x03, 0xc4, 0x42, 0x01, 0xbf, 0xff, 0xff, 0xfe, 0x43, 0x00, 0x00, 0x00, 
	0x08, 0x7d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe4, 0x07, 0x8c, 0x82, 
	0x00, 0xbf, 0xff, 0xff, 0xfc, 0x82, 0x00, 0x00, 0x00, 0x06, 0x7d, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0x88, 0x04, 0x00, 0x9f, 0xff, 0xff, 0xfb, 0x02, 0x00, 
	0x00, 0x00, 0x0e, 0x7b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f, 
	0x18, 0x0c, 0x00, 0x5f, 0xff, 0xff, 0xf2, 0x02, 0x00, 0x00, 0x00, 0x1e, 0x7b, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc4, 0x1f, 0x10, 0x1c, 0x00, 0x6f, 0xff, 0xff, 0xe6, 
	0x06, 0x3a, 0x00, 0x00, 0x3e, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xcc, 0x1e, 0x30, 0x38, 0x00, 0x2f, 0xff, 0xff, 0xcc, 0x0c, 0x3b, 0x00, 0x00, 0x76, 0x77, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x98, 0xbc, 0x30, 0x70, 0x00, 0x37, 0xff, 
	0xff, 0x98, 0x08, 0x39, 0x00, 0x00, 0x7e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x90, 0xbc, 0x70, 0xf0, 0x00, 0x1b, 0xff, 0xff, 0x70, 0x08, 0x39, 0x80, 0x00, 0x6e, 
	0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb1, 0xf8, 0x60, 0x70, 0x00, 
	0x0c, 0xf7, 0xfc, 0xe0, 0x08, 0x38, 0x80, 0x00, 0x5e, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x31, 0xe0, 0x40, 0x60, 0x00, 0x06, 0x77, 0xf9, 0xe0, 0x08, 0x38, 0x80, 
	0x00, 0x1e, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x23, 0xe0, 0xc0, 
	0xc0, 0x00, 0x03, 0x37, 0xe6, 0x40, 0x08, 0x78, 0x50, 0x00, 0x3e, 0xfd, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x23, 0xc0, 0x80, 0x80, 0x00, 0x01, 0x97, 0x0c, 0x40, 0x08, 
	0x78, 0x50, 0x00, 0x3e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x63, 
	0x81, 0x81, 0x80, 0x00, 0x00, 0xc2, 0x30, 0x00, 0x18, 0x78, 0x78, 0x04, 0x7e, 0xfe, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x66, 0x81, 0x01, 0x80, 0x00, 0x00, 0x70, 0xe0, 
	0x80, 0x18, 0x78, 0x38, 0x02, 0x3e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x6e, 0x81, 0x03, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x18, 0x60, 0x38, 0x03, 0x1e, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6e, 0x01, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x10, 0x60, 0x1c, 0x01, 0x9c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x6e, 0x01, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x60, 0x1c, 0x00, 
	0xcc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6e, 0x11, 0x05, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x40, 0x1c, 0x00, 0x6c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x6e, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x30, 0x00, 
	0x0c, 0xc0, 0x34, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 
	0x1e, 0x00, 0x00, 0x21, 0x00, 0x00, 0xc2, 0x78, 0x00, 0x0c, 0xf0, 0x30, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 
	0xe8, 0x00, 0x0c, 0x78, 0x18, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x00, 0x3c, 0x20, 0x00, 0x00, 0x90, 0x1d, 0xb4, 0xc0, 0x00, 0x04, 0x7c, 0x18, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3d, 0x20, 0x00, 0x32, 0x10, 
	0x1f, 0xec, 0xf0, 0x00, 0x04, 0x7e, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x1f, 0x6c, 0xf0, 0xf3, 0x13, 0x1e, 0xfc, 0xf8, 0x02, 0x04, 0x3f, 0x0e, 
	0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xcf, 0xf9, 
	0xff, 0xc2, 0x3c, 0xfd, 0xf8, 0x02, 0x04, 0x1f, 0x0e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xf0, 0x02, 0x04, 
	0x0f, 0x87, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f, 
	0xff, 0xff, 0xff, 0xf7, 0xff, 0xf7, 0xd8, 0x04, 0x00, 0x5f, 0x87, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0xf7, 0xbf, 0xff, 0xf8, 
	0x0c, 0x00, 0xdf, 0x87, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xc0, 0x07, 0xef, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xf8, 0x18, 0x00, 0xff, 0xa7, 0x17, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xdf, 
	0xff, 0xf0, 0x31, 0x20, 0xff, 0xa7, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf2, 0x60, 0xff, 0x67, 0xfb, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0xe6, 0x60, 0xff, 0xef, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x23, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xfc, 0xc0, 0xff, 
	0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x3b, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf9, 0xc0, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdc, 0x73, 
	0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd8, 
	0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd8, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0x3f, 0x89, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xd8, 0x67, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x19, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x0e, 0x39, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xde, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3b, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x1f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xdc, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xcf, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
  };

  EPD_SendBitmapData((const unsigned char *)myBitmap, sizeof(myBitmap)); // Send bitmap data to the display

  // You can add delay here if needed
  delay(5000); // Delay for 5 seconds before refreshing the display
}