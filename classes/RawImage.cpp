//
// Created by drosaca on 18/11/22.
//
#include <fstream>
#include "Error.h"
#include "RawImage.h"

RawImage::RawImage(const std::string &filePath, uint32_t width, uint32_t height) {
    std::vector<unsigned char> bytes(2);
    colorType = ImageColorType::MONO;
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw Error("Fail to open image: " + filePath);
    }

    while (file.read(reinterpret_cast<char *>(bytes.data()), 2)) {
        int pixel = ((bytes[1] << 4) + (bytes[0] >> 4));
        if (pixel > 4096) {
            throw Error("Unexpected pixel value" + std::to_string(pixel));
        }
        this->_pixels.emplace_back(pixel * 16);
    }
    _height = height;
    _width = width;

}

std::vector<uint16_t> RawImage::getPixels() {
    return this->_pixels;
}


std::tuple<uint32_t, uint32_t, uint32_t>
RawImage::interpolate(int x, int y, const std::vector<Pos2D> &r, const std::vector<Pos2D> &g, const std::vector<Pos2D> &b) {
    uint32_t red = 0;
    uint32_t blue = 0;
    uint32_t green = 0;
    int counter = 0;
    for (auto redPos: r) {
        auto pix = getPixel(x + redPos.x, y + redPos.y);
        if (!pix)
            continue;
        red += *pix.value();
        counter++;
    }
    red /= counter;
    counter = 0;
    for (auto greenPos: g) {
        auto pix = getPixel(x + greenPos.x,y + greenPos.y);
        if (!pix)
            continue;
        green += *pix.value();
        counter++;
    }
    green /= counter;
    counter = 0;
    for (auto bluePos: b) {
        auto pix = getPixel(x + bluePos.x, y + bluePos.y);
        if (!pix)
            continue;
        blue += *pix.value();
        counter++;
    }
    blue /= counter;
    /*if (r.size() == 1) {
        return {red, 0, 0};
    }
    if (g.size() == 1) {
        return {0, green, 0};

    }
    if (b.size() == 1) {
        return {0, 0, blue};

    }*/
    return {red, green, blue};
}

std::vector<std::vector<Pos2D>> BlueOps = {
        {{-1, -1}, {-1, +1}, {+1, +1}, {+1, -1},},
        {{+1, 0},  {-1, 0},  {0,  +1}, {0,  -1},},
        {{0,  0}}
};

std::vector<std::vector<Pos2D>> RedOps = {
        {{0,  0}},
        {{+1, 0},  {-1, 0},  {0,  +1}, {0,  -1},},
        {{-1, -1}, {+1, +1}, {-1, +1}, {+1, -1},}
};
std::vector<std::vector<Pos2D>> EvenGreenOps = {
        {{+1, 0},{-1, 0},},
        {{0,  0}},
        {{0,  +1},{0,  -1},}
};
std::vector<std::vector<Pos2D>> OddGreenOps = {
        {{0, +1},{0, -1},},
        {{0, 0}},
        {{+1, 0},{-1, 0},}
};

std::tuple<uint32_t, uint32_t, uint32_t> RawImage::colorizePixel(int x, int y) {
    if (y % 2 != 0 && x % 2 == 0) {
        return interpolate(x,y,BlueOps[0], BlueOps[1], BlueOps[2]);
    }
    if (y % 2 == 0 && x % 2 != 0) {
        return interpolate(x,y,RedOps[0], RedOps[1], RedOps[2]);
    }
    if (y % 2 == 0 && x % 2 == 0) {
        return interpolate(x,y,EvenGreenOps[0], EvenGreenOps[1], EvenGreenOps[2]);
    }
    if (y % 2 != 0 && x % 2 != 0) {
        return interpolate(x,y,OddGreenOps[0], OddGreenOps[1], OddGreenOps[2]);
    }

    throw (Error("Unhandled pixel"));
}


RawImage RawImage::toRGB() {
    RawImage rgb(this->_width, this->_height);
    rgb.setColorType(ImageColorType::RGB);
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            auto [red, green, blue] = colorizePixel(x, y);
            rgb._pixels.push_back(red);
            rgb._pixels.push_back(green);
            rgb._pixels.push_back(blue);

        }
    }
    return rgb;
}


tl::expected<uint16_t *, bool> RawImage::getPixel(int x, int y) {
    uint32_t pos = y * _width + x;
    if (pos >= _pixels.size() || x < 0 || y < 0)
        return tl::make_unexpected(false);
    uint16_t *pix = &_pixels[y * _width + x];
    return pix;
}


