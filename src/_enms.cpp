#include "_enms.h"

_enms::_enms()
{
    // ctor
    pos.x = 0;
    pos.y = -0.4;
    pos.z = -7;

    rot.x = 0;
    rot.y = 0;
    rot.z = 0;

    scale.x = 0.5;
    scale.y = 0.5;
    scale.z = 1.0;

    vel = 45;
    t = 0.1;
    actionTrigger = FALL;
}

_enms::~_enms()
{
    // dtor
}

void _enms::enmsInit(int x, int y, float minX, float maxX, float minY, float maxY, char *fileName)
{
    initQuad(fileName);
    xFrames = x;
    yFrames = y;

    initialFrameMinX = minX / (float)xFrames;
    initialFrameMaxX = maxX / (float)xFrames;
    initialFrameMinY = minY / (float)yFrames;
    initialFrameMaxY = maxY / (float)yFrames;

    xMin = initialFrameMinX;
    xMax = initialFrameMaxX;
    yMin = initialFrameMinY;
    yMax = initialFrameMaxY;

    actionTrigger = FALL;
}

void _enms::enmsActions(float deltaT)
{
    timer += deltaT;
    switch (actionTrigger)
    {
    case FALL:
        xMin = initialFrameMinX;
        xMax = initialFrameMaxX;
        if (timer > 0.08)
        {
            pos.y -= 0.2f;
            timer = 0;
            if (pos.y < -4.0f)
            {
                pos.y = 4.0f;
                pos.x = (float)(rand() % 7) - 3.0f;
            }
        }
        break;
    case HIT:
        if (timer > 0.08)
        {

            xMin += 1.0f / (float)xFrames;
            xMax += 1.0f / (float)xFrames;
            timer = 0;
            if (xMax > 1.0f)
            {
                pos.x = (float)(rand() % 7) - 3.0f;
                pos.y = (float)(rand() % 7) + 4.0f;
                actionTrigger = FALL;
                isDead = false;
            }
        }
        break;
    default:
        break;
    }
}

void _enms::placeEmns(vec3 Epos, float timer)
{
    pos.x = Epos.x;
    pos.y = Epos.y;
    pos.z = Epos.z;
}

void _enms::drawEnms()
{
    updateQuad();
    drawQuad();
}
