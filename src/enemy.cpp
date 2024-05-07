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
    if (!getIsAlive())
        return;
    // get toTarget vector -- direction of the knight in comparison to the enemy
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < closeRadius || Vector2Length(velocity) > attackRadius)
        velocity = {};
    BaseCharacter::tick(deltaTime);
    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

void Enemy::setTarget(Character *character)
{
    target = character;
}

Vector2 Enemy::getScreenPos()
{
    // Calculate the screen position relative to the target character
    return Vector2Subtract(worldPos, target->getWorldPos());
}
