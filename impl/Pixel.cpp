//
// Created by Allan Pichardo on 2019-04-01.
//

#include <Pixel.h>
#include <Camera.h>

void Pixel::initialize(const int &resolutionWidth, const int &resolutionHeight, const int &x, const int &y, const Camera *camera) {
    width = camera->getViewWidth()/resolutionWidth;
    height = camera->getViewHeight()/resolutionHeight;
    position = camera->getScreenCorner() +
            (camera->getU() * (float)y * width) +
            (camera->getV() * (float)x * height);

    position.x = position.x + (width/2.0f);
    position.y = position.y + (height/2.0f);
}
