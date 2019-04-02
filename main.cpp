#include <iostream>
#include "Scene.h"

int main() {
    Scene scene("../scenes/scene3.txt");
    if(scene.isSceneLoaded()) {
        scene.renderToImage("../output/render.bmp");
    }
}