#include "character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    this->width = static_cast<float>(texture.width) / maxFrames;
    this->height = static_cast<float>(texture.height);
    this->screenPos = {
        static_cast<float>(winWidth) / 2.0f - this->charScale * (0.5f * this->width),
        static_cast<float>(winHeight) / 2.0f - this->charScale * (0.5f * this->height)};
}

void Character::undoMovement()
{
    this->worldPos = this->worldPosLastFrame;
}

void Character::tick(float deltaTime)
{
    this->worldPosLastFrame = this->worldPos;
    // check key input
    Vector2 direction{};
    if (IsKeyDown(KEY_LEFT))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_RIGHT))
        direction.x += 1.0;
    if (IsKeyDown(KEY_UP))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_DOWN))
        direction.y += 1;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction * speed
        this->worldPos = Vector2Add(this->worldPos, Vector2Scale(Vector2Normalize(direction), this->speed));
        // set direction of knight
        this->rightLeft = direction.x < 0.f ? -1.f : 1.f;
        this->texture = this->run;
    }
    else
    {
        this->texture = this->idle;
    }
    // update animation frame for knight
    this->runningTime += deltaTime;
    if (this->runningTime >= this->updateTime)
    {
        this->frame++;
        this->runningTime = 0.f;
        if (this->frame > this->maxFrames)
            this->frame = 0;
    }
    // draw knight
    Rectangle source{this->width * static_cast<float>(this->frame), 0.0f, this->rightLeft * this->width, this->height};
    Rectangle dest{this->screenPos.x, this->screenPos.y, this->charScale * this->width, this->charScale * this->height};
    Vector2 origin{0.0f, 0.0f};
    DrawTexturePro(this->texture, source, dest, origin, 0.0f, WHITE);
}

Rectangle Character::getCollisionRec()
{
    return Rectangle{this->screenPos.x, this->screenPos.y, this->width * this->charScale, this->height * this->charScale};
}
