//
// Created by drosaca on 18/11/22.
//

#include "Error.h"
#include "Tif.h"
#include "tiffio.h"

void Tif::setPixels(std::vector<uint16_t> &pixels) {
    this->_pixels = pixels;
}

void Tif::write(const std::string &path) {
    TIFF* tif = TIFFOpen(path.c_str(), "w");
    int BytesPerRow = _width * (_pixelBits / 8);

    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, _width);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, _height);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, _channels);
    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, 1);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, _pixelBits);
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif, _width * 2));
    if(TIFFScanlineSize(tif) != BytesPerRow) {
        throw Error("unexpected Scan length: " + std::to_string(TIFFScanlineSize(tif)) + "expected:" + std::to_string(BytesPerRow));
    }

    for (int row = 0; row < _height; row++)
    {
        if (TIFFWriteScanline(tif, &(_pixels[row * _width]), row, 0) < 0)
            break;
    }
    TIFFClose(tif);
}