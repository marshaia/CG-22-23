#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <cstring>
#include "data/world.h"
#include "pugixml/pugixml.hpp"

world myWorld;
float beta = 45, alpha = 0;
float camRadius = 10.0f;
bool freeCamMode = false;
int timebase;
float frame;
char fileName[64];

float toRadians(float degree) {
    return (float) (degree * 0.01745329252); // 2*PI / 360
}

void setNewPosXYZ () {
    float actX = camRadius * cos(toRadians(beta)) * sin(toRadians(alpha));
    float actY = camRadius * sin(toRadians(beta));
    float actZ = camRadius * cos(toRadians(beta)) * cos(toRadians(alpha));
    myWorld.myCamera.setPosition(actX,actY,actZ);
    myWorld.myCamera.setLookAt(0,0,0);
    myWorld.myCamera.setUp(0,1,0);
}


void drawAxis(){
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(-1000.0f,0.0f,0.0f);
    glVertex3f(1000.0f,0.0f,0.0f);

    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f,-1000.0f,0.0f);
    glVertex3f(0.0f,1000.0f,0.0f);

    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f,0.0f,-1000.0f);
    glVertex3f(0.0f,0.0f,1000.0f);
    glEnd();
}

void drawAxisSized(float size){
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(size,0.0f,0.0f);

    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,size,0.0f);

    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,size);
    glEnd();
}

void updateFPSCounter(){
    frame++;
    int time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        float fps = frame * 1000.0 / (time - timebase);
        char windowTitle[128];
        sprintf(windowTitle,"CG 22/23 G30 - Engine - %s - FPS: %.2f",fileName,fps);
        glutSetWindowTitle(windowTitle);
        timebase = time;
        frame = 0;
    }
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

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


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    if (freeCamMode) setNewPosXYZ();
    gluLookAt(myWorld.myCamera.posX,myWorld.myCamera.posY,myWorld.myCamera.posZ,
              myWorld.myCamera.lookX,myWorld.myCamera.lookY,myWorld.myCamera.lookZ,
              myWorld.myCamera.upX,myWorld.myCamera.upY,myWorld.myCamera.upZ);

    // put axis drawing in here
    drawAxis();

    myWorld.draw();
    updateFPSCounter();

    // End of frame
    glutSwapBuffers();
}



// write function to process keyboard events
void keyboardHandler(unsigned char key, int x, int y){
    switch (key) {
        case '+': camRadius -= 0.5; break; //setNewPosXYZ(); break;
        case '-': camRadius += 0.5; break; //setNewPosXYZ(); break;
    }
    glutPostRedisplay();
}


void keyboardHandlerSpecial(int key_code, int x, int y){
    switch (key_code) {
        case GLUT_KEY_F1: glPolygonMode(GL_FRONT,GL_FILL); break;
        case GLUT_KEY_F2: glPolygonMode(GL_FRONT,GL_LINE); break;
        case GLUT_KEY_F3: glPolygonMode(GL_FRONT,GL_POINT); break;
        case GLUT_KEY_F4: freeCamMode = !freeCamMode; break;

        case (GLUT_KEY_UP): beta += 5; break;
        case (GLUT_KEY_DOWN): beta -= 5; break;
        case (GLUT_KEY_LEFT):  alpha -= 10; break;
        case (GLUT_KEY_RIGHT): alpha += 10; break;
    }

    //Free Cam Boundary Check
    if(beta >= 85) beta = 85;
    if(beta <= -85) beta = -85;
    if(alpha >= 360) alpha -= 360;
    if(alpha < 0) alpha += 360;

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
    myWorld.loadXML(fileName);

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(myWorld.myWindow.width,myWorld.myWindow.height);

    float ratio = ((float) myWorld.myWindow.width) * 1.0 / ((float) myWorld.myWindow.height);
    gluPerspective(myWorld.myCamera.fov ,ratio, myWorld.myCamera.near ,myWorld.myCamera.far);
    char windowTitle[128];
    sprintf(windowTitle,"CG 22/23 G30 - Engine - %s - FPS: 0",fileName);
    glutCreateWindow(windowTitle);

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// put here the registration of the keyboard callbacks
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(keyboardHandlerSpecial);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
