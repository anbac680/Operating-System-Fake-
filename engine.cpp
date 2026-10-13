#include "engine.h"
#include "raylib.h"
#include "menu.h"
#include "window_manager.h"

namespace
{
    Texture2D wallpaper{};
    Texture2D homeIcon{};
    Texture2D settingsIcon{};
}

void InitEngine()
{
    InitWindow(1280, 800, "NanoOS");
    SetTargetFPS(60);

    wallpaper = LoadTexture("wallpaper.png");
    homeIcon = LoadTexture("home.png");
    settingsIcon = LoadTexture("setting.png");
    InitWindowManager();
    InitMenu(homeIcon, settingsIcon);
    OpenNanoWindow(WindowType::Home);
}

void UpdateEngine()
{
    const bool menuConsumedClick = UpdateMenu();

    // Vẫn cập nhật animation mỗi frame, nhưng không xử lý
    // lại cú click mà menu vừa nhận.
    UpdateWindowManager(!menuConsumedClick);
}

void DrawEngine()
{
    BeginDrawing();

    ClearBackground(Color{ 25, 28, 35, 255 });

    if (wallpaper.id != 0)
    {
        DrawTexturePro(
            wallpaper,
            { 0.0f, 0.0f,
              (float)wallpaper.width, (float)wallpaper.height },
            { 0.0f, 0.0f,
              (float)GetScreenWidth(), (float)GetScreenHeight() },
            { 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    }


    DrawWindowManager();
    DrawMenu();

    EndDrawing();
}

void CloseEngine()
{
    CloseMenu();
    CloseWindowManager();

    if (wallpaper.id != 0)
        UnloadTexture(wallpaper);

    if (homeIcon.id != 0)
        UnloadTexture(homeIcon);

    if (settingsIcon.id != 0)
        UnloadTexture(settingsIcon);

    CloseWindow();
}
