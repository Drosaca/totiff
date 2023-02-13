//
// Created by drosaca on 18/11/22.
//

#include "Error.h"
#include "Tif.h"

#include <utility>
#include "tiffio.h"

void Tif::setPixels(std::vector<uint16_t> pixels) {
    this->_pixels = std::move(pixels);
}

void Tif::write(const std::string &path) {
    TIFF* tif = TIFFOpen(path.c_str(), "w");
    uint32_t BytesPerRow = _width *  _channels * (_pixelBits / 8);

    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, _width);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, _height);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, _channels);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, _pixelBits);
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    if(colorType == ImageColorType::RGB) {
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
    } else {
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    }
    if(TIFFScanlineSize(tif) != BytesPerRow) {
        throw Error("unexpected Scan length: " + std::to_string(TIFFScanlineSize(tif)) + "expected:" + std::to_string(BytesPerRow));
    }
    for (int row = 0; row < _height; row++)
    {
        if (TIFFWriteScanline(tif, &(_pixels[row * _width * _channels]), row, 0) < 0) {
            std::cout << "Fail to write row " <<row <<std::endl;
            break;
        }
    }
    TIFFClose(tif);
}

void Tif::fromRaw(RawImage raw) {
    _width = raw._width;
    _height = raw._height;
    setPixels(raw.getPixels());
    colorType =  raw.colorType;
    if (raw.colorType == ImageColorType::RGB) {
        _channels = 3;
    }
}

Tif::Tif() {

}
