#include <stdint.h>

#include "settings.h"
#include "settings_eeprom.h"
#include "settings_internal.h"
#include "ui.h"
#include "receiver_spi.h"
#include "receiver.h"
#include "touchpad.h"





namespace Ui {

//    TTVout display;

//    bool shouldDrawUpdate = false;
//    bool shouldDisplay = false;
//    bool shouldFullRedraw = false;
    bool isTvOn = false;

    // Refresh rate is set to match touchpad rate.  Refresh every 50ms (20 FPS)
//    Timer UiRefreshTimer = Timer(50);
    // UI time for return to FPV
    Timer UiTimeOut = Timer(3000);

    int XRES = 324;
    int YRES = 224;
    CompositeGraphics display(XRES, YRES);
    CompositeOutput composite(CompositeOutput::NTSC, XRES * 2, YRES * 2);
    Image<CompositeGraphics> luni0(luni::xres, luni::yres, luni::pixels);
//    Font<CompositeGraphics> font(6, 8, font6x8::pixels);
    Font<CompositeGraphics> font(8, 8, font8x8::pixels);

    void setup() {
        // tone will not work until begin is called.
//        display.begin(SC_448x216); // 72 MHz
//        display.end();  

    //highest clockspeed needed
    rtc_clk_cpu_freq_set(RTC_CPU_FREQ_240M);
    
    //initializing DMA buffers and I2S
    composite.init();
    //initializing graphics double buffer
    display.init();
    composite.stopOutput(); //stop i2s driver (no video output)
    //select font
    display.setFont(font);

    //running composite output pinned to first core
    xTaskCreatePinnedToCore(compositeCore, "c", 1024, NULL, 1, NULL, 0);
    //rendering the actual graphics in the main loop is done on the second core by default
    
    }    

    void update() {

        drawCursor();
        
//            draw();
    }


