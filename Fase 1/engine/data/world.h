//
// Created by vicshadow on 25-02-2023.
//

#ifndef ENGINE_WORLD_H
#define ENGINE_WORLD_H

#include "model.h"
#include "group.h"
#include "camera.h"
#include "window.h"
#include "../pugixml/pugixml.hpp"

#include <iostream>
#include <list>

using namespace std;
using namespace pugi;

class world {
public:
    window myWindow;
    camera myCamera;
    list<group> groups;

    void loadXML(string filename);
    void draw();

private:
    void loadWindow(xml_node windowNode);
    void loadCamera(xml_node cameraNode);
};

#endif //ENGINE_WORLD_H
