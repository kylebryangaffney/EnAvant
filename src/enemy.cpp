#include "enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture)
{
    worldPos = pos;
    texture = idleTexture;
    idle = idleTexture;
    run = runTexture;
    width = static_cast<float>(texture.width) / maxFrames;
    height = static_cast<float>(texture.height);
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    // get toTarget vector -- direction of the knight in comparison to the enemy
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    // normalize toTarget Vector
    toTarget = Vector2Normalize(toTarget);
    // multiply toTarget Vector by speed
    toTarget = Vector2Scale(toTarget, speed);
    // move enemy -- set worldPos
    worldPos = Vector2Add(worldPos, toTarget);
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(deltaTime);
}

void Enemy::setTarget(Character *character)
{
    target = character;
}
