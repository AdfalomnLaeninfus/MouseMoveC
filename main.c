#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #error "Program dont work on another OS, perhaps on windows!"
#endif

typedef struct vec2 {
    float x;
    float y;
} Vec2;

INPUT input;

int main()
{
    int timer = 0, paused = 0;
    int window_size_x = GetSystemMetrics(SM_CXSCREEN);
    int window_size_y = GetSystemMetrics(SM_CYSCREEN);

    SetThreadExecutionState(ES_CONTINUOUS | ES_AWAYMODE_REQUIRED | ES_SYSTEM_REQUIRED);

    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    input.type = INPUT_MOUSE;

    POINT mouse_pos, last_pos = {0, 0};

    SetCursorPos(window_size_x / 2, window_size_y / 2);
    GetCursorPos(&last_pos);

    while(1)
    {
        int x = window_size_x / 2;
        int y = window_size_y / 2;

        GetCursorPos(&mouse_pos);

        if (mouse_pos.x != last_pos.x || mouse_pos.y != last_pos.y) {
            paused = 1;
            timer = 0;
        }

        if (paused && timer < 500) {
            GetCursorPos(&last_pos);
            Sleep(16);
            timer++;

            continue;
        }

        if (timer % 100 == 0) {
            SendInput(1, &input, sizeof(INPUT));
        }

        paused = 0;

        x += cos(timer / 60.0) * 200;
        y += sin(timer / 60.0) * 200;

        SetCursorPos(x, y);
        last_pos.x = x;
        last_pos.y = y;

        timer++;
        Sleep(16);
    }

    return 0;
}