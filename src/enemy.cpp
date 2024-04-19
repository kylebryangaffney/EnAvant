#include "enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture) : texture(idleTexture),
                                                                         idle(idleTexture),
                                                                         run(runTexture),
                                                                         worldPos(pos)
{
    width = static_cast<float>(texture.width) / maxFrames;
    height = static_cast<float>(texture.height);
}

void Enemy::tick(float deltaTime)
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

void Enemy::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRec()
{
    return Rectangle{screenPos.x, screenPos.y, width * charScale, height * charScale};
}