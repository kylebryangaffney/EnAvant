#include "baseCharacter.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{getScreenPos().x, getScreenPos().y, width * charScale, height * charScale};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame for enemy
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + direction * speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        // set direction of knight
        rightLeft = velocity.x < 0.f ? -1.f : 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    // draw enemy
    Rectangle source{width * static_cast<float>(frame), 0.0f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, charScale * width, charScale * height};
    Vector2 origin{0.0f, 0.0f};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}
