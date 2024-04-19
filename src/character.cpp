#include "character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = static_cast<float>(texture.width) / maxFrames;
    height = static_cast<float>(texture.height);
    screenPos = {
        static_cast<float>(winWidth) / 2.0f - charScale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - charScale * (0.5f * height)};
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    // check key input
    Vector2 direction{};
    if (IsKeyDown(KEY_LEFT))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_RIGHT))
        direction.x += 1.0;
    if (IsKeyDown(KEY_UP))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_DOWN))
        direction.y += 1;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction * speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // set direction of knight
        rightLeft = direction.x < 0.f ? -1.f : 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    // update animation frame for knight
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }
    // draw knight
    Rectangle source{width * static_cast<float>(frame), 0.0f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, charScale * width, charScale * height};
    Vector2 origin{0.0f, 0.0f};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

Rectangle Character::getCollisionRec()
{
    return Rectangle{screenPos.x, screenPos.y, width * charScale, height * charScale};
}