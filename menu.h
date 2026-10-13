
#pragma once

#include "raylib.h"

// Trả về true nếu click chuột thuộc khu vực menu.
bool InitMenu(Texture2D home, Texture2D settings);
bool UpdateMenu();
void DrawMenu();
void CloseMenu();