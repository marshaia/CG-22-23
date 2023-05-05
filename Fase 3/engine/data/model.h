#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H


#include <GL/glew.h>
#include <GL/glut.h>
#include <string>

using namespace std;

class model {
public:
    string name;
    int numPoints;
    //color
    //texture
    float *points;
    GLuint buffer[1]{};

    explicit model(const string& filename);

    void drawModel() const;
};


#endif //ENGINE_MODEL_H
