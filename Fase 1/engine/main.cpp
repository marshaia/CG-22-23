#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include "data/world.h"
#include "pugixml/pugixml.hpp"

world myWorld;
float beta = 0, alpha = 0;
float dist = 6.0f;
bool freeMode = false; //Free cam toggle

float toRadians(float degree) {
    return (float) (degree * 0.01745329252); //It also works :v (but u can revert)
    // return degree * ((2 * acos(0.0)) / 180);
}

void setNewPosXYZ () {
    float actX = dist * cos(toRadians(beta)) * sin(toRadians(alpha));
    float actY = dist * sin(toRadians(beta));
    float actZ = dist * cos(toRadians(beta)) * cos(toRadians(alpha));
    myWorld.myCamera.setPosition(actX,actY,actZ);
}

void drawModel(model model){
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0;i < model.numPoints;i+=3){
        glVertex3f(model.points[i],model.points[i+1],model.points[i+2]);
    }
    glEnd();
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
    if (freeMode) setNewPosXYZ();
    gluLookAt(myWorld.myCamera.posX,myWorld.myCamera.posY,myWorld.myCamera.posZ,
              myWorld.myCamera.lookX,myWorld.myCamera.lookY,myWorld.myCamera.lookZ,
              myWorld.myCamera.upX,myWorld.myCamera.upY,myWorld.myCamera.upZ);

    // put axis drawing in here
    drawAxis();

    myWorld.draw();

    // End of frame
    glutSwapBuffers();
}



// write function to process keyboard events
void keyboardHandler(unsigned char key, int x, int y){
    switch (key) {
        case '1': myWorld.myCamera.setPosition(3,8,5);   break;
        case '2': myWorld.myCamera.setPosition(-2,3,-4); break;
        case '3': myWorld.myCamera.setPosition(-5,-2,2); break;
        case '4': myWorld.myCamera.setPosition(4,5,-8);   break;

        // align with x and z axis, respectively
        case 'x': myWorld.myCamera.setPosition(8,10,0); break;
        case 'z': myWorld.myCamera.setPosition(0,10,8); break;

        case '+': dist -= 0.5; break; //setNewPosXYZ(); break;
        case '-': dist += 0.5; break; //setNewPosXYZ(); break;
    }
    glutPostRedisplay();
}


void keyboardHandlerSpecial(int key_code, int x, int y){
    switch (key_code) {
        case GLUT_KEY_F1: glPolygonMode(GL_FRONT,GL_FILL); break;
        case GLUT_KEY_F2: glPolygonMode(GL_FRONT,GL_LINE); break;
        case GLUT_KEY_F3: glPolygonMode(GL_FRONT,GL_POINT); break;
        case GLUT_KEY_F4: freeMode = !freeMode; break;

        case (GLUT_KEY_UP): beta += 3; break; //setNewPosXYZ(); break;
        case (GLUT_KEY_DOWN): beta -= 3; break;//setNewPosXYZ(); break;
        case (GLUT_KEY_LEFT):  alpha -= 6; break;//setNewPosXYZ(); break;
        case (GLUT_KEY_RIGHT): alpha += 6; break; //setNewPosXYZ(); break;
    }

    glutPostRedisplay();
}


int main(int argc, char **argv) {

    using namespace pugi;
    using namespace std;

    if(argc != 2) {
        printf("World Configuration File missing\n");
        exit(1);
    }

    myWorld.loadXML(argv[1]);

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(myWorld.myWindow.width,myWorld.myWindow.height);

    float ratio = ((float) myWorld.myWindow.width) * 1.0 / ((float) myWorld.myWindow.height);
    gluPerspective(myWorld.myCamera.fov ,ratio, myWorld.myCamera.near ,myWorld.myCamera.far);
    glutCreateWindow("CG 22/23 G30 - Engine");

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
