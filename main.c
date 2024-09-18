#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #error "This program only works on Windows!"
#endif

typedef struct {
    float x, y;
} Vec2;

int main() {
    INPUT input = {0};
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    input.type = INPUT_MOUSE;

    POINT last_pos = {0}, mouse_pos;
    int paused = 0, time = 0;
    int window_size_x = GetSystemMetrics(SM_CXSCREEN);
    int window_size_y = GetSystemMetrics(SM_CYSCREEN);

    SetCursorPos(window_size_x / 2, window_size_y / 2);
    GetCursorPos(&last_pos);

    while (1) {
        GetCursorPos(&mouse_pos);
        int x = window_size_x / 2 + cos(time * 0.013) * 200;
        int y = window_size_y / 2 + sin(time * 0.013) * 200;

        if (mouse_pos.x != last_pos.x || mouse_pos.y != last_pos.y) {
            paused = 1;
            time = 0;
        }

        if (paused && time < 1000) {
            GetCursorPos(&last_pos);
            Sleep(25);
            time++;
            continue;
        }

        if (time % 200 == 0) {
            SendInput(1, &input, sizeof(INPUT));
        }

        paused = 0;
        SetCursorPos(x, y);
        last_pos.x = x;
        last_pos.y = y;

        time++;
        Sleep(25);
    }

    return 0;
}
