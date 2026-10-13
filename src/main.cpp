
#include "raylib.h"
#include "engine.h"

int main()
{
    InitEngine();

    while (!WindowShouldClose())
    {
        UpdateEngine();
        DrawEngine();
    }

    CloseEngine();
    return 0;
}
