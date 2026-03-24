#include "_player.h"

_player::_player()
{
    pos.x = START_OF_LEVEL;
}

_player::~_player()
{
    // dtor
}

void _player::lvl1PlayerInit(int x, int y, char *fileName)
{
    initQuad(fileName);
    xFrames = x;
    yFrames = y;

    xMin = 2.0f / (float)xFrames;
    xMax = 1.0f / (float)xFrames;
    yMin = 0.02f / (float)yFrames;
    yMax = 1.0f / (float)yFrames;
    facingLeft = false;
    facingRight = true;
    pos.y = yPosLvl1;
}

void _player::playerActions(float deltaT)
{
    timer += deltaT;
    switch (actionTrigger)
    {

    case STANDLEFT:
        xMin = 1.0f / (float)xFrames;
        xMax = 2.0f / (float)xFrames;
        yMin = 0.02f / (float)yFrames;
        yMax = 1.0f / (float)yFrames;
        break;
    case STANDRIGHT:
        xMin = 2.0f / (float)xFrames;
        xMax = 1.0f / (float)xFrames;
        yMin = 0.02f / (float)yFrames;
        yMax = 1.0f / (float)yFrames;
        break;
    case LEFTWALK:
        if (facingRight)
        {
            xMin = 1.0f / (float)xFrames;
            xMax = 2.0f / (float)xFrames;
            facingRight = false;
            facingLeft = true;
        }
        if (timer > 0.07)
        {
            xMin += 1.0f / (float)xFrames;
            xMax += 1.0f / (float)xFrames;
            if (pos.x > -4.6f)
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
        if (timer > 0.07)
        {
            xMin += 1.0f / (float)xFrames;
            xMax += 1.0f / (float)xFrames;
            pos.x += 0.05f;
            timer = 0;
        }
        break;
    case HIT:
        if (facingRight)
        {
            xMin = 0.0f;
            xMax = 1.0f / (float)xFrames;
            yMin = 1.02f / (float)yFrames;
            yMax = 2.0f / (float)yFrames;
        }
        else
        {
            xMin = 1.0f / (float)xFrames;
            xMax = 0.0f / (float)xFrames;
            yMin = 1.02f / (float)yFrames;
            yMax = 2.0f / (float)yFrames;
        }
        for (int i = 0; i < 4; i++)
        {
            if (timer > 0.07f)
            {
                xMin += 1.0f / (float)xFrames;
                xMax += 1.0f / (float)xFrames;
                timer = 0;
            }
        }
        (facingLeft) ? actionTrigger = STANDLEFT : actionTrigger = STANDRIGHT;
        break;
    default:
        break;
    }
}
