#include "_player.h"

_player::_player()
{
    pos.x = START_OF_LEVEL;
}

_player::~_player()
{
    // dtor
}

void _player::lvl1PlayerInit(char *fileName)
{
    initQuad(fileName);

    standLeftMin = 1.0f / (float)xFrames;
    standLeftMax = 2.0f / (float)xFrames;
    standRightMin = 2.0f / (float)xFrames;
    standRightMax = 1.0f / (float)xFrames;

    xMin = standRightMin;
    xMax = standRightMax;
    yMin = 0.02f / (float)yFrames;
    yMax = 1.0f / (float)yFrames;
    facingLeft = false;
    facingRight = true;
    pos.y = yPosLvl1;
}

void _player::lvl2PlayerInit(char *fileName)
{
    initQuad(fileName);

    standLeftMin = 3.0f / (float)xFrames;
    standLeftMax = 2.0f / (float)xFrames;
    standRightMin = 2.0f / (float)xFrames;
    standRightMax = 3.0f / (float)xFrames;

    xMin = standRightMin;
    xMax = standRightMax;
    yMin = 0.0f / (float)yFrames;
    yMax = 1.0f / (float)yFrames;
    facingLeft = false;
    facingRight = true;
    pos.y = yPosLvl2;
}

void _player::lvl3PlayerInit(char *fileName)
{
    initQuad(fileName);

    standLeftMin = 3.0f / (float)xFrames;
    standLeftMax = 2.0f / (float)xFrames;
    standRightMin = 2.0f / (float)xFrames;
    standRightMax = 3.0f / (float)xFrames;

    xMin = standRightMin;
    xMax = standRightMax;
    yMin = 0.05f / (float)yFrames;
    yMax = 1.0f / (float)yFrames;
    facingLeft = false;
    facingRight = true;
    scale.x = 0.75f;
    scale.y = 0.75f;
    pos.y = -1.8f;
}

void _player::playerActions(float deltaT)
{
    timer += deltaT;
    switch (actionTrigger)
    {

    case STANDLEFT:
        xMin = standLeftMin;
        xMax = standLeftMax;
        yMin = 0.02f / (float)yFrames;
        yMax = 1.0f / (float)yFrames;
        break;
    case STANDRIGHT:
        xMin = standRightMin;
        xMax = standRightMax;
        yMin = 0.02f / (float)yFrames;
        yMax = 1.0f / (float)yFrames;
        break;
    case LEFTWALK:
        if (facingRight)
        {
            xMin = standLeftMin;
            xMax = standLeftMax;
            facingRight = false;
            facingLeft = true;
        }
        if (timer > 0.07f)
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
            xMin = standRightMin;
            xMax = standRightMax;
            facingLeft = false;
            facingRight = true;
        }
        if (timer > 0.07f)
        {
            xMin += 1.0f / (float)xFrames;
            xMax += 1.0f / (float)xFrames;
            pos.x += 0.05f;
            timer = 0;
        }
        break;
    case HIT:
        yMin = 1.02f / (float)yFrames;
        yMax = 2.0f / (float)yFrames;
        if (timer > 0.07f)
        {
            xMin += 1.0f / (float)xFrames;
            xMax += 1.0f / (float)xFrames;
            timer = 0;
            if (xMax > 0.4f)
            {
                if (facingLeft)
                    actionTrigger = STANDLEFT;
                else if (facingRight)
                    actionTrigger = STANDRIGHT;
            }
        }
        break;
    default:
        break;
    }
}
