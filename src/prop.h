#ifndef PROP_H
#define PROP_H
#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 knightPos);
    bool getIsAlive() { return isAlive; }
    void setIsAlive(bool alive) { isAlive = alive; }

private:
    Vector2 worldPos{};
    Texture2D texture{};
    float propScale{4.f};
    bool isAlive{true};
};

#endif