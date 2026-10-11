
#include "engine.h"
#include "menu.h"

Texture2D wallpaper;
Texture2D homeIcon;
Texture2D settingsIcon;

void InitEngine()
{
    InitWindow(1280, 800, "NanoOS");
    SetTargetFPS(60);

    // Load textures after InitWindow()
    wallpaper = LoadTexture("assets/wallpaper.png");
    homeIcon = LoadTexture("assets/home.png");
    settingsIcon = LoadTexture("assets/setting.png");

    InitMenu();
}

void UpdateEngine()
{
    UpdateMenu();
}

void DrawEngine()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Desktop wallpaper
    if (IsTextureValid(wallpaper))
    {
        DrawTexture(wallpaper, 0, 0, WHITE);
    }

    // Menu and icons are drawn together
    DrawMenu();

    EndDrawing();
}

void CloseEngine()
{
    CloseMenu();

    if (IsTextureValid(wallpaper))
        UnloadTexture(wallpaper);

    if (IsTextureValid(homeIcon))
        UnloadTexture(homeIcon);

    if (IsTextureValid(settingsIcon))
        UnloadTexture(settingsIcon);

    CloseWindow();
}