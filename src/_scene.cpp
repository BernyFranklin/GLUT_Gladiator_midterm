#include "_scene.h"

auto lastTime = chrono::steady_clock::now();
_scene::_scene()
{
    // ctor

    mouse.x = 0;
    mouse.y = 0;
    mouse.z = -6;
}

_scene::~_scene()
{
    // dtor
}

GLint _scene::initGL()
{
    glewInit();
    glClearColor(0.0, 0.0, 0.0, 1.0); // background color
    glClearDepth(1.0);                // depth test value;
    glEnable(GL_DEPTH_TEST);          // Enable depth test
    glDepthFunc(GL_LEQUAL);           // True for less or Equal

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set background
    level1->initPrlx("images/lvl1.png");
    level2->initPrlx("images/lvl2.png");
    level3->initPrlx("images/lvl3.png");
    lvl1Player->lvl1PlayerInit(
        lvl1Player->xFrames1,
        lvl1Player->yFrames1, "images/frog.png");

    for (int i = 0; i < sizeof(lvl1Enms) / sizeof(lvl1Enms[0]); i++)
    {
        lvl1Enms[i]->enmsInit(7, 1, "images/obj1.png");
        float x = (float)(rand() % 7) - 3.0f;
        float y = (float)(rand() % 4) + 4.0f;
        lvl1Enms[i]->placeEmns(vec3{x, y, -7.0f}, deltaTime);
    }
    return true;
}

void _scene::reSize(GLint width, GLint height)
{
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height; // keep track of window resize
    glViewport(0, 0, width, height);                        // setting the viewport

    glMatrixMode(GL_PROJECTION);                   // initiate the projection
    glLoadIdentity();                              // initialize the matrix with identity matrixc
    gluPerspective(45.0, aspectRatio, 0.1, 100.0); // setup perspective projection

    glMatrixMode(GL_MODELVIEW); // initiate model & view matrix
    glLoadIdentity();

    dim.x = GetSystemMetrics(SM_CXSCREEN);
    dim.y = GetSystemMetrics(SM_CYSCREEN);
}

float _scene::deltaTime = 0; // initializing static variable

void _scene::drawScene()
{
    // Level 1
    if (playLevel1)
    {
        // Initiiate current time for delta use
        auto currentTime = chrono::steady_clock::now();
        // Calculate the elapsed time since the last frame
        chrono::duration<float> elapsed = currentTime - lastTime;
        _scene::deltaTime = elapsed.count();
        // Update lastTime
        lastTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Clear buffers
        glLoadIdentity();

        glPushMatrix();
        glScalef(13.3f, 13.3f, 1.0f);
        level1->drawBckGrnd(dim.x, dim.y);
        glPopMatrix();

        glPushMatrix();
        // Draw player
        lvl1Player->playerActions(deltaTime);
        lvl1Player->updateQuad();
        lvl1Player->drawQuad();
        // Draw enemies
        for (int i = 0; i < sizeof(lvl1Enms) / sizeof(lvl1Enms[0]); i++)
        {
            lvl1Enms[i]->enmsActions(deltaTime);
            lvl1Enms[i]->updateQuad();
            lvl1Enms[i]->drawQuad();
        }
        glPopMatrix();

        // Check for collisions
        for (int i = 0; i < sizeof(lvl1Enms) / sizeof(lvl1Enms[0]); i++)
        {
            if (colCheck->isLinearCol(
                    vec2{lvl1Player->pos.x, lvl1Player->pos.y},
                    vec2{lvl1Enms[i]->pos.x, lvl1Enms[i]->pos.y}))
            {
                lvl1Enms[i]->actionTrigger = lvl1Enms[i]->HIT;
                lvl1Player->actionTrigger = lvl1Player->HIT;
                if (!lvl1Enms[i]->isDead)
                {
                    lvl1Enms[i]->isDead = true;
                    hitCounter++;
                }
                cout << "Hit counter: " << hitCounter << endl;
            }
        }
        if (hitCounter >= MAX_HITS)
        {
            // TO DO: Add constant for start position
            lvl1Player->pos.x = lvl1Player->START_OF_LEVEL;
            hitCounter = 0;
        }

        if (lvl1Player->pos.x >= lvl1Player->END_OF_LEVEL)
        {
            playLevel1 = false;
            playLevel2 = true;
        }
    }

    if (playLevel2)
    {
        // Initiiate current time for delta use
        auto currentTime = chrono::steady_clock::now();
        // Calculate the elapsed time since the last frame
        chrono::duration<float> elapsed = currentTime - lastTime;
        _scene::deltaTime = elapsed.count();
        // Update lastTime
        lastTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Clear buffers
        glLoadIdentity();

        glPushMatrix();
        glScalef(13.3f, 13.3f, 1.0f);
        level2->xMax = 1.0f;
        level2->yMin = 0.1f;
        level2->drawBckGrnd(dim.x, dim.y);
        glPopMatrix();
    }
}

void _scene::drawScene2()
{
    auto currentTime = chrono::steady_clock::now();

    chrono::duration<float> elapsed = currentTime - lastTime;
    _scene::deltaTime = elapsed.count();
    lastTime = currentTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Clear buffers
    glLoadIdentity();
    glColor3f(1.0, 0, 1.0); // sett color for my model

    glPushMatrix();
    glScalef(13.3f, 13.3f, 1.0f);
    level2->xMax = 1.0f;
    level2->yMin = 0.1f;
    level2->drawBckGrnd(dim.x, dim.y);
    glPopMatrix();

    glPushMatrix();
    lvl1Player->pos.y = -1.16f;
    lvl1Player->playerActions(deltaTime);
    lvl1Player->updateQuad();
    lvl1Player->drawQuad();
    glPopMatrix();
}

void _scene::drawScene3()
{
    auto currentTime = chrono::steady_clock::now();

    chrono::duration<float> elapsed = currentTime - lastTime;
    _scene::deltaTime = elapsed.count();
    lastTime = currentTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Clear buffers
    glLoadIdentity();
    glColor3f(1.0, 0, 1.0); // sett color for my model

    glPushMatrix();
    glScalef(13.3f, 13.3f, 1.0f);
    level3->xMax = 0.5f;
    level3->drawBckGrnd(dim.x, dim.y);
    glPopMatrix();

    glPushMatrix();
    lvl1Player->pos.y = -1.06f;
    lvl1Player->playerActions(deltaTime);
    lvl1Player->updateQuad();
    lvl1Player->drawQuad();
    glPopMatrix();
}

void _scene::mouseMapping(int x, int y)
{
    GLint viewPort[4];        // for the window
    GLdouble modelViewM[16];  // model and camera
    GLdouble projectionM[16]; // for the projectio
    GLfloat winX, winY, winZ; // mouse clicks

    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewM);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionM);
    glGetIntegerv(GL_VIEWPORT, viewPort);

    winX = (GLfloat)x;
    winY = (GLfloat)viewPort[3] - y;

    glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelViewM, projectionM, viewPort, &mouse.x, &mouse.y, &mouse.z);
}

int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:
        myKeys->wParam = wParam;
        myKeys->keyPressed(lvl1Player);
        break;

    case WM_KEYUP:
        myKeys->wParam = wParam;
        myKeys->keyUp(lvl1Player);
        break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        mouseMapping(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:

        break;
    case WM_MOUSEMOVE:
        break;
    case WM_MOUSEWHEEL:
        break;
    }
}
