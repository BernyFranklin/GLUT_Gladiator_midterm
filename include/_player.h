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
    const int xFrames1 = 10;
    const int yFrames1 = 2;
    float timer = 0.0f;
    int xFrames, yFrames;
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

    void lvl1PlayerInit(int, int, char *);
    void playerActions(float);

protected:
private:
};

#endif // _PLAYER_H
