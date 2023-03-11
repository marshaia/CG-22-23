//
// Created by vicshadow on 25-02-2023.
//

#include "group.h"

group::group(xml_node myNode){
    this->loadModels(myNode.child("models"));
    this->loadSubGroups(myNode);
}

// void group::loadTransforms(xml_node transformNode);

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
    //APPLY TRANSFORMS
    for (auto it = models.begin(); it != models.end(); ++it){
        it->drawModel();
    }
}
