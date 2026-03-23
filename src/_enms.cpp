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
    actionTrigger = 2;
}

_enms::~_enms()
{
    // dtor
}

void _enms::enmsInit(int x, int y, char *fileName)
{
    initQuad(fileName);
    xFrames = x;
    yFrames = y;

    xMin = 2.0 / (float)xFrames;
    xMax = 3.0 / (float)xFrames;
    yMin = 0;
    yMax = 1.0 / (float)yFrames;

    actionTrigger = FALL;
}

void _enms::enmsActions(float deltaT)
{
    timer += deltaT;
    switch (actionTrigger)
    {
    case FALL:
        xMin = 2.0 / (float)xFrames;
        xMax = 3.0 / (float)xFrames;
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
                pos.y = 4.0f;
                pos.x = (float)(rand() % 7) - 3.0f;
                actionTrigger = FALL;
            }
        }
        break;
    case LEFTWALK:
        if (timer > 0.08)
        {
            
        }
        break;
    case ROLLEFT:

        break;
    case ROLRIGHT:

        if (timer > 0.08)
        {
            theta = 30 * PI / 180.0;

            rot.z += (float)rand() / (float)(RAND_MAX) * 100;

            // x = vtcos
            // y = vtsin - (1/2)gravity*t^2

            pos.x += vel * t * cos(theta) / 1200.0;
            pos.y += (vel * t * sin(theta) - 0.5 * GRAVITY * t * t) / 100.0;

            pos.y > -1.5 ? t += 0.3 : (t = 0.1, pos.y = -1.4);
            pos.x > 4.5 ? (actionTrigger = LEFTWALK, rot.z = 0) : NULL;
            timer = 0;
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
