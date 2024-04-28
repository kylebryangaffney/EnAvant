#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "raymath.h"
#include "baseCharacter.h"
#include "character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);

    virtual void tick(float deltaTime) override;
    void setTarget(Character *character);

private:
    Character *target{};
};

#endif