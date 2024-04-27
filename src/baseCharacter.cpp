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
    return Rectangle{screenPos.x, screenPos.y, width * charScale, height * charScale};
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
    // draw enemy
    Rectangle source{width * static_cast<float>(frame), 0.0f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, charScale * width, charScale * height};
    Vector2 origin{0.0f, 0.0f};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}
