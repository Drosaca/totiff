//
// Created by drosaca on 18/11/22.
//

#ifndef TOTIFF_RAWIMAGE_H
#define TOTIFF_RAWIMAGE_H

#include <string>
#include <vector>

class RawImage {
public:
RawImage(const std::string& filePath);
const std::vector<uint16_t> &getPixels();
private:
std::vector<uint16_t> _pixels;
};


#endif //TOTIFF_RAWIMAGE_H
