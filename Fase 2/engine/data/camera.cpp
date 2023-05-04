//
// Created by vicshadow on 25-02-2023.
//

#include "camera.h"

//Default Values
camera::camera(){
    this->posX=5;this->posY=5;this->posZ=5;
    this->lookX=0;this->lookY=0;this->lookZ=0;
    this->upX=0;this->upY=1;this->upZ=0;
    this->fov=60;this->near=1;this->far=1000;
}

void camera::setPosition(float posX,float posY,float posZ){
    this->posX=posX;this->posY=posY;this->posZ=posZ;
}

void camera::setLookAt(float lookX,float lookY,float lookZ){
    this->lookX=lookX;this->lookY=lookY;this->lookZ=lookZ;
}
void camera::setUp(float upX,float upY,float upZ){
    this->upX=upX;this->upY=upY;this->upZ=upZ;
}
void camera::setFov(float fov){
    this->fov=fov;
}
void camera::setNearFar(float near, float far){
    this->near=near;this->far=far;
}
