#include "_collisioncheck.h"

_collisionCheck::_collisionCheck()
{
    // ctor
}

_collisionCheck::~_collisionCheck()
{
    // dtor
}

bool _collisionCheck::isLinearCol(vec2 player, vec2 enemy, float collisionThreshX, float collisionThreshY)
{
    bool crossX, crossY;
    (enemy.y < (player.y + collisionThreshY) && enemy.y > (player.y - collisionThreshY))
        ? crossY = true
        : crossY = false;
    (enemy.x > (player.x - collisionThreshX) && enemy.x < (player.x + collisionThreshX))
        ? crossX = true
        : crossX = false;

    return (crossX && crossY);
}

bool _collisionCheck::isRadialCol(vec3 p1, vec3 p2, float r1, float r2, float thrld)
{
    return (sqrt(pow(p1.x - p2.x, 2) +
                 pow(p1.y - p2.y, 2) +
                 pow(p1.z - p2.z, 2)) -
                (r1 + r2) <
            thrld);
}

bool _collisionCheck::isPlanoCol(vec3, vec3)
{
}
