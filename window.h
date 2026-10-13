
#pragma once

#include "raylib.h"

enum class WindowType
{
    Home,
    Settings
};

struct NanoWindow
{
    int id = 0;

    WindowType type = WindowType::Home;
    const char* title = "Window";

    Rectangle bounds = { 200, 150, 520, 360 };
    Rectangle restoreBounds = { 200, 150, 520, 360 };

    float animation = 0.0f;

    bool closing = false;
    bool minimized = false;
    bool maximized = false;
    bool dragging = false;
};

void DrawNanoWindow(const NanoWindow& window);