    void draw()
    {
      //clearing background and starting to draw
//      display.begin(0);
      //drawing an image
//      luni0.draw(graphics, 200, 10);
    
      //drawing a frame
      display.fillRect(27, 18, 160, 30, 10);
      display.rect(27, 18, 160, 30, 20);
    
      //setting text color, transparent background
      display.setTextColor(50);
      //text starting position
      display.setCursor(30, 20);
      //printing some lines of text
      display.print("hello!");
      display.print(" free memory: ");
      display.print((int)heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
      display.print("\nrendered frame: ");
      static int frame = 0;
      display.print(frame, 10, 4); //base 10, 6 characters 
      display.print("\n        in hex: ");
      display.print(frame, 16, 4);
      frame++;
    
      //drawing some lines
      for(int i = 0; i <= 100; i++)
      {
        display.line(50, i + 60, 50 + i, 160, i / 2);
        display.line(150, 160 - i, 50 + i, 60, i / 2);
      }
      
      //draw single pixel
      display.dot(20, 190, 10);
      
      //finished drawing, swap back and front buffer to display it
//      display.end();
    
    }

    void compositeCore(void *data)
    {
      while (true)
      {
        //just send the graphics frontbuffer whithout any interruption 
        composite.sendFrameHalfResolution(&display.frame);
      }
    }

    void tvOn() {

        ReceiverSpi::setPowerDownRegister(0b01010000110000010011);
        
        composite.startOutput();
//        display.begin(SC_448x216); // 72 MHz
        
        isTvOn = true;
    }

    void tvOff() { 

        ReceiverSpi::setPowerDownRegister(0b00010000110000010011);

        Receiver::setChannel(Receiver::activeChannel);
        
        composite.stopOutput();
//        display.end();   
         
        isTvOn = false;
    }

    // This needs to be redone with a fill triangle... which needs to be added to the TTVout lib.
    void drawCursor() {

//        // Black inner
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX, TouchPad::touchData.cursorY + 16, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+1, TouchPad::touchData.cursorY + 16, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+2, TouchPad::touchData.cursorY + 15, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+3, TouchPad::touchData.cursorY + 14, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+4, TouchPad::touchData.cursorY + 13, BLACK);
//        
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+6, TouchPad::touchData.cursorY + 18, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+7, TouchPad::touchData.cursorY + 18, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+8, TouchPad::touchData.cursorY + 17, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+9, TouchPad::touchData.cursorY + 17, BLACK);
//        
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+7, TouchPad::touchData.cursorY + 13, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+8, TouchPad::touchData.cursorY + 13, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+9, TouchPad::touchData.cursorY + 13, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+10, TouchPad::touchData.cursorY + 13, BLACK);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+11, TouchPad::touchData.cursorY + 13, BLACK);
//        
//        // White boarder
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX, TouchPad::touchData.cursorY + 16, WHITE);
//        display.draw_line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY + 16, TouchPad::touchData.cursorX + 4, TouchPad::touchData.cursorY + 13, WHITE);
//        display.draw_line(TouchPad::touchData.cursorX + 4, TouchPad::touchData.cursorY + 13, TouchPad::touchData.cursorX + 6, TouchPad::touchData.cursorY + 18, WHITE);
//        display.draw_line(TouchPad::touchData.cursorX + 6, TouchPad::touchData.cursorY + 18, TouchPad::touchData.cursorX + 9, TouchPad::touchData.cursorY + 17, WHITE);
//        display.draw_line(TouchPad::touchData.cursorX + 9, TouchPad::touchData.cursorY + 17, TouchPad::touchData.cursorX + 7, TouchPad::touchData.cursorY + 13, WHITE);
//        display.draw_line(TouchPad::touchData.cursorX + 7, TouchPad::touchData.cursorY + 13, TouchPad::touchData.cursorX + 11, TouchPad::touchData.cursorY + 12, WHITE);
//        display.draw_line(TouchPad::touchData.cursorX + 11, TouchPad::touchData.cursorY + 12, TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, WHITE);
        
        // Black inner
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX, TouchPad::touchData.cursorY + 16, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+1, TouchPad::touchData.cursorY + 16, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+2, TouchPad::touchData.cursorY + 15, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+3, TouchPad::touchData.cursorY + 14, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+4, TouchPad::touchData.cursorY + 13, 10);
        
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+6, TouchPad::touchData.cursorY + 18, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+7, TouchPad::touchData.cursorY + 18, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+8, TouchPad::touchData.cursorY + 17, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+9, TouchPad::touchData.cursorY + 17, 10);
        
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+7, TouchPad::touchData.cursorY + 13, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+8, TouchPad::touchData.cursorY + 13, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+9, TouchPad::touchData.cursorY + 13, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+10, TouchPad::touchData.cursorY + 13, 10);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX+11, TouchPad::touchData.cursorY + 13, 10);
        
        // White boarder
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, TouchPad::touchData.cursorX, TouchPad::touchData.cursorY + 16, 100);
        display.line(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY + 16, TouchPad::touchData.cursorX + 4, TouchPad::touchData.cursorY + 13, 100);
        display.line(TouchPad::touchData.cursorX + 4, TouchPad::touchData.cursorY + 13, TouchPad::touchData.cursorX + 6, TouchPad::touchData.cursorY + 18, 100);
        display.line(TouchPad::touchData.cursorX + 6, TouchPad::touchData.cursorY + 18, TouchPad::touchData.cursorX + 9, TouchPad::touchData.cursorY + 17, 100);
        display.line(TouchPad::touchData.cursorX + 9, TouchPad::touchData.cursorY + 17, TouchPad::touchData.cursorX + 7, TouchPad::touchData.cursorY + 13, 100);
        display.line(TouchPad::touchData.cursorX + 7, TouchPad::touchData.cursorY + 13, TouchPad::touchData.cursorX + 11, TouchPad::touchData.cursorY + 12, 100);
        display.line(TouchPad::touchData.cursorX + 11, TouchPad::touchData.cursorY + 12, TouchPad::touchData.cursorX, TouchPad::touchData.cursorY, 100);

        display.setCursor(TouchPad::touchData.cursorX, TouchPad::touchData.cursorY);
        display.print("[");
        display.print(TouchPad::touchData.cursorX);
        display.print(", ");
        display.print(TouchPad::touchData.cursorY);
        display.print("]");
        
    }

