//
// Created by vicshadow on 25-02-2023.
//

#include "window.h"

//Default Values
window::window() {
    this->width = 512;
    this->height = 512;
}

void window::setDims(int width, int height) {
    this->width = width;
    this->height = height;
}
