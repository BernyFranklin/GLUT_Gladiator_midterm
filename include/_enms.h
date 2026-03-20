#ifndef _ENMS_H
#define _ENMS_H
#include "_common.h"
#include "_quad.h"


class _enms:public _quad
{
    public:
        _enms();
        virtual ~_enms();

        float timer =0;
        int xFrames,yFrames;
        int actionTrigger;
        enum{STAND,LEFTWALK,RIGHTWALK,RUN,JUMP,ATTACK,WALKUP,WALKBACK};

        void enmsInit(int,int,char*);
        void enmsActions(float);
        void placeEmns(vec3,float);
        void drawEnms();

        bool isEnmsLive = true;


    protected:

    private:
};

#endif // _ENMS_H
