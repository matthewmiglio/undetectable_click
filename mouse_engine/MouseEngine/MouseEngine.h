#pragma once

#include <windows.h>

#ifdef MOUSEENGINE_EXPORTS
#define MOUSEENGINE_API __declspec(dllexport)
#else
#define MOUSEENGINE_API __declspec(dllimport)
#endif

extern "C" {
    MOUSEENGINE_API void move_mouse_humanlike(int x, int y, double randomness, double speed);
    MOUSEENGINE_API void click_mouse(bool left_button, int delay_ms);
    MOUSEENGINE_API void press_key(WORD key_code, int delay_ms);
    MOUSEENGINE_API void press_key_combo(WORD* key_codes, int count, int delay_between_keys);
}
