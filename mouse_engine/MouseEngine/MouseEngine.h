#pragma once

#include <windows.h>

#ifdef MOUSEENGINE_EXPORTS
#define MOUSEENGINE_API __declspec(dllexport)
#else
#define MOUSEENGINE_API __declspec(dllimport)
#endif

extern "C"
{
    MOUSEENGINE_API void move_mouse_humanlike(
        int x,
        int y,
        double base_randomness,
        double base_speed,
        double randomness_gradient_randomness,
        double speed_gradient_randomness,
        int curve_count,
        double curve_severity,
        double curve_severity_randomness,
        double curve_time_randomness);

    MOUSEENGINE_API void click_mouse(bool left_button, int delay_ms);
    MOUSEENGINE_API void press_key(WORD key_code, int delay_ms);
    MOUSEENGINE_API void press_key_combo(WORD *key_codes, int count, int delay_between_keys);
}
