#include "_player.h"

_player::_player()
{
    pos.x = START_OF_LEVEL;
}

_player::~_player()
{
    // dtor
}

void _player::playerInit(float xFrameStart, float xFrameEnd, float yFrameStart, float yFrameEnd, float yPos, char *fileName)
{
    initQuad(fileName);

    standRightMin = xFrameStart / (float)xFrames;
    standRightMax = xFrameEnd / (float)xFrames;
    standLeftMin = xFrameEnd / (float)xFrames;
    standLeftMax = xFrameStart / (float)xFrames;

    xMin = standRightMin;
    xMax = standRightMax;
    yMin = yFrameStart / (float)yFrames;
    yMax = yFrameEnd / (float)yFrames;
    facingRight = true;
    facingLeft = false;
    pos.y = yPos;
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
