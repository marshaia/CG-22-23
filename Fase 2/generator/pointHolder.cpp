#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pointHolder.h"

PointHolder initPointHolder(){
    PointHolder res = (PointHolder) malloc(sizeof (pointHolder));
    res->size = 3;
    res->current = 0;
    res->list = (float*) malloc(sizeof(float) * res->size);
    return res;
}

void checkMem(PointHolder self){
    if (self->current > self->size - 3){
        self->size *= 2;
        self->list = (float*) realloc(self->list,sizeof(float) * self->size);
    }
}

void addPoint(PointHolder self,float x,float y,float z){
    checkMem(self);
    self->list[self->current] = x;
    self->current++;
    self->list[self->current] = y;
    self->current++;
    self->list[self->current] = z;
    self->current++;
}

void printToFile(PointHolder self,FILE* file){
    //fprintf(file,"%d\n",self->current);
    //for (int i = 0; i <self->current;i += 3){
    //    fprintf(file,"%.6f;%.6f;%.6f\n",self->list[i],self->list[i+1],self->list[i+2]);
    //}

    fwrite(&self->current,sizeof (int),1,file);
    fwrite(self->list,sizeof (float ),self->current,file);
}