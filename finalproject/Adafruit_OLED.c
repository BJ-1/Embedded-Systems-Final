
// Standard includes
#include <string.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_ints.h"
#include "gpio.h"
#include "spi.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "prcm.h"
#include "uart.h"
#include "interrupt.h"

// Common interface includes
#include "uart_if.h"
//#include "pinmux.h"
#include "pinmux.h"

#include "Adafruit_SSD1351.h"
#include "Adafruit_GFX.h"

//*****************************************************************************


/* These functions are based on the Arduino test program at
*  https://github.com/adafruit/Adafruit-SSD1351-library/blob/master/examples/test/test.ino
*
*  You can use these high-level routines to implement your
*  test program.
*/

// TODO Configure SPI port and use these libraries to implement
// an OLED test program. See SPI example program.


#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"

extern int cursor_x;
extern int cursor_y;

float p = 3.1415926;

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define GREEN           0x07E0
#define CYAN            0x07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

//*****************************************************************************
//  function delays 3*ulCount cycles
void delay(unsigned long ulCount){
    int i;

  do{
    ulCount--;
        for (i=0; i< 65535; i++) ;
    }while(ulCount);
}


//*****************************************************************************
void testfastlines(unsigned int color1, unsigned int color2) {
    unsigned int x;
    unsigned int y;

   fillScreen(BLACK);
   for (y=0; y < height()-1; y+=8) {
     drawFastHLine(0, y, width()-1, color1);
   }
     delay(100);
   for (x=0; x < width()-1; x+=8) {
     drawFastVLine(x, 0, height()-1, color2);
   }
     delay(100);
}

//*****************************************************************************

void testdrawrects(unsigned int color) {
    unsigned int x;

 fillScreen(BLACK);
 for (x=0; x < height()-1; x+=6) {
   drawRect((width()-1)/2 -x/2, (height()-1)/2 -x/2 , x, x, color);
     delay(10);
 }
}

//*****************************************************************************

void fillcircles(unsigned long w, unsigned long h, unsigned char radius, unsigned int color) {
    unsigned char x;
    unsigned char y;

  for (x=radius; x < w; x+=radius*2) {
    for (y=radius; y < h; y+=radius*2) {
      fillCircle(x, y, radius, color);
            delay(10);
    }
  }
}

//*****************************************************************************

void testfillcircles(unsigned char radius, unsigned int color) {
    unsigned char x;
    unsigned char y;

  for (x=radius; x < width()-1; x+=radius*2) {
    for (y=radius; y < height()-1; y+=radius*2) {
      fillCircle(x, y, radius, color);
            delay(10);
    }
  }
}

//*****************************************************************************

void testdrawcircles(unsigned char radius, unsigned int color) {
    unsigned char x;
    unsigned char y;

  for (x=0; x < width()-1+radius; x+=radius*2) {
    for (y=0; y < height()-1+radius; y+=radius*2) {
      drawCircle(x, y, radius, color);
            delay(10);
    }
  }
}


void testtriangles() {
  int color = 0xF800;
  int t;
  int w = width()/2;
  int x = height()-1;
  int y = 0;
  int z = width()-1;

  fillScreen(BLACK);
  for(t = 0 ; t <= 15; t+=1) {
    drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
        delay(10);
  }
}

//*****************************************************************************

void testroundrects() {
  int color = 100;

    int i;
  int x = 0;
  int y = 0;
  int w = width();
  int h = height();

  fillScreen(BLACK);

  for(i = 0 ; i <= 24; i++) {
    drawRoundRect(x, y, w, h, 5, color);
    x+=2;
    y+=3;
    w-=4;
    h-=6;
    color+=1100;
  }
}

//*****************************************************************************
void testlines(unsigned int color) {
    unsigned int x;
    unsigned int y;

   fillScreen(BLACK);
   for (x=0; x < width()-1; x+=6) {
     drawLine(0, 0, x, height()-1, color);
   }
     delay(10);
   for (y=0; y < height()-1; y+=6) {
     drawLine(0, 0, width()-1, y, color);
   }
     delay(100);

   fillScreen(BLACK);
   for (x=0; x < width()-1; x+=6) {
     drawLine(width()-1, 0, x, height()-1, color);
   }
     delay(100);
   for (y=0; y < height()-1; y+=6) {
     drawLine(width()-1, 0, 0, y, color);
   }
     delay(100);

   fillScreen(BLACK);
   for (x=0; x < width()-1; x+=6) {
     drawLine(0, height()-1, x, 0, color);
   }
     delay(100);
   for (y=0; y < height()-1; y+=6) {
     drawLine(0, height()-1, width()-1, y, color);
   }
     delay(100);

   fillScreen(BLACK);
   for (x=0; x < width()-1; x+=6) {
     drawLine(width()-1, height()-1, x, 0, color);
   }
     delay(100);
   for (y=0; y < height()-1; y+=6) {
     drawLine(width()-1, height()-1, 0, y, color);
   }
     delay(100);

}

