#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

using namespace std;

class model {
public:
    string name;
    int numPoints;
    //color
    //texture
    float *points;

    model(string filename);

    void drawModel();
};


#endif //ENGINE_MODEL_H
