#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/display/lv_display.h"
#include "liblvgl/llemu.hpp"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/misc/lv_types.h"
#include "liblvgl/widgets/image/lv_image.h"

lv_obj_t *img = nullptr;

inline void black_background() { lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), 0); }

void leftScreenButton();
void rightScreenButton();
void displayImage(); 

// Hide (or rather delete) the image when clicked
void hideImage(lv_event_t *e) {
    if (img) {
        lv_obj_delete(img);  // delete it entirely instead of hiding
        img = nullptr;
    }

    // Re-enable the PROS LCD
    pros::lcd::initialize(); 
    pros::lcd::register_btn0_cb(leftScreenButton);
    pros::lcd::register_btn1_cb(displayImage);
    pros::lcd::register_btn2_cb(rightScreenButton);
}

void displayImage() {
    pros::lcd::shutdown();  // disable LCD
    black_background();

    LV_IMAGE_DECLARE(speedzappers_logo_rotated);

    // Create image object
    img = lv_image_create(lv_screen_active());
    lv_image_set_src(img, &speedzappers_logo_rotated);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    // Make image clickable
    lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);

    // Attach event to delete it on tap
    lv_obj_add_event_cb(img, hideImage, LV_EVENT_CLICKED, nullptr);
}