//    void beep() { 
//        uint16_t freq = 5000; // frequency in Hz
//        display.tone(freq, BEEPER_CHIRP);
//    }
//    void beep(uint16_t freq) { 
//        display.tone(freq, BEEPER_CHIRP);
//    }

//    void drawGraph(
//        const uint8_t data[],
//        const uint8_t dataSize,
//        const uint8_t dataScale,
//        const uint8_t x,
//        const uint8_t y,
//        const uint8_t w,
//        const uint8_t h
//    ) {
//        #define SCALE_DATAPOINT(p) (p * (float)h / (float)dataScale)
//        #define CLAMP_DATAPOINT(p) (p > (float)dataScale) ? (float)dataScale : ((p < 0) ? 0 : p);
//
//        Ui::clearRect(x, y, w, h);
//        
//        const float xScaler = (float)w / ((float)dataSize - 1);
//        const float xScalarMissing = (float)w - (xScaler * ((float)dataSize - 1));
//
//        float xNext = (float)x;
//
//        for (uint8_t i = 0; i < dataSize - 1; i++) {
//            const float dataPoint = CLAMP_DATAPOINT((float)data[i]);
//            const float dataPointNext = CLAMP_DATAPOINT((float)data[i + 1]);
//
//            // Need to invert the heights so it shows the right way on the screen.
//            const float dataPointHeight = (float)h - SCALE_DATAPOINT((float)dataPoint);
//            const float dataPointNextHeight = (float)h - SCALE_DATAPOINT((float)dataPointNext);
//
//            const float xEnd = xNext + xScaler + (i == 0 || i == dataSize - 2 ? (xScalarMissing + 1) / 2 : 0);
//            
//              #ifdef OLED_128x64_ADAFRUIT_SCREENS
//                display.drawLine(
//                    xNext,
//                    y + dataPointHeight,
//                    xEnd,
//                    y + dataPointNextHeight,
//                    WHITE
//                );
//              #endif
//              #ifdef TVOUT_SCREENS
//                display.draw_line(
//                    xNext,
//                    y + dataPointHeight,
//                    xEnd,
//                    y + dataPointNextHeight,
//                    WHITE
//                );
//              #endif
//            xNext = xEnd;
//        }
//
//        #undef SCALE_DATAPOINT
//        #undef CLAMP_DATAPOINT
//    }
//
//    void drawSolidGraph(
//        const uint8_t data[],
//        const uint8_t dataSize,
//        const uint8_t dataScale,
//        const uint8_t x,
//        const uint8_t y,
//        const uint8_t w,
//        const uint8_t h
//    ) {
//        #define SCALE_DATAPOINT(p) (p * (float)h / (float)dataScale)
//        #define CLAMP_DATAPOINT(p) (p > (float)dataScale) ? (float)dataScale : ((p < 0) ? 0 : p);
//        
//        const float xScaler = (float)w / ((float)dataSize - 1);
//        const float xScalarMissing = (float)w - (xScaler * ((float)dataSize - 1));
//
//        float xNext = (float)x;
//
//        for (uint8_t i = 0; i < dataSize - 1; i++) {
//            const float dataPoint = CLAMP_DATAPOINT((float)data[i]);
//            const float dataPointNext = CLAMP_DATAPOINT((float)data[i + 1]);
//
//            // Need to invert the heights so it shows the right way on the screen.
//            const float dataPointHeight = (float)h - SCALE_DATAPOINT((float)dataPoint);
//            const float dataPointNextHeight = (float)h - SCALE_DATAPOINT((float)dataPointNext);
//
//            const float xEnd = xNext + xScaler + (i == 0 || i == dataSize - 2 ? (xScalarMissing + 1) / 2 : 0);
//
//            const float m = (dataPointNextHeight - dataPointHeight) / (xEnd - xNext);
//            
//            for (float j = xNext; j < xEnd; j=j+1) {
//              float fillPointHeight = dataPointHeight + (j - xNext) * m;
//              if (fillPointHeight < 0) {
//                fillPointHeight = 0;
//                }
//              drawFastVLine((int)j, y, (int)fillPointHeight, BLACK);
//              drawFastVLine((int)j, (int)fillPointHeight, y + h - (int)fillPointHeight, WHITE);
//            }
//            
//            xNext = xEnd;
//        }
//
//        #undef SCALE_DATAPOINT
//        #undef CLAMP_DATAPOINT
//    }
//
//    void drawLine(
//        const int x1,
//        const int y1,
//        const int x2,
//        const int y2,
//        const int color
//    ) {
//          #ifdef TVOUT_SCREENS
//            display.draw_line( x1, y1, x2, y2, WHITE );
//          #endif
//        }
//
//    void drawDashedHLine(
//        const int x,
//        const int y,
//        const int w,
//        const int step
//    ) {
//        for (int i = 0; i < w; i += step) {
//          #ifdef OLED_128x64_ADAFRUIT_SCREENS
//            display.drawFastHLine(x + i, y, step / 2, WHITE);
//          #endif
//          #ifdef TVOUT_SCREENS
//            display.draw_row(y, x + i, x + i + (step / 2), WHITE);
//          #endif
//        }
//    }
//
//    void drawDashedVLine(
//        const int x,
//        const int y,
//        const int h,
//        const int step
//    ) {
//        for (int i = 0; i < h; i += step) {
//          #ifdef OLED_128x64_ADAFRUIT_SCREENS
//            display.drawFastVLine(x, y + i, step / 2, INVERSE);
//          #endif
//          #ifdef TVOUT_SCREENS
//            display.draw_column(x, y + i, y + i + (step / 2), WHITE);
//          #endif
//        }
//    }
//
//    void drawFastHLine(
//        const int x,
//        const int y,
//        const int w,
//        const int color
//    ) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.drawFastHLine(x, y, w, color);
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.draw_row(y, x, x+w, color);
//      #endif
//    }
//
//    void drawFastVLine(
//        const int x,
//        const int y,
//        const int h,
//        const int color
//    ) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.drawFastVLine(x, y, h, color);
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.draw_column(x, y, y+h, color);
//      #endif
//    }
//
//    void drawRect(
//        const int x,
//        const int y,
//        const int w,
//        const int h,
//        const int color
//    ) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
////        display.drawRoundRect(x, y, w, h, r, color);
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.draw_rect(x, y, w, h, color);
//      #endif
//    }
//
//    void drawRoundRect(
//        const int x,
//        const int y,
//        const int w,
//        const int h,
//        const int r,
//        const int color
//    ) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.drawRoundRect(x, y, w, h, r, color);
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.draw_rect(x, y, w, h, color);
//      #endif
//    }
//
//    void fillRect(
//        const int x,
//        const int y,
//        const int w,
//        const int h,
//        const int color
//    ) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.fillRect(x, y, w, h, color);
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.draw_rect(x, y, w, h, color, color);
//      #endif
//    }
//
//    void fillTriangle(
//        const int x0,
//        const int y0,
//        const int x1,
//        const int y1,
//        const int x2,
//        const int y2,
//        const int color
//    ) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.fillTriangle(
//          x0, y0, x1, y1, x2, y2, color
//        );
//      #endif
//      #ifdef TVOUT_SCREENS
//        for (int x=x0; x<=x2; x++) {
//          display.draw_line(x,y0,x1,y1,color);
//        }
//      #endif
//    }
//
//    void drawBitmap(const int x, const int y, const unsigned char *image, const int w, const int h, const int color) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//
//        // draw Bitmap not working.  On the TODO list and remove the below work around.
//        int setColor;
//        for (int i=0; i<w; i++) {
//          for (int j=0; j<h; j++) {
//            setColor = bitRead( image[(j*w+i) / 8], 7 - (j*w+i) % 8 );
//            if (color) {
//              display.drawPixel(x+i, y+j, setColor);
//            } else {
//              display.drawPixel(x+i, y+j, !setColor);
//            }
//          }
//        }
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.bitmap(x, y, image, 0, w, h);
//        if (color == BLACK) {
//          display.draw_rect(x, y, w, h,INVERT,INVERT);
//        }
//      #endif
//    }
//
//    void drawCircle(const int x, const int y,const int r, const int color, const int fillcolor) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.drawCircle(x, y, r, color);
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.draw_circle(x, y, r, color, fillcolor);
//      #endif
//    }
//
//    void drawBullseye(const int x, const int y,const int r, const int color) {
//      drawCircle(x, y, r-2, color, BLACK);
//      drawFastHLine(x, y, 0, color);
//      drawFastHLine(x-r, y, 2*r+1, color);
//      drawFastVLine(x, y-r, 2*r+1, color);
//    }
//    
//    void setTextColor(const int color) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.setTextColor(color);
//      #endif
//      #ifdef TVOUT_SCREENS
//        // No equivalent function
//      #endif
//    }
//    
//    void setTextSize(const int size) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.setTextSize(size); 
//      #endif
//      #ifdef TVOUT_SCREENS
//      //TODO add larger font
//        if (size == 1) {
//          display.select_font(font8x8);
//        }
//        else if (size == 2) {
//          display.select_font(font8x8);
//        }
//        else if (size == 3) {
//          display.select_font(font8x8);
//        }
//        else if (size == 4) {
//          display.select_font(font8x8);
//        }
//        else if (size == 5) {
//          display.select_font(font8x8);
//        }
//        else if (size == 6) {
//          display.select_font(font8x8);
//        }
//        else {
//          display.select_font(font8x8);
//        }        
//      #endif
//    }
//    
//    void setCursor(const int x, const int y) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.setCursor(x,y);
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.set_cursor(x,y);
//      #endif
//    }
//
//    // TODO move print here
//    void print(const char text) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
////        display.print(text);
//      #endif
//      #ifdef TVOUT_SCREENS
////        display.print(text);
//      #endif
//    }

    // font6x8.pixels[] 
    void drawBigCharacter( const int x, const int y, const char text, const int xMultiplier, const int yMultiplier) {
  
        for (uint8_t py=0; py<8; py++) {
            for (uint8_t px=0; px<6; px++) {

                unsigned char colour = font6x8::pixels[(text-32)*8*6 + py*8 + px];
                display.fillRect( x + px * xMultiplier, 
                          y + py * yMultiplier, 
                          xMultiplier, 
                          yMultiplier, 
                          colour/2.55);
            }
        }
  
    }



    
