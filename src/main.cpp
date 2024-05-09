#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

int main()
{
    const int windowWidth{900};
    const int windowHeight{900};
    InitWindow(windowWidth, windowHeight, "EnAvant");

    Texture2D map = LoadTexture("nature_tileset\\WorldMap.png");
    Vector2 mapPos{0.0f, 0.0f};

    Character knight{windowWidth, windowHeight};
    Enemy goblin{Vector2{450.f, 555.f}, LoadTexture("characters\\goblin_idle_spritesheet.png"), LoadTexture("characters\\goblin_run_spritesheet.png")};

    Enemy slime{Vector2{555.f, 333.f}, LoadTexture("characters\\slime_idle_spritesheet.png"), LoadTexture("characters\\slime_run_spritesheet.png")};
    InitAudioDevice();
    Music classicalMusic = LoadMusicStream("soundFX\\gregorquendel_schumann.wav");
    Music hatefulMusic = LoadMusicStream("soundFX\\metal_tune.mp3");

    // Set up initial background music
    Music bgMusic = classicalMusic;
    PlayMusicStream(bgMusic);

    float timePlayed = 0.0f;
    //  jump variable
    Prop propArray[2]{
        Prop{Vector2{666.f, 333.f}, LoadTexture("nature_tileset\\Rock.png")},
        Prop{Vector2{222.f, 444.f}, LoadTexture("nature_tileset\\Log.png")}};
    Prop *swordProp = nullptr;

    Enemy *enemyArray[]{&goblin, &slime};
    for (int i = 0; i < 2; i++)
    {
        enemyArray[i]->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(bgMusic);
        timePlayed = GetMusicTimePlayed(bgMusic) / GetMusicTimeLength(bgMusic);
        if (timePlayed > 1.0f)
            timePlayed = 1.0f;
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw map
        DrawTextureEx(map, mapPos, 0.f, knight.getCharScale(), WHITE);

        if (!knight.checkSword() && swordProp == nullptr)
        {
            swordProp = new Prop{Vector2{900.f, 900.f}, LoadTexture("characters\\weapon_sword.png")};
        }

        for (int i = 0; i < 2; i++)
        {
            propArray[i].Render(knight.getWorldPos());
        }
        if (swordProp != nullptr && swordProp->getIsAlive())
        {
            swordProp->Render(knight.getWorldPos());
        }
        if (!knight.getIsAlive()) // knight died
        {
            DrawText("Game Over", 200.f, 200.f, 35, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightHealth = "HP: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 2);
            DrawText(knightHealth.c_str(), 40.f, 40.f, 35, RED);
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
        if (swordProp != nullptr && swordProp->getIsAlive() &&
            CheckCollisionRecs(knight.getCollisionRec(), swordProp->getCollisionRec(knight.getWorldPos())))
        {
            knight.takeSword();
            swordProp->setIsAlive(false);
            delete swordProp;
            swordProp = nullptr;
            StopMusicStream(bgMusic);
            bgMusic = hatefulMusic;
            PlayMusicStream(bgMusic);
        }
        for (int i = 0; i < 2; i++)
        {
            enemyArray[i]->tick(GetFrameTime());
            if (IsKeyPressed(KEY_SPACE))
            {
                if (CheckCollisionRecs(knight.getWeaponCollisionRec(), enemyArray[i]->getCollisionRec()))
                {
                    enemyArray[i]->setIsAlive(false);
                }
            }
        }
        EndDrawing();
    }
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    CloseWindow();
}