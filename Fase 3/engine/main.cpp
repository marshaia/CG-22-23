

#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include "data/world.h"
#include "pugixml/pugixml.hpp"

world myWorld;
float camBeta = 45, camAlpha = 0;
float camRadius = 30.0f;
bool freeCamMode = false;
int timebase = 0,fpsTimeBase = 0;
float frame;
char fileName[64];

float toRadians(float degree) {
    return (float) (degree * 0.01745329252); // 2*PI / 360
}

void setNewPosXYZ () {
    float actX = camRadius * cos(toRadians(camBeta)) * sin(toRadians(camAlpha));
    float actY = camRadius * sin(toRadians(camBeta));
    float actZ = camRadius * cos(toRadians(camBeta)) * cos(toRadians(camAlpha));
    myWorld.myCamera.setPosition(actX,actY,actZ);
    myWorld.myCamera.setLookAt(0,0,0);
    myWorld.myCamera.setUp(0,1,0);
}


void updateFPSCounter(){
    frame++;
    int time = glutGet(GLUT_ELAPSED_TIME);
    if (time - fpsTimeBase > 1000) {
        float fps = float(frame) / (float(time - fpsTimeBase) / 1000);
        char windowTitle[128];
        sprintf(windowTitle,"CG 22/23 G30 - Engine - %s - FPS: %.2f",fileName,fps);
        glutSetWindowTitle(windowTitle);
        fpsTimeBase = time;
        frame = 0;
    }
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = float(w) / float(h);

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(myWorld.myCamera.fov ,ratio, myWorld.myCamera.near ,myWorld.myCamera.far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void renderScene() {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    if (freeCamMode) setNewPosXYZ();
    gluLookAt(myWorld.myCamera.posX,myWorld.myCamera.posY,myWorld.myCamera.posZ,
              myWorld.myCamera.lookX,myWorld.myCamera.lookY,myWorld.myCamera.lookZ,
              myWorld.myCamera.upX,myWorld.myCamera.upY,myWorld.myCamera.upZ);

    int time = glutGet(GLUT_ELAPSED_TIME);
    float elapsedTime = float(time - timebase) / 1000;
    timebase = time;

    myWorld.draw(elapsedTime);
    updateFPSCounter();

    // End of frame
    glutSwapBuffers();
}



// write function to process keyboard events
void keyboardHandler(unsigned char key, int x, int y){
    switch (key) {
        case '+': camRadius -= 5; break;
        case '-': camRadius += 5; break;

        default:
            break;
    }
    glutPostRedisplay();
}


void keyboardHandlerSpecial(int key_code, int x, int y){
    switch (key_code) {
        case GLUT_KEY_F1: glPolygonMode(GL_FRONT,GL_FILL); break;
        case GLUT_KEY_F2: glPolygonMode(GL_FRONT,GL_LINE); break;
        case GLUT_KEY_F3: glPolygonMode(GL_FRONT,GL_POINT); break;
        case GLUT_KEY_F4: freeCamMode = !freeCamMode; break;

        case (GLUT_KEY_UP): camBeta += 5; break;
        case (GLUT_KEY_DOWN): camBeta -= 5; break;
        case (GLUT_KEY_LEFT):  camAlpha -= 10; break;
        case (GLUT_KEY_RIGHT): camAlpha += 10; break;

        default:
            break;
    }

    //Free Cam Boundary Check
    if(camBeta >= 85) camBeta = 85;
    if(camBeta <= -85) camBeta = -85;
    if(camAlpha >= 360) camAlpha -= 360;
    if(camAlpha < 0) camAlpha += 360;

    glutPostRedisplay();
}


int main(int argc, char **argv) {

    using namespace pugi;
    using namespace std;

    if(argc != 2) {
        printf("World Configuration File missing\n");
        exit(1);
    }
    strcpy(fileName,argv[1]);


// init GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(myWorld.myWindow.width,myWorld.myWindow.height);

    float ratio = ((float) (myWorld.myWindow.width * 1.0)) / ((float) myWorld.myWindow.height);
    gluPerspective(myWorld.myCamera.fov ,ratio, myWorld.myCamera.near ,myWorld.myCamera.far);
    char windowTitle[128];
    sprintf(windowTitle,"CG 22/23 G30 - Engine - %s - FPS: 0",fileName);
    glutCreateWindow(windowTitle);

// Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

// put here the registration of the keyboard callbacks
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(keyboardHandlerSpecial);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// GLEW
    if (glewInit() != GLEW_OK) {
        printf("Glew Failed to load\n");
        return -1;
    }
    glEnableClientState(GL_VERTEX_ARRAY);

// Load World
    myWorld.loadXML(fileName);
    glutReshapeWindow(myWorld.myWindow.width,myWorld.myWindow.height);


// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
