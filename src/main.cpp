//Generic TFT_eSPI@^2.5.43 use with lvgl(8.4) and xtp2046_touchscreen(alpha) with st7796 driver in Arduinoo framework on platformio
//move .h files to respective lib/x path

#include <Arduino.h>

#include <UIHandler.h>
UIHandler* uiHandler;

void setup() {
    Serial.begin(115200);

    uiHandler = UIHandler::getInstance();
    uiHandler->init();

    
}

void loop() {
    uiHandler->lvTimerHandler();
}