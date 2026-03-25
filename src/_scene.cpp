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

    // Set backgrounds
    level1->initPrlx("images/lvl1.png");
    level2->initPrlx("images/lvl2.png");
    level3->initPrlx("images/lvl3.png");
    endScreen->initPrlx("images/endScreen.png");
    // Set players
    lvl1Player->playerInit(2.0f, 1.0f, 0.02f, 1.0f, -2.56f, "images/frog.png");
    lvl2Player->playerInit(2.0f, 3.0f, 0.0f, 1.0f, -2.26f, "images/mushroom.png");
    lvl3Player->playerInit(2.0f, 3.0f, 0.05f, 1.0f, -1.8f, "images/spaceman.png");
    lvl3Player->scale.x = 0.75f;
    lvl3Player->scale.y = 0.75f;
    // Set enemy objects
    for (int i = 0; i < _scene::ENMS_COUNT; i++)
    {
        lvl1Enms[i]->enmsInit(7, 1, 2.0f, 3.0f, 0.0f, 1.0f, "images/fallingSkull.png");
        float x = (float)(rand() % 7) - 3.0f;
        float y = (float)(rand() % 7) + 4.0f;
        lvl1Enms[i]->placeEmns(vec3{x, y, -7.0f}, deltaTime);
    }

    for (int i = 0; i < _scene::ENMS_COUNT; i++)
    {
        lvl2Enms[i]->enmsInit(6, 1, 0.0f, 1.0f, 0.0f, 1.0f, "images/fallingGas.png");
        float x = (float)(rand() % 7) - 3.0f;
        float y = (float)(rand() % 7) + 4.0f;
        lvl2Enms[i]->placeEmns(vec3{x, y, -7.0f}, deltaTime);
    }

    for (int i = 0; i < _scene::ENMS_COUNT; i++)
    {
        lvl3Enms[i]->enmsInit(7, 1, 1.0f, 2.0f, 0.0f, 1.0f, "images/fallingOrb.png");
        float x = (float)(rand() % 7) - 3.0f;
        float y = (float)(rand() % 7) + 4.0f;
        lvl3Enms[i]->placeEmns(vec3{x, y, -7.0f}, deltaTime);
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
    float collisionThreshX, collisionThreshY;
    // Initiiate current time for delta use
    auto currentTime = chrono::steady_clock::now();
    // Calculate the elapsed time since the last frame
    chrono::duration<float> elapsed = currentTime - lastTime;
    _scene::deltaTime = elapsed.count();
    // Update lastTime
    lastTime = currentTime;

    // Level 1
    if (playLevel1)
    {
        // Settings specific to level
        colCheck->xThresh = 0.25f;
        colCheck->yThresh = 0.25f;
        // Draw the level
        loadLevel(level1, lvl1Player, lvl1Enms, _scene::ENMS_COUNT);
        // Check if player has reached end of level
        if (lvl1Player->pos.x >= lvl1Player->END_OF_LEVEL)
        {
            playLevel1 = false;
            playLevel2 = true;
        }
    }
    // Level 2
    if (playLevel2)
    {
        // Settings specific to level
        colCheck->xThresh = 0.15f;
        colCheck->yThresh = 0.5f;
        level2->xMax = 1.0f;
        level2->yMin = 0.1f;
        // Draw the level
        loadLevel(level2, lvl2Player, lvl2Enms, _scene::ENMS_COUNT);
        // Check if player has reached end of level
        if (lvl2Player->pos.x >= lvl2Player->END_OF_LEVEL)
        {
            playLevel2 = false;
            playLevel3 = true;
        }
    }
    // Level 3
    if (playLevel3)
    {
        // Settings specific to level
        colCheck->xThresh = 0.25f;
        colCheck->yThresh = 0.5f;
        level3->xMax = 0.5f;
        level3->yMin = 0.0f;
        // Draw the level
        loadLevel(level3, lvl3Player, lvl3Enms, _scene::ENMS_COUNT);
        // Check if player has reached end of level
        if (lvl3Player->pos.x >= lvl3Player->END_OF_LEVEL)
        {
            playLevel3 = false;
            endGame = true;
        }
    }
    // End of game
    if (endGame)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Clear buffers
        glLoadIdentity();

        glPushMatrix();
        glScalef(13.3f, 13.3f, 1.0f);
        endScreen->xMin = 0.0f;
        endScreen->xMax = 1.0f;
        endScreen->yMin = 0.0f;
        endScreen->yMax = 1.0f;
        endScreen->drawBckGrnd(dim.x, dim.y);
        glPopMatrix();
    }
}

void _scene::loadLevel(_parallax *level, _player *player, _enms *enms[], int enmsArraySize)
{
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw background parallax
    glPushMatrix();
    glScalef(13.3f, 13.3f, 1.0f);
    level->drawBckGrnd(dim.x, dim.y);
    glPopMatrix();

    glPushMatrix();
    // Draw player
    player->playerActions(deltaTime);
    player->updateQuad();
    player->drawQuad();
    // Draw enemies
    for (int i = 0; i < enmsArraySize; i++)
    {
        enms[i]->enmsActions(deltaTime);
        enms[i]->updateQuad();
        enms[i]->drawQuad();
    }
    glPopMatrix();

    // Check for collisions
    for (int i = 0; i < enmsArraySize; i++)
    {
        if (colCheck->isLinearCol(
                vec2{player->pos.x, player->pos.y},
                vec2{enms[i]->pos.x, enms[i]->pos.y},
                colCheck->xThresh,
                colCheck->yThresh))
        {
            enms[i]->actionTrigger = enms[i]->HIT;
            player->actionTrigger = player->HIT;
            if (!enms[i]->isDead)
            {
                enms[i]->isDead = true;
                hitCounter++;
            }
        }
    }
    if (hitCounter >= MAX_HITS && player->actionTrigger != player->HIT)
    {
        player->pos.x = player->START_OF_LEVEL;
        hitCounter = 0;
    }
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
        myKeys->keyPressed(lvl2Player);
        myKeys->keyPressed(lvl3Player);
        break;

    case WM_KEYUP:
        myKeys->wParam = wParam;
        myKeys->keyUp(lvl1Player);
        myKeys->keyUp(lvl2Player);
        myKeys->keyUp(lvl3Player);
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
