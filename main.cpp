#include <iostream>
#include "Scene.h"


void showUsage() {
    std::cerr << "Missing arguments." << std::endl;
    std::cerr << "Usage: raytracer -in [scene file path] -out [image path]" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc == 5) {
        char* infile;
        char* outfile;

        if(strcasecmp(argv[1], "-in") == 0) {
            infile = argv[2];
        }else if(strcasecmp(argv[1], "-out") == 0) {
            outfile = argv[2];
        } else {
            showUsage();
            return 0;
        }

        if(strcasecmp(argv[3], "-in") == 0) {
            infile = argv[4];
        }else if(strcasecmp(argv[3], "-out") == 0) {
            outfile = argv[4];
        } else {
            showUsage();
            return 0;
        }

        try {
            Scene scene(infile);
            if (scene.isSceneLoaded()) {
                scene.renderToImage(outfile);
            }
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else {
        showUsage();
    }
}