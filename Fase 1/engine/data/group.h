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
    // transX, transY...
    // rotAngle, rotX....
    // scaleX, scaleY....
    list<model> models;
    list<group> subgroups;

    group(xml_node myNode);
    // void loadTransforms(xml_node transformNode);
    void loadModels(xml_node modelsNode);
    void loadSubGroups(xml_node myNode);

    void drawGroup();
};


#endif //ENGINE_GROUP_H
