#include "_player.h"

_player::_player()
{
    // ctor
    xMin = 0.0f;
    xMax = 1.0f;
    yMin = 0.0f;
    yMax = 1.0f;

    pos.y = -1.36f;
}

_player::~_player()
{
    // dtor
}

void _player::plyInit(int x, int y, char *fileName)
{
    initQuad(fileName);
    xFrames = x;
    yFrames = y;

    xMin = 1.0f / (float)xFrames;
    xMax = 2.0f / (float)xFrames;
    yMin = 0.02f / (float)yFrames;
    yMax = 1.0f / (float)yFrames;
    facingLeft = true;
    facingRight = false;
}

void _player::playerActions(float deltaT)
{
    timer += deltaT;
    switch (actionTrigger)
    {

    case STANDLEFT:
        xMin = 1.0f / (float)xFrames;
        xMax = 2.0f / (float)xFrames;
        break;
    case STANDRIGHT:
        xMin = 2.0f / (float)xFrames;
        xMax = 1.0f / (float)xFrames;
        break;
    case LEFTWALK:
        if (facingRight)
        {
            xMin = 1.0f / (float)xFrames;
            xMax = 2.0f / (float)xFrames;
            facingRight = false;
            facingLeft = true;
        }
        if (timer > 0.08)
        {
            xMin += 1.0f / (float)xFrames;
            xMax += 1.0f / (float)xFrames;
            if (pos.x > -2.6f)
            {
                pos.x -= 0.05f;
            }
            timer = 0;
        }
        break;
    case RIGHTWALK:
        if (facingLeft)
        {
            xMin = 2.0f / (float)xFrames;
            xMax = 1.0f / (float)xFrames;
            facingLeft = false;
            facingRight = true;
        }
        if (timer > 0.08)
        {
            xMin += 1.0f / (float)xFrames;
            xMax += 1.0f / (float)xFrames;
            if (pos.x < 2.6f)
            {
                pos.x += 0.05f;
            }
            timer = 0;
        }
        break;
    case WALKUP:
        if (timer > 0.08)
        {
            xMin += 1.0 / (float)xFrames;
            ;
            xMax += 1.0 / (float)xFrames;
            yMax = 1.0 / 4.0;
            yMin = 0.0 / 4.0;
            timer = 0;
        }
        break;
    case WALKBACK:
        if (timer > 0.08)
        {
            xMin += 1.0 / (float)xFrames;
            ;
            xMax += 1.0 / (float)xFrames;
            yMax = 1.0;
            yMin = 3.0 / 4.0;
            timer = 0;
        }

        break;
    default:
        break;
    }
}
