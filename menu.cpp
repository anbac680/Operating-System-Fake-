
#include "menu.h"
#include "window_manager.h"
#include "animation.h"

namespace
{
    Texture2D homeIcon{};
    Texture2D settingsIcon{};

    float menuY = 0.0f;
    float menuAnimation = 0.0f;

    constexpr float MENU_WIDTH = 460.0f;
    constexpr float MENU_HEIGHT = 64.0f;

    Rectangle GetMenuBounds()
    {
        return {
            ((float)GetScreenWidth() - MENU_WIDTH) / 2.0f,
            menuY,
            MENU_WIDTH,
            MENU_HEIGHT
        };
    }

    Rectangle GetHomeButton()
    {
        const Rectangle bar = GetMenuBounds();

        return {
            bar.x + 18.0f, bar.y + 12.0f, 52.0f, 40.0f
        };
    }

    Rectangle GetSettingsButton()
    {
        const Rectangle bar = GetMenuBounds();

        return {
            bar.x + 78.0f, bar.y + 12.0f, 52.0f, 40.0f
        };
    }
}

bool InitMenu(Texture2D home, Texture2D settings)
{
    homeIcon = home;
    settingsIcon = settings;

    menuY = (float)GetScreenHeight() + 20.0f;
    menuAnimation = 0.0f;

    return true;
}

bool UpdateMenu()
{
    const float dt = GetFrameTime();

    menuAnimation += dt * 1.8f;

    if (menuAnimation > 1.0f)
        menuAnimation = 1.0f;

    const float startY = (float)GetScreenHeight() + 20.0f;
    const float targetY =
        (float)GetScreenHeight() - MENU_HEIGHT - 16.0f;

    menuY = startY +
        (targetY - startY) * EaseOutBack(menuAnimation);

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return false;

    const Vector2 mouse = GetMousePosition();

    // Chặn cửa sổ phía sau nhận cùng cú click.
    if (!CheckCollisionPointRec(mouse, GetMenuBounds()))
        return false;

    if (CheckCollisionPointRec(mouse, GetHomeButton()))
    {
        OpenNanoWindow(WindowType::Home);
    }
    else if (CheckCollisionPointRec(mouse, GetSettingsButton()))
    {
        OpenNanoWindow(WindowType::Settings);
    }

    return true;
}

void DrawMenu()
{
    const Rectangle bar = GetMenuBounds();
    const Vector2 mouse = GetMousePosition();

    DrawRectangleRounded(
        { bar.x, bar.y + 5.0f, bar.width, bar.height },
        0.35f, 16,
        Fade(BLACK, 0.18f)
    );

    DrawRectangleRounded(
        bar, 0.35f, 16,
        Color{ 38, 42, 52, 235 }
    );

    DrawRectangleRoundedLinesEx(
        bar, 0.35f, 16, 1.0f,
        Fade(WHITE, 0.18f)
    );

    const Rectangle homeButton = GetHomeButton();
    const Rectangle settingsButton = GetSettingsButton();

    if (CheckCollisionPointRec(mouse, homeButton))
        DrawRectangleRounded(
            homeButton, 0.3f, 8, Fade(WHITE, 0.12f)
        );

    if (CheckCollisionPointRec(mouse, settingsButton))
        DrawRectangleRounded(
            settingsButton, 0.3f, 8, Fade(WHITE, 0.12f)
        );

    if (homeIcon.id != 0 && homeIcon.width > 0)
    {
        DrawTextureEx(
            homeIcon,
            { homeButton.x + 10.0f, homeButton.y + 4.0f },
            0.0f, 32.0f / (float)homeIcon.width,
            WHITE
        );
    }
    else
    {
        DrawText("H", (int)(homeButton.x + 17.0f),
                 (int)(homeButton.y + 10.0f), 20, WHITE);
    }

    if (settingsIcon.id != 0 && settingsIcon.width > 0)
    {
        DrawTextureEx(
            settingsIcon,
            { settingsButton.x + 10.0f, settingsButton.y + 4.0f },
            0.0f, 32.0f / (float)settingsIcon.width,
            WHITE
        );
    }
    else
    {
        DrawText("S", (int)(settingsButton.x + 17.0f),
                 (int)(settingsButton.y + 10.0f), 20, WHITE);
    }

    DrawText(
        "NanoOS",
        (int)(bar.x + 150.0f),
        (int)(bar.y + 23.0f),
        17, RAYWHITE
    );
}

void CloseMenu()
{
    // Engine sở hữu texture nên menu không unload chúng.
    homeIcon = Texture2D{};
    settingsIcon = Texture2D{};
}