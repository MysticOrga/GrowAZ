#include "Tree.hpp"

Tree::Tree(Vector2 center, float foliageRadius, float trunkWidth, float trunkHeight)
    : position(center),
    foliageRadius(foliageRadius),
    trunkWidth(trunkWidth),
    trunkHeight(trunkHeight),
    foliageScale(1.0f)
{
}

void Tree::draw()
{
    Rectangle trunkRect = getTrunkRect();
    DrawRectangleRec(trunkRect, {153, 76, 0, 255});
    DrawCircleV(position, foliageRadius * foliageScale, {0, 204, 0, 255});
}

void Tree::animate(float dt)
{
    float scaleRelaxSpeed = 6.0f;
    foliageScale += (1.0f - foliageScale) * scaleRelaxSpeed * dt;
}

bool Tree::contains(const Vector2 &point)
{
    return isOnFoliage(point) || CheckCollisionPointRec(point, getTrunkRect());
}

void Tree::popFoliage()
{
    foliageScale = 1.1f;
}

Rectangle Tree::getTrunkRect()
{
    return Rectangle{
        position.x - trunkWidth / 2.0f,
        position.y,
        trunkWidth,
        trunkHeight};
}

bool Tree::isOnFoliage(const Vector2 &point)
{
    float dx = point.x - position.x;
    float dy = point.y - position.y;
    float distanceSquared = dx * dx + dy * dy;
    float radius = foliageRadius * foliageScale;
    return distanceSquared <= radius * radius;
}
