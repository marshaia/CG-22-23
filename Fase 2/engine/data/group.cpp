//
// Created by vicshadow on 25-02-2023.
//

#include <cstring>
#include "group.h"

group::group(xml_node myNode){
    this->loadTransforms(myNode.child("transform"));
    this->loadModels(myNode.child("models"));
    this->loadSubGroups(myNode);
}

void group::loadTransforms(xml_node transformNode) {

    int currOrder = 0;
    for(xml_node node = transformNode.first_child(); node; node = node.next_sibling()){

        if(currOrder >= 3) break;

        //Translate
        if (!strcmp(node.name(),"translate")){
            this->transX = node.attribute("x").as_float();
            this->transY = node.attribute("y").as_float();
            this->transZ = node.attribute("z").as_float();
            this->transformOrder[currOrder] = 't';
            currOrder++;
        }

        //Rotate
        else if(!strcmp(node.name(),"rotate")){
            this->rotAngle = node.attribute("angle").as_float();
            this->rotX = node.attribute("x").as_float();
            this->rotY = node.attribute("y").as_float();
            this->rotZ = node.attribute("z").as_float();
            this->transformOrder[currOrder] = 'r';
            currOrder++;
        }

        //Scale
        else if(!strcmp(node.name(),"scale")){
            this->scaleX = node.attribute("x").as_float();
            if(this->scaleX == 0) this->scaleX = 1;
            this->scaleY = node.attribute("y").as_float();
            if(this->scaleY == 0) this->scaleY = 1;
            this->scaleZ = node.attribute("z").as_float();
            if(this->scaleZ == 0) this->scaleZ = 1;
            this->transformOrder[currOrder] = 's';
            currOrder++;
        }

    }
}

void group::loadModels(xml_node modelsNode){
    for(xml_node node = modelsNode.child("model"); node; node = node.next_sibling("model")){
        string name = node.attribute("file").as_string();
        try{
            this->models.push_back(model(name));
        }catch (int error){
            ::printf("Error while loading model %s\n",name.c_str());
        }

    }
}

void group::loadSubGroups(xml_node myNode){
    for(xml_node node = myNode.child("group"); node; node = node.next_sibling("group")){
        this->subgroups.push_back(group(node));
    }
}

void group::drawGroup() {
    glPushMatrix();

    for(int i = 0; i < 3; i++){
        if (this->transformOrder[i] == 't') glTranslatef(this->transX,this->transY,this->transZ);
        else if (this->transformOrder[i] == 'r') glRotatef(this->rotAngle,this->rotX,this->rotY,this->rotZ);
        else if (this->transformOrder[i] == 's') glScalef(this->scaleX,this->scaleY,this->scaleZ);
        else break;
    }

    for (auto it = models.begin(); it != models.end(); ++it){
        it->drawModel();
    }

    for (auto it = subgroups.begin(); it != subgroups.end(); ++it){
        it->drawGroup();
    }

    glPopMatrix();
}
