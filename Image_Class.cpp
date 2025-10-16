#include "Image_Class.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdexcept>
#include <cstring>
#include <algorithm>

// ------------------------------------------------------------
// Private helpers
// ------------------------------------------------------------
bool Image::isValidFilename(const std::string &filename) {
    const char *extension = strrchr(filename.c_str(), '.');
    if (extension == nullptr) {
        std::cerr << "Invalid filename: " << filename << std::endl;
        return false;
    }
    return true;
}

short Image::getExtensionType(const char *extension) {
    if (strcmp(extension, ".png") == 0) return PNG_TYPE;
    if (strcmp(extension, ".bmp") == 0) return BMP_TYPE;
    if (strcmp(extension, ".tga") == 0) return TGA_TYPE;
    if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0) return JPG_TYPE;
    std::cerr << "Unsupported image format: " << extension << std::endl;
    return UNSUPPORTED_TYPE;
}

// ------------------------------------------------------------
// Constructors / Destructor
// ------------------------------------------------------------
Image::Image() = default;

Image::Image(std::string filename) : filename(filename) {
    loadNewImage(this->filename);
}

Image::Image(int mWidth, int mHeight) {
    width = mWidth;
    height = mHeight;
    channels = 3;
    imageData = (unsigned char *)malloc(width * height * channels);
}

Image::Image(const Image &other) {
    *this = other;
}

Image &Image::operator=(const Image &image) {
    if (this == &image)
        return *this;

    stbi_image_free(this->imageData);
    this->imageData = nullptr;

    width = image.width;
    height = image.height;
    channels = image.channels;
    imageData = (unsigned char *)malloc(width * height * channels);

    std::copy(image.imageData, image.imageData + width * height * channels, this->imageData);
    return *this;
}

Image::~Image() {
    if (imageData != nullptr)
        stbi_image_free(imageData);
}

// ------------------------------------------------------------
// Image IO
// ------------------------------------------------------------
bool Image::loadNewImage(const std::string &filename) {
    if (!isValidFilename(filename))
        throw std::invalid_argument("The file extension does not exist");

    const char *extension = strrchr(filename.c_str(), '.');
    short extensionType = getExtensionType(extension);
    if (extensionType == UNSUPPORTED_TYPE)
        throw std::invalid_argument("Unsupported file format");

    if (imageData != nullptr)
        stbi_image_free(imageData);

    imageData = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);

    if (imageData == nullptr)
        throw std::invalid_argument("Invalid filename, file does not exist");

    return true;
}

bool Image::saveImage(const std::string &outputFilename) {
    if (!isValidFilename(outputFilename))
        throw std::invalid_argument("Invalid output filename");

    const char *extension = strrchr(outputFilename.c_str(), '.');
    short extensionType = getExtensionType(extension);
    if (extensionType == UNSUPPORTED_TYPE)
        throw std::invalid_argument("Unsupported file format");

    if (extensionType == PNG_TYPE)
        stbi_write_png(outputFilename.c_str(), width, height, STBI_rgb, imageData, width * 3);
    else if (extensionType == BMP_TYPE)
        stbi_write_bmp(outputFilename.c_str(), width, height, STBI_rgb, imageData);
    else if (extensionType == TGA_TYPE)
        stbi_write_tga(outputFilename.c_str(), width, height, STBI_rgb, imageData);
    else if (extensionType == JPG_TYPE)
        stbi_write_jpg(outputFilename.c_str(), width, height, STBI_rgb, imageData, 90);

    return true;
}

// ------------------------------------------------------------
// Pixel Access
// ------------------------------------------------------------
unsigned char &Image::getPixel(int x, int y, int c) {
    return imageData[(y * width + x) * channels + c];
}

const unsigned char &Image::getPixel(int x, int y, int c) const {
    return imageData[(y * width + x) * channels + c];
}

void Image::setPixel(int x, int y, int c, unsigned char value) {
    imageData[(y * width + x) * channels + c] = value;
}

unsigned char &Image::operator()(int row, int col, int channel) {
    return getPixel(row, col, channel);
}

const unsigned char &Image::operator()(int row, int col, int channel) const {
    return getPixel(row, col, channel);
}
