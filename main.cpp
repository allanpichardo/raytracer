#include <iostream>
#include "Scene.h"

int main() {
    Scene scene;
    if(scene.isSceneLoaded()) {
        scene.renderToImage("../output/render.bmp");
    }
}