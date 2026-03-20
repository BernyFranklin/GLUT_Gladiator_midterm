#ifndef _SCENE_H
#define _SCENE_H

#include "_common.h"
#include "_lightsettings.h"
#include "_model.h"
#include "_inputs.h"
#include "_modelvbo.h"
#include "_parallax.h"
#include "_quad.h"
#include "_player.h"
#include "_collisioncheck.h"
#include "_sounds.h"
#include "_enms.h"

class _scene
{
    public:

        _scene();
        virtual ~_scene();

        GLint initGL();  // initialize the openGL contents
        void reSize(GLint, GLint);//to handle resize window
        void drawScene(); // render the final scene
        int winMsg( HWND	hWnd,			// Handle For This Window
                    UINT	uMsg,			// Message For This Window
                    WPARAM	wParam,			// Additional Message Information
                    LPARAM	lParam);

           static float deltaTime;


         _lightSettings *myLight = new _lightSettings();
         _inputs *myKbMs = new _inputs();
         _model *myModel = new _model();
         _modelVBO *myVbo = new _modelVBO();
         _parallax *myPrlx = new _parallax();
         _quad *myQuad = new _quad();
         _player *ply = new _player();
         _sounds *snds = new _sounds();
         _collisionCheck *hit = new _collisionCheck();
         _enms enm[20];

         vec2 dim;  //window size

    protected:

    private:
};

#endif // _SCENE_H
