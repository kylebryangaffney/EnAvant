#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "EnAvant");

    Texture2D map = LoadTexture("nature_tileset\\WorldMap.png");
    Vector2 mapPos{0.0f, 0.0f};

    Character knight{windowWidth, windowHeight};

    Prop propArray[2]{
        Prop{Vector2{666.f, 333.f}, LoadTexture("nature_tileset\\Rock.png")},
        Prop{Vector2{222.f, 444.f}, LoadTexture("nature_tileset\\Log.png")}};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw map
        DrawTextureEx(map, mapPos, 0.f, knight.getCharScale(), WHITE);

        for (int i = 0; i < 2; i++)
        {
            propArray[i].Render(knight.getWorldPos());
        }
        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * knight.getCharScale() ||
            knight.getWorldPos().y + windowHeight > map.height * knight.getCharScale())
        {
            knight.undoMovement();
        }

        // check prop collisions.
        for (int i = 0; i < 2; i++)
        {
            if (CheckCollisionRecs(knight.getCollisionRec(), propArray[i].getCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }

        EndDrawing();
    }
    CloseWindow();
}