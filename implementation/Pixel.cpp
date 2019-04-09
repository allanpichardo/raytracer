/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#include <Pixel.h>
#include <Camera.h>

void Pixel::initialize(const int &resolutionWidth, const int &resolutionHeight, const int &x, const int &y, const Camera *camera) {
    width = camera->getViewWidth()/resolutionWidth;
    height = camera->getViewHeight()/resolutionHeight;
    position = camera->getScreenCorner() +
            (camera->getU() * (float)x * width) -
            (camera->getV() * (float)y * height);

    position.x = position.x + (width/2.0f);
    position.y = position.y + (height/2.0f);
}
