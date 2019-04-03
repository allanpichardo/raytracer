#include <iostream>
#include "Scene.h"

int main() {
    Scene scene("../scenes/scene5.txt");
    if(scene.isSceneLoaded()) {
        scene.renderToImage("../output/render.bmp");
    }
}