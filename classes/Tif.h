//
// Created by drosaca on 18/11/22.
//

#ifndef TOTIFF_TIF_H
#define TOTIFF_TIF_H


#include <string>
#include <vector>

class Tif {
public:
    Tif(unsigned int width, unsigned int height): _width(width), _height(height){};
    void write(const std::string &path);
    void setPixels(std::vector<uint16_t>&pixels);
private:
    unsigned int _height;
    unsigned int _width;
    int _pixelBits = 16;
    int _channels = 1;
    std::vector<uint16_t> _pixels;


};


#endif //TOTIFF_TIF_H
