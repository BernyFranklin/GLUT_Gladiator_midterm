#include "../include/_scene.h"

 auto lastTime = chrono::steady_clock::now();
_scene::_scene()
{
    //ctor
}

_scene::~_scene()
{
    //dtor

     delete myLight;
     delete myKbMs;
     delete myModel;
  /*       _modelVBO *myVbo = new _modelVBO();
         _parallax *myPrlx = new _parallax();
         _quad *myQuad = new _quad();
         _player *ply = new _player();
         _sounds *snds = new _sounds();

         */
}

GLint _scene::initGL()
{
    glewInit();
    glClearColor(0.0,0.0,0.0,1.0); // background color
    glClearDepth(1.0);             // depth test value;
    glEnable(GL_DEPTH_TEST);       // Enable depth test
    glDepthFunc(GL_LEQUAL);        // True for less or Equal

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

   // glEnable(GL_COLOR_MATERIAL);

    myLight->setLight(GL_LIGHT0);
    myModel->initModel();
   // myVbo->modelInit("images/crate.jpeg");

    myPrlx->initPrlx("images/crate1.jpeg");
    ply->plyInit(8,4,"images/ply.png");


    snds->initSounds();
    snds->playMusic("sounds/MF-W-90.XM");


    for(int i=0; i<20; i++)
    {
       enm[i].enmsInit(7,2,"images/mon.png"); // need to fix : repeated reading
      //  enm[i].myTex->tex = enm[0].myTex->tex;
        enm[i].pos.x = (float)rand()/(float)(RAND_MAX)*5 -1.0;
        enm[i].pos.y = -1.4;

        enm[i].scale.x = enm[i].scale.y = (float)(rand()%12)/20.0;
    }
    return true;
}

void _scene::reSize(GLint width, GLint height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height; //keep track of window resize
    glViewport(0,0,width,height);// setting the viewport

    glMatrixMode(GL_PROJECTION); // initiate the projection
    glLoadIdentity();            // initialize the matrix with identity matrixc
    gluPerspective(45.0,aspectRatio,0.1,100.0);//setup perspective projection

    glMatrixMode(GL_MODELVIEW);  // initiate model & view matrix
    glLoadIdentity();

    dim.x = GetSystemMetrics(SM_CXSCREEN);
    dim.y = GetSystemMetrics(SM_CYSCREEN);
}

float _scene::deltaTime =0;      // initializing static variable

void _scene::drawScene()
{

    auto currenTime = chrono::steady_clock::now();

    chrono::duration<float> elapsed = currenTime - lastTime;
    _scene::deltaTime = elapsed.count();
    lastTime = currenTime;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // Clear buffers
    glLoadIdentity();
    glColor3f(1.0,0,1.0); // sett color for my model

  //  myModel->drawModel();
  //  myQuad->updateQuad();
  //  myQuad->drawQuad();

    glPushMatrix();
    glScalef(13.3,13.3,1);
    myPrlx->drawBckGrnd(dim.x,dim.y);
  //  myPrlx->scroll(true,myPrlx->UP,0.0005);
     myPrlx->scroll(true,myPrlx->LEFT,0.05 *deltaTime);
    glPopMatrix();
    ply->playerActions(deltaTime);
    ply->updateQuad();
    ply->drawQuad();


    for(int i=0;i<20;i++)
    {
        if(hit->isRadialCol(enm[i].pos, ply->pos,0.2,0.3, 0.6))
        {
            enm[i].actionTrigger =0;
        }

        enm[i].enmsActions(deltaTime);
        enm[i].drawEnms();
    }

    glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glTranslatef(0.0f, 0.0f, -6.0f);
        glutSolidTeapot(0.2f);
        glEnable(GL_TEXTURE_2D);
    glPopMatrix();
  // myVbo->drawmodel();
}
int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
     switch(uMsg)
     {
     case WM_KEYDOWN:
            myKbMs->wParam = wParam;
            myKbMs->keyPressed(myModel);
            myKbMs->keyPressed(myVbo);
            myKbMs->keyPressed(ply);
        break;

     case WM_KEYUP:
            ply->actionTrigger = ply->STAND;
        break;

     case WM_LBUTTONDOWN:
     case WM_RBUTTONDOWN:
            myKbMs->wParam = wParam;
            myKbMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
        break;
     case WM_LBUTTONUP:
     case WM_RBUTTONUP:
     case WM_MBUTTONUP:
           myKbMs->mouseEventUp();
         break;
     case WM_MOUSEMOVE:

         myKbMs->mouseMove(myModel,LOWORD(lParam),HIWORD(lParam));
        break;
     case WM_MOUSEWHEEL:

         myKbMs->mouseWheel(myModel,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;
     }
}

