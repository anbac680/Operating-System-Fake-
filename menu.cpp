
#include "menu.h"
#include "raylib.h"
#include <cmath>

extern Texture2D homeIcon;
extern Texture2D settingsIcon;

static float menuY = 0.0f;
static float targetY = 0.0f;
static float startY = 0.0f;

static double animationStart = 0.0;
static bool animating = false;

static const float BAR_WIDTH = 460.0f;
static const float BAR_HEIGHT = 64.0f;
static const float BOTTOM_MARGIN = 16.0f;
static const float ICON_SIZE = 24.0f;

static bool homeOpen = false;
static bool settingsOpen = false;

static Rectangle homeRect;
static Rectangle settingsRect;

void InitMenu()
{
    float screenH = (float)GetScreenHeight();

    targetY = screenH - BAR_HEIGHT - BOTTOM_MARGIN;
    startY = screenH + 10.0f;
    menuY = startY;

    animationStart = GetTime();
    animating = true;
}

void UpdateMenu()
{
    if (animating)
    {
        float t = (float)((GetTime() - animationStart) / 0.75);

        if (t >= 1.0f)
        {
            t = 1.0f;
            animating = false;
        }

        if (t < 0.0f)
            t = 0.0f;

        const float c1 = 1.70158f;
        const float c3 = c1 + 1.0f;

        float eased = 1.0f
            + c3 * powf(t - 1.0f, 3.0f)
            + c1 * powf(t - 1.0f, 2.0f);

        menuY = startY + (targetY - startY) * eased;
    }

    float screenW = (float)GetScreenWidth();
    float barX = (screenW - BAR_WIDTH) / 2.0f;
    float iconY = menuY + (BAR_HEIGHT - ICON_SIZE) / 2.0f;

    // Click areas move together with the menu.
    homeRect = {
        barX + 20.0f, iconY,
        ICON_SIZE, ICON_SIZE
    };

    settingsRect = {
        barX + 80.0f, iconY,
        ICON_SIZE, ICON_SIZE
    };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, homeRect))
        {
            homeOpen = !homeOpen;
            settingsOpen = false;
        }
        else if (CheckCollisionPointRec(mouse, settingsRect))
        {
            settingsOpen = !settingsOpen;
            homeOpen = false;
        }
    }
}

void DrawMenu()
{
    float screenW = (float)GetScreenWidth();
    float barX = (screenW - BAR_WIDTH) / 2.0f;

    Rectangle bar = {
        barX, menuY,
        BAR_WIDTH, BAR_HEIGHT
    };

    DrawRectangleRounded(
        {barX, menuY + 5.0f, BAR_WIDTH, BAR_HEIGHT},
        0.8f, 16, Fade(BLACK, 0.25f)
    );

    DrawRectangleRounded(
        bar, 0.8f, 16, Color{35, 35, 48, 235}
    );

    DrawRectangleRoundedLinesEx(
        bar, 0.8f, 16, 1.0f, Fade(WHITE, 0.18f)
    );

    if (IsTextureValid(homeIcon))
    {
        DrawTexturePro(
            homeIcon,
            {0, 0, (float)homeIcon.width, (float)homeIcon.height},
            homeRect, {0, 0}, 0, WHITE
        );
    }

    if (IsTextureValid(settingsIcon))
    {
        DrawTexturePro(
            settingsIcon,
            {0, 0, (float)settingsIcon.width, (float)settingsIcon.height},
            settingsRect, {0, 0}, 0, WHITE
        );
    }

    // Home window inside NanoOS
    if (homeOpen)
    {
        Rectangle win = {340, 250, 600, 350};

        DrawRectangleRounded(win, 0.04f, 8, Color{240, 240, 245, 255});
        DrawRectangle(340, 250, 600, 40, Color{45, 45, 60, 255});
        DrawText("Home", 355, 261, 18, WHITE);

        DrawText("Welcome to NanoOS", 370, 320, 28, DARKGRAY);
        DrawText("This window is inside the app.", 370, 365, 18, GRAY);

        // Close button
        Rectangle closeRect = {900, 250, 40, 40};
        DrawRectangleRec(closeRect, MAROON);
        DrawText("X", 913, 260, 20, WHITE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), closeRect))
        {
            homeOpen = false;
        }
    }

    // Settings window inside NanoOS
    if (settingsOpen)
    {
        Rectangle win = {390, 280, 500, 280};

        DrawRectangleRounded(win, 0.04f, 8, Color{240, 240, 245, 255});
        DrawRectangle(390, 280, 500, 40, Color{45, 45, 60, 255});
        DrawText("Settings", 405, 291, 18, WHITE);

        DrawText("NanoOS Settings", 420, 345, 24, DARKGRAY);
        DrawText("Display   |   Appearance", 420, 390, 18, GRAY);

        Rectangle closeRect = {850, 280, 40, 40};
        DrawRectangleRec(closeRect, MAROON);
        DrawText("X", 863, 290, 20, WHITE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), closeRect))
        {
            settingsOpen = false;
        }
    }
}

void CloseMenu()
{
}