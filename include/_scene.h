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
    void loadLevel(_parallax*, _player*, _enms*[], int);
    int winMsg(HWND hWnd,     // Handle For This Window
               UINT uMsg,     // Message For This Window
               WPARAM wParam, // Additional Message Information
               LPARAM lParam);

    void mouseMapping(int, int);
    static float deltaTime;
    static const int ENMS_COUNT = 10;

    _parallax *level1 = new _parallax();
    _parallax *level2 = new _parallax();
    _parallax *level3 = new _parallax();
    _parallax *endScreen = new _parallax();
    _player *lvl1Player = new _player();
    _player *lvl2Player = new _player();
    _player *lvl3Player = new _player();
    _enms *lvl1Enms[ENMS_COUNT] =
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
    _enms *lvl2Enms[ENMS_COUNT] =
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
    _enms *lvl3Enms[ENMS_COUNT] =
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
    bool playLevel1 = true;
    bool playLevel2 = false;
    bool playLevel3 = false;
    bool endGame = false;

protected:
private:
};

#endif // _SCENE_H
