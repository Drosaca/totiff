#include "functions.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        std::cout << "usage totiff path/to/img.ims_rgb width height [--rgb]" << std::endl;
        exit(0);
    }
    bool rgb = argc > 4 && std::string(argv[4]) == "--rgb";
    run(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), rgb);
}
