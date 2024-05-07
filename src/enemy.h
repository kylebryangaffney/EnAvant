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
    virtual Vector2 getScreenPos() override;

private:
    Character *target{};
    float damagePerSec{10.f};
    float closeRadius{25.f};
    float attackRadius{300.f};
};

#endif