//    void drawBigNumber( const int x, const int y, const int number, const int xMultiplier, const int yMultiplier) {
//        switch (number) {
//            case 0:
//                  drawBigCharacter( x, y, '0', xMultiplier, yMultiplier);
//              break;
//            case 1:
//                  drawBigCharacter( x, y, '1', xMultiplier, yMultiplier);
//              break;
//            case 2:
//                  drawBigCharacter( x, y, '2', xMultiplier, yMultiplier);
//              break;
//            case 3:
//                  drawBigCharacter( x, y, '3', xMultiplier, yMultiplier);
//              break;
//            case 4:
//                  drawBigCharacter( x, y, '4', xMultiplier, yMultiplier);
//              break;
//            case 5:
//                  drawBigCharacter( x, y, '5', xMultiplier, yMultiplier);
//              break;
//            case 6:
//                  drawBigCharacter( x, y, '6', xMultiplier, yMultiplier);
//              break;
//            case 7:
//                  drawBigCharacter( x, y, '7', xMultiplier, yMultiplier);
//              break;
//            case 8:
//                  drawBigCharacter( x, y, '8', xMultiplier, yMultiplier);
//              break;
//            case 9:
//                  drawBigCharacter( x, y, '9', xMultiplier, yMultiplier);
//              break;
//          }
//    }
//          
//    void clear() {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.clearDisplay();
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.clear_screen();
//      #endif
//    }
//
//    void clearRect(const int x, const int y, const int w, const int h) {
//      #ifdef OLED_128x64_ADAFRUIT_SCREENS
//        display.fillRect(x, y, w, h, BLACK);
//      #endif
//      #ifdef TVOUT_SCREENS
//        display.draw_rect(x, y, w, h,BLACK,BLACK);
//      #endif
//    }
//          
//    void needUpdate() {
//        shouldDrawUpdate = true;
//    }
//
//    void needDisplay() {
//        shouldDisplay = true;
//    }
//
//    void needFullRedraw() {
//        shouldFullRedraw = true;
//    }
}


