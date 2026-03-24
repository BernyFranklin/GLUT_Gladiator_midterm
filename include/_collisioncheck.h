#ifndef _COLLISIONCHECK_H
#define _COLLISIONCHECK_H

#include<_common.h>

class _collisionCheck
{
    public:
        _collisionCheck();
        virtual ~_collisionCheck();

        bool isLinearCol(vec2,vec2); // check only xy
        bool isRadialCol(vec3,vec3,float,float,float);
         //positions, radius, threshold
        bool isPlanoCol(vec3,vec3);
        const float COLLISION_THRESHOLD = 0.3f;

    protected:

    private:
};

#endif // _COLLISIONCHECK_H
