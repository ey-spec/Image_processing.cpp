/**
 * @File  : Image_Class.h
 * @brief : Declaration of the Image class (for loading, saving, and manipulating images)
 * @authors :
 *           Shehab Diab, Youssef Mohamed, Nada Ahmed
 *           Dr. Mohamed El-Ramely
 * @version   : v2.0 (Refactored to avoid multiple definitions)
 * @date      : 27/3/2024
 */

#ifndef _IMAGE_CLASS_H
#define _IMAGE_CLASS_H

#define ll long long
#define PNG_TYPE 1
#define BMP_TYPE 2
#define TGA_TYPE 3
#define JPG_TYPE 4
#define UNSUPPORTED_TYPE -1
using pixel = unsigned int;

#include <iostream>
#include <exception>
#include <string>
#include <cstring>

#include "stb_image.h"
#include "stb_image_write.h"

/**
 * @class Image
 * @brief Represents an image with functionalities for loading, saving, and manipulating pixels.
 */
class Image {
private:
    std::string filename; ///< Image filename

    bool isValidFilename(const std::string &filename);
    short getExtensionType(const char *extension);

public:
    int width = 0;      ///< Image width
    int height = 0;     ///< Image height
    int channels = 3;   ///< Number of color channels
    unsigned char *imageData = nullptr; ///< Raw image data

    // Constructors
    Image();
    Image(std::string filename);
    Image(int mWidth, int mHeight);
    Image(const Image &other);

    // Operators
    Image &operator=(const Image &image);

    // Destructor
    ~Image();

    // Methods
    bool loadNewImage(const std::string &filename);
    bool saveImage(const std::string &outputFilename);

    unsigned char &getPixel(int x, int y, int c);
    const unsigned char &getPixel(int x, int y, int c) const;

    void setPixel(int x, int y, int c, unsigned char value);

    // Operator() overloads for pixel access
    unsigned char &operator()(int row, int col, int channel);
    const unsigned char &operator()(int row, int col, int channel) const;
};

#endif // _IMAGE_CLASS_H
