#include "../include/_enms.h"

_enms::_enms()
{
    //ctor
    pos.x =0;
    pos.y =-0.4;
    pos.z =-7;

    rot.x =0;
    rot.y =0;
    rot.z =0;

    scale.x =0.5;
    scale.y =0.5;
    scale.z =1.0;

    actionTrigger =2;
}

_enms::~_enms()
{
    //dtor
}

void _enms::enmsInit(int x, int y, char *fileName)
{
    initQuad(fileName);
    xFrames =x;
    yFrames =y;

    xMin =0;
    xMax =1.0/(float)xFrames;
    yMax =1.0/(float)yFrames;
    yMin =0;
}

void _enms::enmsActions(float deltaT)
{
    timer += deltaT;
    switch(actionTrigger)
    {
        case STAND:
            xMin =0;
            xMax =1.0/(float)xFrames;
            yMax = 1.0/(float)yFrames;
            yMin = yMax-(1.0/(float)yFrames);
            break;
        case LEFTWALK:

            if(timer>0.08)
             {

            xMax<xMin?(xMin =0,xMax = 1.0/(float)xFrames):NULL;
            xMin +=1.0/(float)xFrames;;
            xMax +=1.0/(float)xFrames;

            pos.x <=4.5?pos.x +=2*deltaT+0.2:actionTrigger=2;

              timer =0;
             }
             break;
        case RIGHTWALK:
            if(timer>0.08)
             {
             xMax>xMin?(xMax =0,xMin = 1.0/(float)xFrames):NULL;
             xMin +=1.0/(float)xFrames;
             xMax +=1.0/(float)xFrames;

             pos.x >= -4.5?pos.x -= 2*deltaT+0.2:actionTrigger=1;

             timer =0;
             }
             break;
        case WALKUP:

             break;
        case WALKBACK:

            break;
        default: break;
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
