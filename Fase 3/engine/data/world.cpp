//
// Created by vicshadow on 25-02-2023.
//

#include "world.h"

using namespace pugi;

void world::loadXML(const string& filename) {

    xml_document doc;
    if (!doc.load_file(filename.c_str())) throw std::invalid_argument("Invalid Filename or Invalid XML File");

    xml_node selfNode = doc.child("world");
    this->axis = selfNode.attribute("axis").as_bool(false);

    //Load
    this->loadWindow(selfNode.child("window"));
    this->loadCamera(selfNode.child("camera"));
    for (xml_node node = selfNode.child("group"); node; node = node.next_sibling("group")) {
        this->groups.emplace_back(node);
    }
}

void world::loadWindow(xml_node windowNode){
    this->myWindow.setDims(windowNode.attribute("width").as_int(),windowNode.attribute("height").as_int());
}

void world::loadCamera(xml_node cameraNode){
    //Position
    if(cameraNode.child("position")){
        xml_node pos = cameraNode.child("position");
        this->myCamera.setPosition(pos.attribute("x").as_float(),pos.attribute("y").as_float(),pos.attribute("z").as_float());
    }

    //LookAt
    if(cameraNode.child("lookAt")){
        xml_node lookAt = cameraNode.child("lookAt");
        this->myCamera.setLookAt(lookAt.attribute("x").as_float(),lookAt.attribute("y").as_float(),lookAt.attribute("z").as_float());
    }

    //Up
    if(cameraNode.child("up")){
        xml_node up = cameraNode.child("up");
        this->myCamera.setUp(up.attribute("x").as_float(),up.attribute("y").as_float(),up.attribute("z").as_float());
    }

    //Projection
    if(cameraNode.child("projection")){
        xml_node proj = cameraNode.child("projection");
        this->myCamera.setFov(proj.attribute("fov").as_float());
        this->myCamera.setNearFar(proj.attribute("near").as_float(),proj.attribute("far").as_float());
    }

}


void world::drawAxis(){
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


void world::draw(float elapsedTime) {
    if (axis) drawAxis();
    for (auto &group : groups){
        group.drawGroup(elapsedTime);
    }
}