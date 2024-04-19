#include "raylib.h"
#include "baseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
    Vector2 getWorldPos()
    {
        return worldPos;
    }

    void tick(float deltaTime);
    float getCharScale()
    {
        return charScale;
    }
    void undoMovement();

    Rectangle getCollisionRec();

private:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 = facing right : -1 = facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float charScale{4.f};
};