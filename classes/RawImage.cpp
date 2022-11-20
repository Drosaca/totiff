//
// Created by drosaca on 18/11/22.
//
#include <fstream>
#include "Error.h"
#include "RawImage.h"

RawImage::RawImage(const std::string& filePath) {
    std::vector<unsigned char> bytes(2);
    std::ifstream file(filePath, std::ios::binary);
    if(!file) {
        throw Error("Fail to open image");
    }

    while (file.read(reinterpret_cast<char *>(bytes.data()), 2)) {
        int pixel = ((bytes[1] << 4) + (bytes[0]>>4));
        if (pixel > 4096) {
            throw Error("Unexpected pixel value" + std::to_string(pixel));
        }
        this->_pixels.emplace_back(pixel * 16);
    }
}

const std::vector<uint16_t> &RawImage::getPixels() {
    return this->_pixels;
}


