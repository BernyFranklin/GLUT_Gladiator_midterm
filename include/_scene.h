#ifndef _SCENE_H
#define _SCENE_H

#include <_common.h>
#include <_lightsettings.h>
#include <_model.h>
#include <_inputs.h>
#include <_modelvbo.h>
#include <_parallax.h>
#include <_quad.h>
#include <_player.h>
#include <_enms.h>
#include <_collisioncheck.h>

class _scene
{
public:
    _scene();
    virtual ~_scene();

    GLint initGL();            // initialize the openGL contents
    void reSize(GLint, GLint); // to handle resize window
    void drawScene();          // render the final scene
    void drawScene2();
    void drawScene3();
    int winMsg(HWND hWnd,     // Handle For This Window
               UINT uMsg,     // Message For This Window
               WPARAM wParam, // Additional Message Information
               LPARAM lParam);

    void mouseMapping(int, int);
    static float deltaTime;

    _parallax *level1 = new _parallax();
    _parallax *level2 = new _parallax();
    _parallax *level3 = new _parallax();
    _player *lvl1Player = new _player();
    _player *lvl2Player = new _player();
    _player *lvl3Player = new _player();
    _enms *lvl1Enms[10] =
        {
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms()};
    _enms *lvl2Enms[10] =
        {
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms(),
            new _enms()};
    _inputs *myKeys = new _inputs();
    _collisionCheck *colCheck = new _collisionCheck();
    vec3 mouse; // to keep track of the mouse location
    vec2 dim;   // window size
    int hitCounter = 0;
    const int MAX_HITS = 5;
    bool playLevel1 = false;
    bool playLevel2 = false;
    bool playLevel3 = true;

protected:
private:
};

#endif // _SCENE_H
