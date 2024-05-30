//Generic TFT_eSPI@^2.5.43 use with lvgl(8.4) and xtp2046_touchscreen(alpha) with st7796 driver in Arduinoo framework on platformio
//move .h files to respective lib/x path


#include <XPT2046_Touchscreen.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

// Pin definitions
#define CS_PIN  14
#define TIRQ_PIN  25

// Screen resolution, adjust to specs
#define TFT_HOR_RES 480
#define TFT_VER_RES 320

// Global screen objects
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

// Counter variable for disp
static int counter = 0;

// Label for counter for display
lv_obj_t *counter_label;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
    tft.pushColors((uint16_t *)&color_p->full, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1), true);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    if (ts.touched()) {
        TS_Point p = ts.getPoint();

        // Adjust coordinates to match screen orientation
        p.x = map(p.x, 0, 4095, 0, TFT_HOR_RES);
        p.y = map(p.y, 0, 4095, 0, TFT_VER_RES);

        data->point.x = p.x;
        data->point.y = p.y;
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}
//puts on screen display for counter
void update_counter_label() {
    static char buf[32];
    snprintf(buf, sizeof(buf), "Count: %d", counter);
    lv_label_set_text(counter_label, buf);
}

//button click will +1 to the 
void event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        counter++;
        Serial.println("Hello World");
        update_counter_label();
    }
}

void lv_example(void) {
    // bg color
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

    // Create a button
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

    // label on the button
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Button");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);  // Set text color to white

    // added to have counter on dissplay, ensure event change tft
    counter_label = lv_label_create(lv_scr_act());
    lv_label_set_text(counter_label, "Count: 0");
    lv_obj_set_style_text_color(counter_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);  // Set text color to white
    lv_obj_align(counter_label, LV_ALIGN_CENTER, 0, -50);
}

void setup() {
    Serial.begin(115200);

    // Initialize TFT
    tft.begin();
    tft.setRotation(1); // Landscape mode

    // Initialize Touchscreen
    ts.begin();
    ts.setRotation(1); // Landscape mode

    // Initialize LVGL
    lv_init();

    // Set up display buffer
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf[TFT_HOR_RES * 10];
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, TFT_HOR_RES * 10);

    // Set up display driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_HOR_RES;
    disp_drv.ver_res = TFT_VER_RES;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Set up input driver
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    // Run LVGL example
    lv_example();
}

void loop() {
    // Handle LVGL tasks
    lv_timer_handler();
    delay(5);
}