//*****************************************************************************

void lcdTestPattern(void)
{
  unsigned int i,j;
  goTo(0, 0);

  for(i=0;i<128;i++)
  {
    for(j=0;j<128;j++)
    {
      if(i<16){writeData(RED>>8); writeData((unsigned char) RED);}
      else if(i<32) {writeData(YELLOW>>8);writeData((unsigned char) YELLOW);}
      else if(i<48){writeData(GREEN>>8);writeData((unsigned char) GREEN);}
      else if(i<64){writeData(CYAN>>8);writeData((unsigned char) CYAN);}
      else if(i<80){writeData(BLUE>>8);writeData((unsigned char) BLUE);}
      else if(i<96){writeData(MAGENTA>>8);writeData((unsigned char) MAGENTA);}
      else if(i<112){writeData(BLACK>>8);writeData((unsigned char) BLACK);}
      else {writeData(WHITE>>8); writeData((unsigned char) WHITE);}
    }
  }
}
/**************************************************************************/
void lcdTestPattern2(void)
{
  unsigned int i,j;
  goTo(0, 0);

  for(i=0;i<128;i++)
  {
    for(j=0;j<128;j++)
    {
      if(j<16){writeData(RED>>8); writeData((unsigned char) RED);}
      else if(j<32) {writeData(YELLOW>>8);writeData((unsigned char) YELLOW);}
      else if(j<48){writeData(GREEN>>8);writeData((unsigned char) GREEN);}
      else if(j<64){writeData(CYAN>>8);writeData((unsigned char) CYAN);}
      else if(j<80){writeData(BLUE>>8);writeData((unsigned char) BLUE);}
      else if(j<96){writeData(MAGENTA>>8);writeData((unsigned char) MAGENTA);}
      else if(j<112){writeData(BLACK>>8);writeData((unsigned char) BLACK);}
      else {writeData(WHITE>>8);writeData((unsigned char) WHITE);}
    }
  }
}

/**************************************************************************/


void writeCommand(unsigned char c) {

//TODO 1
/* Write a function to send a command byte c to the OLED via
*  SPI.
*/

        unsigned long ulDummy;

        MAP_SPICSEnable(GSPI_BASE);

        // DC
        GPIOPinWrite(GPIOA1_BASE, 0x2, 0x00);
        // CS
        GPIOPinWrite(GPIOA2_BASE, 0x40, 0x00);

        // Push the character over SPI

        MAP_SPIDataPut(GSPI_BASE, c);

        //
        // Clean up the receive register into a dummy
        // variable
        //
        MAP_SPIDataGet(GSPI_BASE,&ulDummy);

        // CS
        GPIOPinWrite(GPIOA2_BASE, 0x40, 0x40);


        // Disable chip select

        MAP_SPICSDisable(GSPI_BASE);


}
//*****************************************************************************

void writeData(unsigned char c) {

//TODO 2
/* Write a function to send a data byte c to the OLED via
*  SPI.
*/
    unsigned long ulDummy;

        MAP_SPICSEnable(GSPI_BASE);

        // CS
        GPIOPinWrite(GPIOA2_BASE, 0x40, 0x00);
        // DC
        GPIOPinWrite(GPIOA1_BASE, 0x2, 0x2);

        // Push the character over SPI

        MAP_SPIDataPut(GSPI_BASE, c);

        //
        // Clean up the receive register into a dummy
        // variable
        //
        MAP_SPIDataGet(GSPI_BASE, &ulDummy);

        // CS
        GPIOPinWrite(GPIOA2_BASE, 0x40, 0x40);


        // Disable chip select

        MAP_SPICSDisable(GSPI_BASE);

}

