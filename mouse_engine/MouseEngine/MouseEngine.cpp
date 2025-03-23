#include "pch.h"
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "MouseEngine.h"

// Helper function to add jitter
int random_jitter(int value, double randomness)
{
    return value + (rand() % (int)(randomness * 10) - (randomness * 5));
}

// Simulates human-like mouse movement
void move_mouse_humanlike(
    int x,
    int y,
    double base_randomness,
    double base_speed,
    double randomness_gradient_randomness,
    double speed_gradient_randomness,
    int curve_count,
    double curve_severity,
    double curve_severity_randomness,
    double curve_time_randomness)
{
    POINT current_pos;
    GetCursorPos(&current_pos);

    int start_x = current_pos.x;
    int start_y = current_pos.y;

    double total_dx = x - start_x;
    double total_dy = y - start_y;

    double segment_ratios[100] = {0};
    double total_ratio = 0.0;

    // Randomly split the total curve time using ratio weights
    for (int i = 0; i < curve_count; ++i)
    {
        double base = 1.0 + (((rand() / (double)RAND_MAX) - 0.5) * 2 * curve_time_randomness);
        if (base < 0.1)
            base = 0.1; // Avoid zero-length segments
        segment_ratios[i] = base;
        total_ratio += base;
    }

    double current_x = start_x;
    double current_y = start_y;

    srand((unsigned int)time(NULL)); // Seed RNG once

    for (int c = 0; c < curve_count; c++)
    {
        double progress_ratio = segment_ratios[c] / total_ratio;

        // Target point for this curve
        double target_x = current_x + total_dx * progress_ratio;
        double target_y = current_y + total_dy * progress_ratio;

        // Curve direction randomization
        int direction = (rand() % 2 == 0) ? 1 : -1;

        double severity = curve_severity - ((rand() / (double)RAND_MAX) * curve_severity_randomness);
        if (severity < 0)
            severity = 0;

        double dx = target_x - current_x;
        double dy = target_y - current_y;
        double length = sqrt(dx * dx + dy * dy);

        if (length < 1.0)
            continue;

        double norm_dx = dx / length;
        double norm_dy = dy / length;

        double perp_x = -norm_dy * direction;
        double perp_y = norm_dx * direction;

        double offset_amount = severity * length;
        double control_x = (current_x + target_x) / 2 + perp_x * offset_amount;
        double control_y = (current_y + target_y) / 2 + perp_y * offset_amount;

        // Smooth curve interpolation
        int steps = (int)(length / 4); // Roughly one step per ~4px
        if (steps < 10)
            steps = 10;

        for (int i = 1; i <= steps; i++)
        {
            double t = (double)i / steps;

            // Bezier interpolation
            double xa = current_x + (control_x - current_x) * t;
            double ya = current_y + (control_y - current_y) * t;

            double xb = control_x + (target_x - control_x) * t;
            double yb = control_y + (target_y - control_y) * t;

            double interp_x = xa + (xb - xa) * t;
            double interp_y = ya + (yb - ya) * t;

            // Add jitter
            double randomness_variation = base_randomness + ((rand() / (double)RAND_MAX) - 0.5) * 2 * randomness_gradient_randomness;
            double speed_variation = base_speed + ((rand() / (double)RAND_MAX) - 0.5) * 2 * speed_gradient_randomness;
            if (speed_variation < 0.01)
                speed_variation = 0.01;

            int jittered_x = random_jitter((int)interp_x, randomness_variation);
            int jittered_y = random_jitter((int)interp_y, randomness_variation);

            SetCursorPos(jittered_x, jittered_y);
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(speed_variation * 10)));
        }

        current_x = target_x;
        current_y = target_y;
    }

    SetCursorPos(x, y);
}

// Simulates a mouse click
void click_mouse(bool left_button, int delay_ms)
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = left_button ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

    input.mi.dwFlags = left_button ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void send_key_event(WORD key_code, DWORD flags)
{
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_code;
    input.ki.dwFlags = flags;
    SendInput(1, &input, sizeof(INPUT));
}

extern "C" void press_key(WORD key_code, int delay_ms)
{
    send_key_event(key_code, 0); // key down
    Sleep(delay_ms);
    send_key_event(key_code, KEYEVENTF_KEYUP); // key up
}

extern "C" void press_key_combo(WORD *key_codes, int count, int delay_between_keys)
{
    // Press keys down
    for (int i = 0; i < count; i++)
    {
        send_key_event(key_codes[i], 0);
        Sleep(delay_between_keys);
    }
    // Release keys in reverse order
    for (int i = count - 1; i >= 0; i--)
    {
        send_key_event(key_codes[i], KEYEVENTF_KEYUP);
        Sleep(delay_between_keys);
    }
}
