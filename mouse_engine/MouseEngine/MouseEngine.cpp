#include "pch.h"
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "MouseEngine.h"


// Helper function to add jitter
int random_jitter(int value, double randomness) {
    return value + (rand() % (int)(randomness * 10) - (randomness * 5));
}

// Simulates human-like mouse movement
void move_mouse_humanlike(int x, int y, double randomness, double speed) {
    POINT current_pos;
    GetCursorPos(&current_pos);

    int start_x = current_pos.x;
    int start_y = current_pos.y;
    int steps = 50; // Number of interpolation steps
    int sleep_time = (int)(speed * 10);

    for (int i = 1; i <= steps; i++) {
        double t = (double)i / steps;
        int interpolated_x = start_x + t * (x - start_x);
        int interpolated_y = start_y + t * (y - start_y);

        // Add jitter
        interpolated_x = random_jitter(interpolated_x, randomness);
        interpolated_y = random_jitter(interpolated_y, randomness);

        SetCursorPos(interpolated_x, interpolated_y);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }

    SetCursorPos(x, y);
}

// Simulates a mouse click
void click_mouse(bool left_button, int delay_ms) {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = left_button ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

    input.mi.dwFlags = left_button ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}


void send_key_event(WORD key_code, DWORD flags) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_code;
    input.ki.dwFlags = flags;
    SendInput(1, &input, sizeof(INPUT));
}

extern "C" void press_key(WORD key_code, int delay_ms) {
    send_key_event(key_code, 0); // key down
    Sleep(delay_ms);
    send_key_event(key_code, KEYEVENTF_KEYUP); // key up
}

extern "C" void press_key_combo(WORD* key_codes, int count, int delay_between_keys) {
    // Press keys down
    for (int i = 0; i < count; i++) {
        send_key_event(key_codes[i], 0);
        Sleep(delay_between_keys);
    }
    // Release keys in reverse order
    for (int i = count - 1; i >= 0; i--) {
        send_key_event(key_codes[i], KEYEVENTF_KEYUP);
        Sleep(delay_between_keys);
    }
}
