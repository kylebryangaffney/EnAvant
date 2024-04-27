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

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
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
}
