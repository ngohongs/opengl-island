//----------------------------------------------------------------------------------------
/**
 * \file       CApplication.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing an application with functions for GLUT window
 *
 * GLUT functions are need for initialization and handling of a window events
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CApplication.h"

void Draw() {
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    auto& nodes = gameState.MRoot->GetSceneNodes();

    for (unsigned int i = 0; i < nodes.size(); ++i) {
        // Draw id to stencil buffer
        glStencilFunc(GL_ALWAYS, i + 1, -1);
        // Draw object
        nodes[i]->Draw();
    }
    glutSwapBuffers();
}

void Timer(int value) {
    // Calculate time delta
    int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
    gameState.MTimeDelta = (currentFrameTime - gameState.MLastFrameTime) / 1000.0f;
    gameState.MLastFrameTime = currentFrameTime;

    // Update object's time
    gameState.MRoot->Update(gameState.MTimeDelta);

    // Move camera
    if (gameState.MKeyMap[KEY_RIGHT_ARROW] == true)
        gameState.MCamera.Pan(-PAN_ANGLE);
    if (gameState.MKeyMap[KEY_LEFT_ARROW] == true)
        gameState.MCamera.Pan(PAN_ANGLE);
    if (gameState.MKeyMap[KEY_UP_ARROW] == true)
        gameState.MCamera.Tilt(TILT_ANGLE);
    if (gameState.MKeyMap[KEY_DOWN_ARROW] == true)
        gameState.MCamera.Tilt(-TILT_ANGLE);
    if (gameState.MKeyMap[KEY_LOWER_W] == true)
        gameState.MCamera.MoveForwardBackward(FRONT_BACK_MOVEMENT_COEF);
    if (gameState.MKeyMap[KEY_LOWER_S] == true)
        gameState.MCamera.MoveForwardBackward(-FRONT_BACK_MOVEMENT_COEF);
    if (gameState.MKeyMap[KEY_LOWER_A] == true)
        gameState.MCamera.MoveRightLeft(RIGHT_LEFT_MOVEMENT_COEF);
    if (gameState.MKeyMap[KEY_LOWER_D] == true)
        gameState.MCamera.MoveRightLeft(-RIGHT_LEFT_MOVEMENT_COEF);

    // Flight view
    if (gameState.MView == 3)
    {
        gameState.MSplineTime += gameState.MTimeDelta / CAMERA_FLIGHT_SLOW;
        if (gameState.MSplineTime >= gameState.MCameraSpline.GetControlPointSize())
            gameState.MSplineTime -= gameState.MCameraSpline.GetControlPointSize();
        glm::vec3 direction = glm::normalize(gameState.MCameraSpline.GetSplineLoopGradient(gameState.MSplineTime));
        glm::vec3 position = gameState.MCameraSpline.GetSplineLoopPoint(gameState.MSplineTime);
        glm::vec3 rightVector = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 upVector = glm::normalize(glm::cross(rightVector, direction));
        gameState.MCamera.SetCamera(position, direction, upVector);
    }

    // Boat view
    if (gameState.MView == 4)
    {
        glm::vec3 position = gameState.MShip->GetPosition();
        glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 direction = glm::normalize(gameState.MShip->GetDirection());
        gameState.MCamera.MEye = position + 0.75f * direction + upVector;
        gameState.MCamera.MUpVector = upVector;
    }
    glutTimerFunc(33, Timer, 0);
    glutPostRedisplay();
}

void Reshape(int newWidth, int newHeight) {
    gameState.MWindowWidth = newWidth;
    gameState.MWindowHeight = newHeight;

    glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
}

void MousePressed(int button, int state, int mouseX, int mouseY)
{
    if (state != GLUT_DOWN)
        return;
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON)
    {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

        unsigned char pixelID;
        glReadPixels(mouseX, windowHeight - mouseY - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &pixelID);
        auto& root = gameState.MRoot;
        auto& nodes = root->GetSceneNodes();

        // Held item
        int& held = gameState.MHolding;

        // Clicked item
        int id = (int)pixelID;

        // If holding nothing
        if (held == -1)
        {
            // Pickup bucket/torch
            if (id == 11 || id == 13)
            {
                held = id;
                nodes[id - 1]->SwitchPicked();
            }
        }
        // If holding bucket
        else if (held == 11)
        {
            // If ground clicked
            if (id == 2)
            {
                held = -1;
                nodes[11 - 1]->SwitchPicked();
                nodes[11 - 1]->SetPosition(BUCKET_POSITION);
                nodes[11 - 1]->SetDirection(glm::vec3(0.0f, 0.0f, -1.0f));
                nodes[11 - 1]->SetUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
            }
            // If fire clicked
            if (id == 14 || id == 9)
            {
                nodes[14 - 1]->SetOn(false);
                gameState.light = NO_CAMPFIRE_LIGHT;
            }
        }
        // If holding torch
        else if (held == 13)
        {
            // If ground clicked
            if (id == 2)
            {
                held = -1;
                nodes[13 - 1]->SwitchPicked();
                nodes[13 - 1]->SetPosition(TORCH_POSITION);
                nodes[13 - 1]->SetDirection(glm::vec3(0.0f, 0.0f, -1.0f));
                nodes[13 - 1]->SetUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
            }
            // If campfire clicked
            if (id == 14 || id == 9)
            {
                nodes[14 - 1]->SetOn(true);
                gameState.light = CAMPFIRE_LIGHT;
            }
            // If cannon clicked
            if (id == 12)
            {
                nodes[15 - 1]->SetTimeToLive(EXPLOSION_DURATION);
            }
        }
    }
}

void MouseMotion(int mouseX, int mouseY) {
    // If in flight mode
    if (gameState.MView == 3)
        return;

    // If movement registered in x axis
    if (mouseX != gameState.MWindowWidth / 2) {
        float deltaX = 0.2f * (mouseX - gameState.MWindowWidth / 2);
        if (fabs(deltaX) < 45.0f) {
            gameState.MCamera.Pan(-deltaX);
        }
    }
    // If movement registered in y axis
    if (mouseY != gameState.MWindowHeight / 2) {
        float deltaY = 0.2f * (mouseY - gameState.MWindowHeight / 2);
        if (fabs(deltaY) < 45.0f)
            gameState.MCamera.Tilt(-deltaY);
    };

    // Recenter cursor
    glutWarpPointer(gameState.MWindowWidth / 2, gameState.MWindowHeight / 2);

    glutPostRedisplay();
}

void KeyPressed(unsigned char keyPressed, int mouseX, int mouseY) {

    switch (keyPressed) {
        case 27: // escape
    #ifndef __APPLE__
            glutLeaveMainLoop();
    #else
            exit(0);
    #endif
            break;
        case 'w':
            gameState.MKeyMap[KEY_LOWER_W] = true;
            break;
        case 's':
            gameState.MKeyMap[KEY_LOWER_S] = true;
            break;
        case 'a':
            gameState.MKeyMap[KEY_LOWER_A] = true;
            break;
        case 'd':
            gameState.MKeyMap[KEY_LOWER_D] = true;
            break;
        // Free camera mode
        case 'c':
            if (!gameState.MCameraControl)
                break;
            if (gameState.MFreeCamera)
                glutPassiveMotionFunc(0);
            else
                glutPassiveMotionFunc(MouseMotion);
            gameState.MFreeCamera = !gameState.MFreeCamera;
            break;
        // View change
        case 'f':
            gameState.MView = (gameState.MView + 1) % 5;
            switch (gameState.MView)
            {
                case 0:
                    gameState.MCamera.SetCamera(STATIC_VIEW_ONE_EYE, STATIC_VIEW_ONE_DIR, STATIC_VIEW_ONE_UP);
                    gameState.MCameraControl = true;
                    break;
                case 1:
                    gameState.MCamera.SetCamera(STATIC_VIEW_TWO_EYE, STATIC_VIEW_TWO_DIR, STATIC_VIEW_TWO_UP);
                    break;
                case 2:
                    gameState.MCamera.SetCamera(STATIC_VIEW_THREE_EYE, STATIC_VIEW_THREE_DIR, STATIC_VIEW_THREE_UP);
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    break;
                }
            break;
        // Directional light on/off switch
        case 'r':
            if (gameState.MDay)
                gameState.dirLight = NIGHT_LIGHT;
            else
                gameState.dirLight = DAY_LIGHT;
            gameState.MDay = !gameState.MDay;
            break;
        default:
            ; // printf("Unrecognized key pressed\n");
    }
}

void KeyReleased(unsigned char keyReleased, int mouseX, int mouseY) {
    switch (keyReleased) {
    case 'w':
        gameState.MKeyMap[KEY_LOWER_W] = false;
        break;
    case 's':
        gameState.MKeyMap[KEY_LOWER_S] = false;
        break;
    case 'a':
        gameState.MKeyMap[KEY_LOWER_A] = false;
        break;
    case 'd':
        gameState.MKeyMap[KEY_LOWER_D] = false;
        break;
    default:
        ;
    }
}

void SpecialKeyPressed(int specKeyPressed, int mouseX, int mouseY) {
    switch (specKeyPressed) {
        case GLUT_KEY_RIGHT:
            gameState.MKeyMap[KEY_RIGHT_ARROW] = true;
            break;
        case GLUT_KEY_LEFT:
            gameState.MKeyMap[KEY_LEFT_ARROW] = true;
            break;
        case GLUT_KEY_UP:
            gameState.MKeyMap[KEY_UP_ARROW] = true;
            break;
        case GLUT_KEY_DOWN:
            gameState.MKeyMap[KEY_DOWN_ARROW] = true;
            break;
        default:
            ;
    }
}

void SpecialKeyReleased(int specKeyReleased, int mouseX, int mouseY) {
    switch (specKeyReleased) {
        case GLUT_KEY_RIGHT:
            gameState.MKeyMap[KEY_RIGHT_ARROW] = false;
            break;
        case GLUT_KEY_LEFT:
            gameState.MKeyMap[KEY_LEFT_ARROW] = false;
            break;
        case GLUT_KEY_UP:
            gameState.MKeyMap[KEY_UP_ARROW] = false;
            break;
        case GLUT_KEY_DOWN:
            gameState.MKeyMap[KEY_DOWN_ARROW] = false;
            break;
        default:
            ;
    }
}

void CApplication::ApplicationInit() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gameState.MLastFrameTime = glutGet(GLUT_ELAPSED_TIME);
    gameState.InitializeGame();
}

int CApplication::WindowInit(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE.c_str());

    glutDisplayFunc(Draw);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyPressed);
    glutKeyboardUpFunc(KeyReleased);
    glutSpecialFunc(SpecialKeyPressed);    
    glutSpecialUpFunc(SpecialKeyReleased);
    glutMouseFunc(MousePressed);
    glutTimerFunc(33, Timer, 0);
    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");

    ApplicationInit();

    glutMainLoop();

    gameState.MRoot->Destroy();
    return 0;
}