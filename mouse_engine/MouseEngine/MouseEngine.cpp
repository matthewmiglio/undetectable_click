#include "pch.h"
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>

extern "C" {
    __declspec(dllexport) void move_mouse_humanlike(int x, int y, double randomness, double speed);
    __declspec(dllexport) void click_mouse(bool left_button, int delay_ms);
}

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
