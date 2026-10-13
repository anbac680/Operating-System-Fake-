
#include "window_manager.h"
#include "animation.h"

#include <vector>

namespace
{
    std::vector<NanoWindow> windows;

    int nextWindowId = 1;
    int draggingId = -1;

    Vector2 dragOffset = { 0.0f, 0.0f };

    constexpr float TITLE_HEIGHT = 42.0f;
    constexpr float CONTROL_WIDTH = 42.0f;

    Rectangle GetControlRect(const NanoWindow& window, int index)
    {
        return {
            window.bounds.x + window.bounds.width
                - CONTROL_WIDTH * (3 - index),
            window.bounds.y,
            CONTROL_WIDTH,
            TITLE_HEIGHT
        };
    }

    void BringToFront(int index)
    {
        if (index < 0 || index >= (int)windows.size())
            return;

        NanoWindow selected = windows[index];

        windows.erase(windows.begin() + index);
        windows.push_back(selected);
    }

    void RestoreWindow(NanoWindow& window)
    {
        window.minimized = false;
        window.closing = false;
        window.animation = 0.0f;
    }

    void UpdateAnimations()
    {
        const float dt = GetFrameTime();

        for (int i = (int)windows.size() - 1; i >= 0; --i)
        {
            NanoWindow& window = windows[i];

            if (window.closing)
            {
                window.animation -= dt * 7.0f;

                if (window.animation <= 0.0f)
                {
                    if (draggingId == window.id)
                        draggingId = -1;

                    windows.erase(windows.begin() + i);
                }
            }
            else if (!window.minimized && window.animation < 1.0f)
            {
                window.animation += dt * 5.0f;

                if (window.animation > 1.0f)
                    window.animation = 1.0f;
            }
        }
    }

    bool RestoreMinimizedWindow(Vector2 mouse)
    {
        float x = 12.0f;
        const float y = (float)GetScreenHeight() - 38.0f;

        for (int i = 0; i < (int)windows.size(); ++i)
        {
            if (!windows[i].minimized)
                continue;

            Rectangle chip = { x, y, 120.0f, 30.0f };

            if (CheckCollisionPointRec(mouse, chip))
            {
                RestoreWindow(windows[i]);
                BringToFront(i);
                return true;
            }

            x += 126.0f;
        }

        return false;
    }
}

void InitWindowManager()
{
    windows.clear();
    nextWindowId = 1;
    draggingId = -1;
}

void OpenNanoWindow(WindowType type)
{
    // Nếu đã tồn tại thì khôi phục và đưa lên trước.
    for (int i = (int)windows.size() - 1; i >= 0; --i)
    {
        if (windows[i].type == type)
        {
            if (windows[i].closing)
            {
                windows[i].closing = false;
                windows[i].animation = 0.0f;
            }

            if (windows[i].minimized)
                RestoreWindow(windows[i]);

            BringToFront(i);
            return;
        }
    }

    NanoWindow window;

    window.id = nextWindowId++;
    window.type = type;
    window.animation = 0.0f;

    if (type == WindowType::Home)
    {
        window.title = "Home";
        window.bounds = { 230, 150, 540, 370 };
    }
    else
    {
        window.title = "Settings";
        window.bounds = { 300, 180, 520, 390 };
    }

    window.restoreBounds = window.bounds;
    windows.push_back(window);
}

void UpdateWindowManager(bool allowMouseInput)
{
    UpdateAnimations();
    if (!allowMouseInput)
        return;

    const Vector2 mouse = GetMousePosition();

    // Tiếp tục kéo cửa sổ khi giữ chuột.
    if (draggingId != -1 &&
        IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        for (NanoWindow& window : windows)
        {
            if (window.id == draggingId &&
                !window.maximized &&
                !window.minimized &&
                !window.closing)
            {
                window.bounds.x = mouse.x - dragOffset.x;
                window.bounds.y = mouse.y - dragOffset.y;
                break;
            }
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        draggingId = -1;

        for (NanoWindow& window : windows)
            window.dragging = false;
    }

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;

    if (RestoreMinimizedWindow(mouse))
        return;

    // Duyệt từ cửa sổ trên cùng xuống dưới.
    for (int i = (int)windows.size() - 1; i >= 0; --i)
    {
        if (windows[i].minimized || windows[i].closing)
            continue;

        if (!CheckCollisionPointRec(mouse, windows[i].bounds))
            continue;

        BringToFront(i);
        NanoWindow& active = windows.back();

        const Rectangle closeButton = GetControlRect(active, 2);
        const Rectangle maxButton = GetControlRect(active, 1);
        const Rectangle minButton = GetControlRect(active, 0);

        if (CheckCollisionPointRec(mouse, closeButton))
        {
            active.closing = true;
            draggingId = -1;
            return;
        }

        if (CheckCollisionPointRec(mouse, maxButton))
        {
            if (!active.maximized)
            {
                active.restoreBounds = active.bounds;

                active.bounds = {
                    16.0f, 16.0f,
                    (float)GetScreenWidth() - 32.0f,
                    (float)GetScreenHeight() - 96.0f
                };

                active.maximized = true;
            }
            else
            {
                active.bounds = active.restoreBounds;
                active.maximized = false;
            }

            return;
        }

        if (CheckCollisionPointRec(mouse, minButton))
        {
            active.minimized = true;
            active.dragging = false;
            draggingId = -1;
            return;
        }

        Rectangle titleBar = {
            active.bounds.x,
            active.bounds.y,
            active.bounds.width - CONTROL_WIDTH * 3.0f,
            TITLE_HEIGHT
        };

        if (CheckCollisionPointRec(mouse, titleBar))
        {
            draggingId = active.id;
            active.dragging = true;

            dragOffset = {
                mouse.x - active.bounds.x,
                mouse.y - active.bounds.y
            };
        }

        return;
    }
}

void DrawWindowManager()
{
    // Vẽ cửa sổ dưới trước, cửa sổ trên sau.
    for (const NanoWindow& window : windows)
        DrawNanoWindow(window);

    float x = 12.0f;
    const float y = (float)GetScreenHeight() - 38.0f;

    for (const NanoWindow& window : windows)
    {
        if (!window.minimized)
            continue;

        Rectangle chip = { x, y, 120.0f, 30.0f };

        DrawRectangleRounded(
            chip, 0.25f, 8,
            Color{ 42, 46, 56, 240 }
        );

        DrawText(
            window.title,
            (int)(x + 10.0f),
            (int)(y + 8.0f),
            13, RAYWHITE
        );

        x += 126.0f;
    }
}

void CloseWindowManager()
{
    windows.clear();
    draggingId = -1;
}