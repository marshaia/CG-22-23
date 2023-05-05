//
// Created by vicshadow on 25-02-2023.
//

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include "model.h"

model::model(const string& filename) {
    FILE* file = fopen(filename.c_str(),"r");
    if(!file) throw std::invalid_argument("Model: Model Name '"+filename+"' not found");
    this->name = filename;
    int numFloats = 0;

    fread(&numFloats,sizeof (int), 1,file);
    this->points = (float*) malloc(sizeof (float) * numFloats);
    fread(this->points,sizeof (float ), numFloats,file);
    this->numPoints = numFloats/3;

    glGenBuffers(1,buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, (long) (sizeof(float) * numFloats), points, GL_STATIC_DRAW);


    // fscanf(file,"%d\n",&this->numPoints);
    // this->points = (float*) malloc(sizeof (float) * this->numPoints);
    // for(int i = 0;i < this->numPoints;i += 3){
    //    fscanf(file,"%f;%f;%f\n",&this->points[i],&this->points[i+1],&this->points[i+2]);
    // }
}

void model::drawModel() const{

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
    glColor3f(1.0f,1.0f,1.0f);
    glDrawArrays(GL_TRIANGLES, 0, this->numPoints);

    /*
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,1.0f,1.0f); // COLOR
    for(int i = 0;i < this->numPoints;i+=3){
        glVertex3f(this->points[i],this->points[i+1],this->points[i+2]);
    }
    // TEXTURE???
    glEnd();
    */
}
