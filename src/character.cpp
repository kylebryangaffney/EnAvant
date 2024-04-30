#include "character.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth),
                                                    windowHeight(winHeight)
{
    width = static_cast<float>(texture.width) / maxFrames;
    height = static_cast<float>(texture.height);
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - charScale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - charScale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{

    // check key input
    if (IsKeyDown(KEY_LEFT))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_RIGHT))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_UP))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_DOWN))
        velocity.y += 1;
    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 wepOffset{};
    float rotation{35.f};
    if (rightLeft > 0.f)
    {
        origin = {0.f, static_cast<float>(weapon.height) * charScale};
        wepOffset = {40.f, 55.f};
        wepCollisionRec = {
            getScreenPos().x + wepOffset.x,
            getScreenPos().y + wepOffset.y - weapon.height * charScale,
            static_cast<float>(weapon.width) * charScale,
            static_cast<float>(weapon.height) * charScale};
    }
    else
    {
        origin = {static_cast<float>(weapon.width) * charScale, static_cast<float>(weapon.height) * charScale};
        wepOffset = {25.f, 55.f};
        wepCollisionRec = {
            getScreenPos().x + wepOffset.x - weapon.width * charScale,
            getScreenPos().y + wepOffset.y - weapon.height * charScale,
            static_cast<float>(weapon.width) * charScale,
            static_cast<float>(weapon.height) * charScale};
        rotation *= -1;
    }

    // draw sword for nkight
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + wepOffset.x, getScreenPos().y + wepOffset.y, static_cast<float>(weapon.width) * charScale, static_cast<float>(weapon.height) * charScale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        wepCollisionRec.x, wepCollisionRec.y, wepCollisionRec.width, wepCollisionRec.height, RED);
}
