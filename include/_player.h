#ifndef _PLAYER_H
#define _PLAYER_H

#include <_common.h>
#include <_quad.h>

class _player : public _quad
{
public:
    _player();
    virtual ~_player();
    const float END_OF_LEVEL = 4.6f;
    const float START_OF_LEVEL = -4.6f;
    const float yPosLvl1 = -2.56f;
    const float yPosLvl2 = -2.26f;
    const int xFrames = 10;
    const int yFrames = 2;
    float timer = 0.0f;
    float standLeftMin, standLeftMax, standRightMin, standRightMax;
    int actionTrigger;
    enum
    {
        STANDLEFT,
        STANDRIGHT,
        LEFTWALK,
        RIGHTWALK,
        HIT
    };
    bool facingLeft;
    bool facingRight;

    void lvl1PlayerInit(char *);
    void lvl2PlayerInit(char *);
    void lvl3PlayerInit(int, int, char *);
    void playerActions(float);

protected:
private:
};

#endif // _PLAYER_H
