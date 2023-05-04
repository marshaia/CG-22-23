//
// Created by vicshadow on 25-02-2023.
//

#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H

#include "../pugixml/pugixml.hpp"
#include "model.h"
#include <list>

using namespace std;
using namespace pugi;


class group {
public:
    //transform functions
    float transX = 0, transY = 0, transZ = 0;
    float rotAngle = 0, rotX = 0,rotY = 0, rotZ = 0;
    float scaleX = 1, scaleY = 1, scaleZ = 1;
    char transformOrder[3] = {'x','x','x'};

    list<model> models;
    list<group> subgroups;

    group(xml_node myNode);

    void loadTransforms(xml_node transformNode);
    void loadModels(xml_node modelsNode);
    void loadSubGroups(xml_node myNode);

    void drawGroup();
};


#endif //ENGINE_GROUP_H
