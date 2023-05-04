//
// Created by vicshadow on 25-02-2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "model.h"

model::model(string filename) {
    FILE* file = fopen(filename.c_str(),"r");
    if(!file) throw 100;
    this->name = filename;

    fread(&this->numPoints,sizeof (int), 1,file);
    this->points = (float*) malloc(sizeof (float) * this->numPoints);
    fread(this->points,sizeof (float ), this->numPoints,file);

    // fscanf(file,"%d\n",&this->numPoints);
    // this->points = (float*) malloc(sizeof (float) * this->numPoints);
    // for(int i = 0;i < this->numPoints;i += 3){
    //    fscanf(file,"%f;%f;%f\n",&this->points[i],&this->points[i+1],&this->points[i+2]);
    // }
}

void model::drawModel(){
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,1.0f,1.0f); // COLOR
    for(int i = 0;i < this->numPoints;i+=3){
        glVertex3f(this->points[i],this->points[i+1],this->points[i+2]);
    }
    // TEXTURE???
    glEnd();
}
