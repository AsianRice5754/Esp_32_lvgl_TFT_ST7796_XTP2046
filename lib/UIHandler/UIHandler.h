#ifndef UIHandler_h
#define UIHandler_h

#include <Arduino.h>
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

class UIHandler{
    private:
        UIHandler();
        static UIHandler* instance;
        // Pin definitions
        const int CS_PIN = 5;
        const int TIRQ_PIN = 26;

        // Screen resolution, adjust to specs
        static const int TFT_HOR_RES = 480;
        static const int TFT_VER_RES = 320;

        int counter;
        lv_obj_t *counter_label;

        TFT_eSPI tft;
        XPT2046_Touchscreen* ts;

        static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
        static void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
        static void update_counter_label();
        static void event_handler(lv_event_t *e);

    public:
        static UIHandler* getInstance();
        void init();
        void lvTimerHandler();

};

#endif