//*****************************************************************************
void Adafruit_Init(void){

//TODO 3
/* NOTE: This function assumes that the RESET pin of the 
*  OLED has been wired to GPIO28, pin 18 (P2.2). If you 
*  use a different pin for the OLED reset, then you should
*  update the GPIOPinWrite commands below that set RESET 
*  high or low.
*/

  volatile unsigned long delay;

  GPIOPinWrite(GPIOA3_BASE, 0x10, 0);	// RESET = RESET_LOW

  for(delay=0; delay<100; delay=delay+1);// delay minimum 100 ns

  GPIOPinWrite(GPIOA3_BASE, 0x10, 0x10);	// RESET = RESET_HIGH

	// Initialization Sequence
  writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
  writeData(0x12);
  writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
  writeData(0xB1);

  writeCommand(SSD1351_CMD_DISPLAYOFF);  		// 0xAE

  writeCommand(SSD1351_CMD_CLOCKDIV);  		// 0xB3
  writeCommand(0xF1);  						// 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)

  writeCommand(SSD1351_CMD_MUXRATIO);
  writeData(127);

  writeCommand(SSD1351_CMD_SETREMAP);
  writeData(0x74);

  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(0x00);
  writeData(0x7F);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(0x00);
  writeData(0x7F);

  writeCommand(SSD1351_CMD_STARTLINE); 		// 0xA1
  if (SSD1351HEIGHT == 96) {
    writeData(96);
  } else {
    writeData(0);
  }


  writeCommand(SSD1351_CMD_DISPLAYOFFSET); 	// 0xA2
  writeData(0x0);

  writeCommand(SSD1351_CMD_SETGPIO);
  writeData(0x00);

  writeCommand(SSD1351_CMD_FUNCTIONSELECT);
  writeData(0x01); // internal (diode drop)
  //writeData(0x01); // external bias

//    writeCommand(SSSD1351_CMD_SETPHASELENGTH);
//    writeData(0x32);

  writeCommand(SSD1351_CMD_PRECHARGE);  		// 0xB1
  writeCommand(0x32);

  writeCommand(SSD1351_CMD_VCOMH);  			// 0xBE
  writeCommand(0x05);

  writeCommand(SSD1351_CMD_NORMALDISPLAY);  	// 0xA6

  writeCommand(SSD1351_CMD_CONTRASTABC);
  writeData(0xC8);
  writeData(0x80);
  writeData(0xC8);

  writeCommand(SSD1351_CMD_CONTRASTMASTER);
  writeData(0x0F);

  writeCommand(SSD1351_CMD_SETVSL );
  writeData(0xA0);
  writeData(0xB5);
  writeData(0x55);

  writeCommand(SSD1351_CMD_PRECHARGE2);
  writeData(0x01);

  writeCommand(SSD1351_CMD_DISPLAYON);		//--turn on oled panel
}

/***********************************/

void goTo(int x, int y) {
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT)) return;

  // set x and y coordinate
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(SSD1351WIDTH-1);

  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(SSD1351HEIGHT-1);

  writeCommand(SSD1351_CMD_WRITERAM);
}

unsigned int Color565(unsigned char r, unsigned char g, unsigned char b) {
  unsigned int c;
  c = r >> 3;
  c <<= 6;
  c |= g >> 2;
  c <<= 5;
  c |= b >> 3;

  return c;
}

void fillScreen(unsigned int fillcolor) {
  fillRect(0, 0, SSD1351WIDTH, SSD1351HEIGHT, fillcolor);
}

/**************************************************************************/
/*!
    @brief  Draws a filled rectangle using HW acceleration
*/
/**************************************************************************/
void fillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int fillcolor)
{
  unsigned int i;

  // Bounds check
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
	return;

  // Y bounds check
  if (y+h > SSD1351HEIGHT)
  {
    h = SSD1351HEIGHT - y - 1;
  }

  // X bounds check
  if (x+w > SSD1351WIDTH)
  {
    w = SSD1351WIDTH - x - 1;
  }

  // set location
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(x+w-1);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(y+h-1);
  // fill!
  writeCommand(SSD1351_CMD_WRITERAM);

  for (i=0; i < w*h; i++) {
    writeData(fillcolor >> 8);
    writeData(fillcolor);
  }
}

void drawFastVLine(int x, int y, int h, unsigned int color) {

  unsigned int i;
  // Bounds check
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
	return;

  // X bounds check
  if (y+h > SSD1351HEIGHT)
  {
    h = SSD1351HEIGHT - y - 1;
  }

  if (h < 0) return;

  // set location
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(x);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(y+h-1);
  // fill!
  writeCommand(SSD1351_CMD_WRITERAM);

  for (i=0; i < h; i++) {
    writeData(color >> 8);
    writeData(color);
  }
}



void drawFastHLine(int x, int y, int w, unsigned int color) {

  unsigned int i;
  // Bounds check
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
	return;

  // X bounds check
  if (x+w > SSD1351WIDTH)
  {
    w = SSD1351WIDTH - x - 1;
  }

  if (w < 0) return;

  // set location
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(x+w-1);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(y);
  // fill!
  writeCommand(SSD1351_CMD_WRITERAM);

  for (i=0; i < w; i++) {
    writeData(color >> 8);
    writeData(color);
  }
}




void drawPixel(int x, int y, unsigned int color)
{
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;

  goTo(x, y);

  writeData(color >> 8);
  writeData(color);
}


void  invert(char v) {
   if (v) {
     writeCommand(SSD1351_CMD_INVERTDISPLAY);
   } else {
     	writeCommand(SSD1351_CMD_NORMALDISPLAY);
   }
 }


