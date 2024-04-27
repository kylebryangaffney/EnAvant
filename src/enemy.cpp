#include "enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture)
{
    worldPos = pos;
    texture = idleTexture;
    idle = idleTexture;
    run = runTexture;
    width = static_cast<float>(texture.width) / maxFrames;
    height = static_cast<float>(texture.height);
}

void Enemy::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
}
