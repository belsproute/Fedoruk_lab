#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include <png.h>
#include <vector>
#include <iostream>
#include <fstream>

typedef unsigned char uchar;
using namespace std;

class PngImage
{
    png_bytep  *buffer;
    png_infop   info;
    png_uint_32 width;
    png_uint_32 heigth;

    int  bit_depth;
    int  color_type;
    int  interlace_method;
    int  compression_method;
    int  filter_method;

    bool loaded;
public:
    PngImage();

    bool readImage(char* filename);
    bool writeImage(const char* filename);

    int getBlockCount(int Nv = 2, int Nh = 2);

    std::vector<uchar> getBlock(int index, int Nv = 2, int Nh = 2);
    void setBlock(std::vector<uchar> block, int index, int Nv = 2, int Nh = 2);
};

PngImage::PngImage()
{
}

bool PngImage::readImage(char *filename)
{
    uchar header[8];
    png_structp readStruct;
    FILE *file;

    if ((file = fopen(filename, "rb")) == NULL) {
        std::cerr << "Can't read file " << filename << std::endl;
        return false;
    }

    fread(header, 1, 8, file);

    if (png_sig_cmp(header, 0, 8)) {
        std::cerr << filename << " is not png file" << std::endl;
        fclose(file);
        return false;
    }

    readStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                        NULL,
                                        NULL,
                                        NULL);
    if (!readStruct) {
        fclose(file);
        return false;
    }

    info = png_create_info_struct(readStruct);
    if (!info) {
        png_destroy_read_struct(&readStruct, NULL, NULL);
        fclose(file);
        return false;
    }

    if (setjmp(png_jmpbuf(readStruct))) {
        png_destroy_read_struct(&readStruct, &info, NULL);
        fclose(file);
        return false;
    }

    png_init_io(readStruct, file);
    png_set_sig_bytes(readStruct, 8);
    png_read_png(readStruct, info, PNG_TRANSFORM_IDENTITY, NULL);

    width  = png_get_image_width(readStruct, info);
    heigth = png_get_image_height(readStruct, info);
    png_get_IHDR(readStruct,
                 info,
                 &width,
                 &heigth,
                 &bit_depth,
                 &color_type,
                 &interlace_method,
                 &compression_method,
                 &filter_method);
    if (bit_depth != 8 || color_type != 0) {
        cerr << "Wrong image format" << endl;
        cerr << "color type (support only 0): " << color_type << endl;
        cerr << "bit depth (support only 8): " << bit_depth << endl;
        return false;
    }
    buffer = png_get_rows(readStruct, info);
    loaded = true;

    fclose(file);

    cerr << "Width = " << width << endl;
    cerr << "Heigth = " << heigth << endl;

    return true;
}

bool PngImage::writeImage(const char *filename)
{
    png_structp writeStruct;
    FILE *file;

    if ((file = fopen(filename, "w")) == NULL) {
        cerr << "Can't write to file " << filename << endl;
        return false;
    }

    writeStruct = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                          NULL,
                                          NULL,
                                          NULL);
    if (!writeStruct) {
        fclose(file);
        return false;
    }

    info = png_create_info_struct(writeStruct);
    if (!info) {
        png_destroy_write_struct(&writeStruct, NULL);
        fclose(file);
        return false;
    }

    if (setjmp(png_jmpbuf(writeStruct))) {
        png_destroy_write_struct(&writeStruct, &info);
        fclose(file);
        return false;
    }
    png_set_IHDR(writeStruct,
                 info,
                 width,
                 heigth,
                 bit_depth,
                 color_type,
                 interlace_method,
                 compression_method,
                 filter_method);

    png_set_rows(writeStruct, info, buffer);

    png_init_io(writeStruct, file);
    png_write_png(writeStruct, info, PNG_TRANSFORM_IDENTITY, NULL);

    fclose(file);

    return true;
}

int PngImage::getBlockCount(int Nv, int Nh)
{
    int bCols = width / Nh;
    int bRows = heigth / Nv;

    return bCols * bRows;
}

std::vector<uchar> PngImage::getBlock(int index, int Nv, int Nh)
{
    int bCols = width / Nh;

    unsigned row = (index / bCols) * Nv;
    unsigned col = (index % bCols) * Nh;

    std::vector<uchar> block;
    block.clear();

    if (row >= heigth) {
        return block;
    }
//    std::cerr << row << " " << col << std::endl;
    for (int i = row; i < (row + Nv); i++) {
        for (int j = col; j < (col + Nh); j++) {
            block.push_back(buffer[i][j]);
        }
    }

    return block;
}

void PngImage::setBlock(std::vector<uchar> block, int index, int Nv, int Nh)
{
    int bCols = width / Nh;

    unsigned row = (index / bCols) * Nv;
    unsigned col = (index % bCols) * Nh;

    if (row >= heigth) return;

    for (int i = 0; i < Nv; i++) {
        for (int j = 0; j < Nh; j++) {
            buffer[i + row][j + col] = (block[i * Nv + j] > 0) ? (block[i * Nv + j] < 256) ? block[i * Nv + j] : 255 : 0;
        }
    }
}


#endif // PNGIMAGE_H
