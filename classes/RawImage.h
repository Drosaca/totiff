//
// Created by drosaca on 18/11/22.
//

#ifndef TOTIFF_RAWIMAGE_H
#define TOTIFF_RAWIMAGE_H

#include <string>
#include <vector>
#include "expected.h"

enum ImageColor {
    NO=0,
    RED,
    GREEN,
    BLUE
};
enum ImageColorType {
    UNKNOWN = 0,
    RGB,
    MONO,
};
struct Pos2D {
    int x;
    int y;
};

class RawImage {

public:
    RawImage(uint32_t width,uint32_t height) : _height(height), _width(width) {
    };
    void setColorType( ImageColorType type) {
        colorType = type;
        if (type == ImageColorType::RGB) {
            _pixels.reserve(_height * _width * 3);
        }
        if (type == ImageColorType::MONO) {
            _pixels.reserve(_height * _width);
        }
    }
    RawImage(const std::string &filePath, uint32_t width, uint32_t height);
    std::vector<uint16_t> getPixels();
    tl::expected<uint16_t *, bool> getPixel(int x, int y);
    RawImage toRGB();
    uint32_t _height;
    uint32_t _width;
    ImageColorType colorType = ImageColorType::UNKNOWN;

private:

    std::vector<uint16_t> _pixels;

    std::tuple<uint32_t, uint32_t, uint32_t>interpolate(int x, int y,const std::vector<Pos2D> &r, const std::vector<Pos2D> &g, const std::vector<Pos2D> &b);

    std::tuple<uint32_t, uint32_t, uint32_t> colorizePixel(int x, int y);
};


#endif //TOTIFF_RAWIMAGE_H
