#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "raymath.h"
#include "baseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual Vector2 getScreenPos() override;
    virtual void tick(float deltaTime) override;
    Rectangle getWeaponCollisionRec() { return wepCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
    bool checkSword() { return hasSword; }
    void takeSword();

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters\\weapon_sword.png")};
    Rectangle wepCollisionRec{};
    float health{99.f};
    bool hasSword{false};
};

#endif