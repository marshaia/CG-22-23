#include <stdio.h>

#ifndef GENERATOR_POINTHOLDER_H
#define GENERATOR_POINTHOLDER_H

typedef struct pointHolder{
    float* list;
    int size;
    int current;
} *PointHolder;

PointHolder initPointHolder();

void checkMem(PointHolder self);

void addPoint(PointHolder self,float x,float y,float z);

void printToFile(PointHolder self,FILE* file);

#endif //GENERATOR_POINTHOLDER_H
