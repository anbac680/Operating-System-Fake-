
#include "window.h"
#include "animation.h"

namespace
{
    constexpr float TITLE_HEIGHT = 42.0f;
    constexpr float CONTROL_WIDTH = 42.0f;

    Rectangle GetAnimatedBounds(const NanoWindow& window)
    {
        Rectangle r = window.bounds;

        const float progress = Clamp01(window.animation);
        const float scale = window.closing
            ? EaseOutCubic(progress)
            : EaseOutBack(progress);

        const float centerX = r.x + r.width / 2.0f;
        const float centerY = r.y + r.height / 2.0f;

        r.width *= scale;
        r.height *= scale;
        r.x = centerX - r.width / 2.0f;
        r.y = centerY - r.height / 2.0f;

        return r;
    }

    void DrawControls(Rectangle r, float alpha)
    {
        const float x = r.x + r.width - CONTROL_WIDTH * 3.0f;

        Rectangle minimize = {
            x, r.y, CONTROL_WIDTH, TITLE_HEIGHT
        };

        Rectangle maximize = {
            x + CONTROL_WIDTH, r.y, CONTROL_WIDTH, TITLE_HEIGHT
        };

        Rectangle close = {
            x + CONTROL_WIDTH * 2.0f,
            r.y, CONTROL_WIDTH, TITLE_HEIGHT
        };

        const Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, minimize))
            DrawRectangleRec(minimize, Fade(WHITE, 0.12f * alpha));

        if (CheckCollisionPointRec(mouse, maximize))
            DrawRectangleRec(maximize, Fade(WHITE, 0.12f * alpha));

        if (CheckCollisionPointRec(mouse, close))
            DrawRectangleRec(close, Fade(RED, 0.80f * alpha));

        
        Color iconColor = Fade(WHITE, alpha);

        // Nút thu nhỏ: dấu gạch ngang
        DrawLine(
            (int)(minimize.x + 15),
            (int)(minimize.y + 21),
            (int)(minimize.x + 27),
            (int)(minimize.y + 21),
            iconColor
        );

        // Nút phóng to: hình vuông
        DrawRectangleLines(
            (int)(maximize.x + 15),
            (int)(maximize.y + 14),
            12, 12,
            iconColor
        );

        // Nút đóng: dấu X
        DrawLine(
            (int)(close.x + 15),
            (int)(close.y + 14),
            (int)(close.x + 27),
            (int)(close.y + 26),
            iconColor
        );

        DrawLine(
            (int)(close.x + 27),
            (int)(close.y + 14),
            (int)(close.x + 15),
            (int)(close.y + 26),
            iconColor
        );
    }
}

void DrawNanoWindow(const NanoWindow& window)
{
    if (window.minimized || window.animation <= 0.0f)
        return;

    const Rectangle r = GetAnimatedBounds(window);
    const float alpha = Clamp01(window.animation);

    // Bóng đổ nhiều lớp
    for (int i = 4; i >= 1; --i)
    {
        Rectangle shadow = {
            r.x - i * 2.0f,
            r.y - i * 2.0f,
            r.width + i * 4.0f,
            r.height + i * 4.0f
        };

        DrawRectangleRounded(
            shadow, 0.06f, 12,
            Fade(BLACK, 0.025f * alpha)
        );
    }

    // Thân cửa sổ
    DrawRectangleRounded(
        r, 0.06f, 12,
        Fade(Color{ 32, 35, 43, 255 }, 0.97f * alpha)
    );

    // Thanh tiêu đề
    Rectangle titleBar = {
        r.x, r.y, r.width, 42.0f
    };

    DrawRectangleRounded(
        titleBar, 0.12f, 12,
        Fade(Color{ 45, 49, 59, 255 }, alpha)
    );

    // Làm phẳng cạnh dưới thanh tiêu đề
    DrawRectangle(
        (int)r.x, (int)(r.y + 34.0f),
        (int)r.width, 8,
        Fade(Color{ 45, 49, 59, 255 }, alpha)
    );

    DrawText(
        window.title,
        (int)(r.x + 16.0f),
        (int)(r.y + 13.0f),
        15, Fade(RAYWHITE, alpha)
    );

    DrawControls(r, alpha);

    const int contentX = (int)(r.x + 24.0f);
    const int contentY = (int)(r.y + 66.0f);

    if (window.type == WindowType::Home)
    {
        DrawText(
            "Welcome to NanoOS",
            contentX, contentY, 23,
            Fade(RAYWHITE, alpha)
        );

        DrawText(
            "Your desktop, your workspace.",
            contentX, contentY + 40, 15,
            Fade(LIGHTGRAY, alpha)
        );

        DrawRectangleRounded(
            { (float)contentX, (float)(contentY + 85), 170, 72 },
            0.12f, 8,
            Fade(Color{ 62, 94, 150, 255 }, alpha)
        );

        DrawText(
            "NanoOS", contentX + 18, contentY + 104,
            20, Fade(RAYWHITE, alpha)
        );
    }
    else if (window.type == WindowType::Settings)
    {
        DrawText("Settings", contentX, contentY, 23,
                 Fade(RAYWHITE, alpha));

        DrawText("Personalization", contentX, contentY + 45, 16,
                 Fade(RAYWHITE, alpha));

        DrawText("Display", contentX, contentY + 82, 16,
                 Fade(RAYWHITE, alpha));

        DrawText("System", contentX, contentY + 119, 16,
                 Fade(RAYWHITE, alpha));
    }

    DrawRectangleRoundedLinesEx(
        r, 0.06f, 12, 1.0f,
        Fade(Color{ 190, 200, 220, 255 }, 0.24f * alpha)
    );
}