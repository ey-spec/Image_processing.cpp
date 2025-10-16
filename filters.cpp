/*
=========================================================
               Image Processing Project
=========================================================

Program Overview:
This C++ program implements a basic image processing system
that allows the user to:
  - Load an image from file
  - Apply a variety of filters:
      • Grayscale
      • Black & White
      • Invert
      • Merge
      • Flip
      • Rotate
      • Darken & Lighten
      • Crop Images
      • Add a Frame
      • Detect Image Edges
      • Resize Images
      • Blur Images
      • Add Natural Sunlight
      • Oil Painting Effect
      • TV Noise
      • Purple Effect
      • Infrared
      • Image Skewing
      • Film
      • Motion Blur
      • Sepia
      • Pencil Sketching

  - Undo last filter
  - Save the processed image
  - Navigate easily using a menu system

Program Structure:
Each filter is implemented in its own function for clarity.
The main function handles user input and overall control flow.

Team Members:
  - Karim Ashraf (ID: 20240419) / S26
      ==> Invert, Rotate, Add Frame, Blur, TV Noise, Skewing ,
          GUI
  - Eyad Hatem (ID: 20240097) / S26
      ==> Grayscale, Merge, Darken & Lighten, Edge Detection,
          Sunlight, Purple Effect , Film , Motion Blur , Sepia ,
          Pencil Sketching , Undo last filter,  Menu System
  - Sherif Ahmed (ID: 20240277) / All-B
      ==> Black & White, Flip, Crop, Resize, Oil Painting, Infrared
Repo link:
  - https://github.com/ey-spec/Image_processing.cpp
Drive link:
  - https://drive.google.com/drive/u/0/folders/154tqApaFqlO04AZ_x_uyCD3uAybApf3T

=========================================================
*/
#include <QColor>
#include <QString>
#include <QWidget>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Image_Class.h"
#include "filters.h"
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;
// filter 1

void Apply_Grayscale_filter(Image &img) {
    int width = img.width;
    int height = img.height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);

            unsigned char gray = (r + g + b) / 3;


            img.setPixel(x, y, 0, gray);
            img.setPixel(x, y, 1, gray);
            img.setPixel(x, y, 2, gray);
        }
    }
}

// filter 2

void Apply_black_white_filter(Image &img) {
    unsigned int threshold = 128;

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k) {
                avg += img(i, j, k);
            }
            avg /= 3;
            unsigned char colour;
            if (avg >= threshold) {
                colour = 255;
            }
            else {
                colour = 0;
            }
            img(i, j, 0) = colour;
            img(i, j, 1) = colour;
            img(i, j, 2) = colour;
        }
    }
}

// filter 3

void Apply_Invert_filter(Image &img){

    for(int i = 0 ; i < img.width ; i++ ){
        for(int j =0 ; j < img.height ; j++){
            unsigned char r = img(i,j,0);
            unsigned char g = img(i,j,1);
            unsigned char b = img(i,j,2);

            img(i, j, 0) = 255-r;
            img(i, j, 1) = 255-g;
            img(i, j, 2) = 255-b;
        }
    }
}

// filter 4

Image resizeImage(const Image &src, int new_W, int new_H) {
    Image resized(new_W, new_H);
    for (int y = 0; y < new_H; y++) {
        for (int x = 0; x < new_W; x++) {
            int srcX = x * src.width / new_W;
            int srcY = y * src.height / new_H;
            for (int c = 0; c < 3; c++) {
                unsigned char val = src.getPixel(srcX, srcY, c);
                resized.setPixel(x, y, c, val);
            }
        }
    }
    return resized;
}

void Apply_Merge_Filter(Image &img1, const Image &img2, MergeOption option ) {
    if (img1.width == img2.width && img1.height == img2.height) {
        // نفس الأبعاد
        for (int y = 0; y < img1.height; y++) {
            for (int x = 0; x < img1.width; x++) {
                for (int c = 0; c < 3; c++) {
                    unsigned char merged = (img1.getPixel(x, y, c) + img2.getPixel(x, y, c)) / 2;
                    img1.setPixel(x, y, c, merged);
                }
            }
        }
        return;
    }

    if (option == ResizeToMatch) {
        int newW = std::max(img1.width, img2.width);
        int newH = std::max(img1.height, img2.height);

        Image resized1 = resizeImage(img1, newW, newH);
        Image resized2 = resizeImage(img2, newW, newH);

        for (int y = 0; y < newH; y++) {
            for (int x = 0; x < newW; x++) {
                for (int c = 0; c < 3; c++) {
                    unsigned char merged = (resized1.getPixel(x, y, c) + resized2.getPixel(x, y, c)) / 2;
                    resized1.setPixel(x, y, c, merged);
                }
            }
        }
        img1 = resized1;
    }
    else if (option == CommonArea) {
        int minW = std::min(img1.width, img2.width);
        int minH = std::min(img1.height, img2.height);

        for (int y = 0; y < minH; y++) {
            for (int x = 0; x < minW; x++) {
                for (int c = 0; c < 3; c++) {
                    unsigned char merged = (img1.getPixel(x, y, c) + img2.getPixel(x, y, c)) / 2;
                    img1.setPixel(x, y, c, merged);
                }
            }
        }
    }
}

// filter 5

void Apply_Flip_Filter(Image &img, FlipType type) {
    Image flipped(img.width, img.height);

    if (type == Horizontal) {
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned char val = img.getPixel(i, j, k);
                    flipped.setPixel(img.width - 1 - i, j, k, val);
                }
            }
        }
    }
    else if (type == Vertical) {
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned char val = img.getPixel(i, j, k);
                    flipped.setPixel(i, img.height - 1 - j, k, val);
                }
            }
        }
    }

    img = flipped;
}

// filter 6

void Apply_Rotate_Filter(Image &img, int angle) {
    Image rotated;

    if (angle == 90) {
        rotated = Image(img.height, img.width);
        for (int x = 0; x < img.width; x++) {
            for (int y = 0; y < img.height; y++) {
                for (int z = 0; z < 3; z++) {
                    rotated.setPixel(y, img.width - 1 - x, z, img.getPixel(x, y, z));
                }
            }
        }
    }
    else if (angle == 180) {
        rotated = Image(img.width, img.height);
        for (int x = 0; x < img.width; x++) {
            for (int y = 0; y < img.height; y++) {
                for (int z = 0; z < 3; z++) {
                    rotated.setPixel(img.width - 1 - x, img.height - 1 - y, z, img.getPixel(x, y, z));
                }
            }
        }
    }
    else if (angle == 270) {
        rotated = Image(img.height, img.width);
        for (int x = 0; x < img.width; x++) {
            for (int y = 0; y < img.height; y++) {
                for (int z = 0; z < 3; z++) {
                    rotated.setPixel(img.height - 1 - y, x, z, img.getPixel(x, y, z));
                }
            }
        }
    }
    else {
        return; // invalid angle, GUI button should prevent this
    }

    img = rotated;
}

// filter 7 (custom percentage)


void Apply_Lighten_Darken_Filter(Image &img, BrightnessType type, double percentage) {
    if (percentage < 0 || percentage > 100) return; // GUI يمكن يمنع خطأ قبل كده
    double factor = percentage / 100.0;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < 3; c++) {
                unsigned char pix = img.getPixel(x, y, c);
                int newValue;
                if (type == Lighten) {
                    newValue = pix + (pix * factor);
                    if (newValue > 255) newValue = 255;
                } else { // Darken
                    newValue = pix - (pix * factor);
                    if (newValue < 0) newValue = 0;
                }
                img.setPixel(x, y, c, (unsigned char)newValue);
            }
        }
    }
}

//filter 8

void Apply_Crop_Filter(Image &img, int startX, int startY, int cropW, int cropH) {
    if (startX < 0 || startY < 0 || startX + cropW > img.width || startY + cropH > img.height)
        return; // GUI ممكن يمنع إدخال خاطئ

    Image cropped(cropW, cropH);
    for (int i = 0; i < cropW; i++) {
        for (int j = 0; j < cropH; j++) {
            for (int c = 0; c < 3; c++) {
                cropped.setPixel(i, j, c, img.getPixel(startX + i, startY + j, c));
            }
        }
    }
    img = cropped;
}


//filter 9
void get_color_from_index(int index, unsigned char &r, unsigned char &g, unsigned char &b) {
    switch(index) {
    case 0: r=0; g=0; b=0; break;       // Black
    case 1: r=255; g=255; b=255; break; // White
    case 2: r=0; g=255; b=0; break;     // Green
    case 3: r=0; g=0; b=255; break;     // Blue
    case 4: r=128; g=0; b=128; break;   // Purple
    case 5: r=255; g=165; b=0; break;   // Orange
    case 6: r=255; g=255; b=0; break;   // Yellow
    case 7: r=255; g=0; b=0; break;     // Red
    case 8: r=255; g=192; b=203; break; // Pink
    case 9: r=165; g=42; b=42; break;   // Brown
    case 10: r=128; g=128; b=128; break;// Gray
    case 11: r=255; g=215; b=0; break;  // Gold
    default: r=0; g=0; b=0; break;      // Black default
    }
}


void draw_Corner_Decorations(Image &img, int thickness, unsigned char r, unsigned char g, unsigned char b) {
    int size = thickness * 2;

    // Top-left
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (x < thickness || y < thickness) {
                img.setPixel(x, y, 0, r);
                img.setPixel(x, y, 1, g);
                img.setPixel(x, y, 2, b);
            }
        }
    }

    // Top-right
    for (int y = 0; y < size; y++) {
        for (int x = img.width - size; x < img.width; x++) {
            if (x > img.width - thickness || y < thickness) {
                img.setPixel(x, y, 0, r);
                img.setPixel(x, y, 1, g);
                img.setPixel(x, y, 2, b);
            }
        }
    }

    // Bottom-left
    for (int y = img.height - size; y < img.height; y++) {
        for (int x = 0; x < size; x++) {
            if (x < thickness || y > img.height - thickness) {
                img.setPixel(x, y, 0, r);
                img.setPixel(x, y, 1, g);
                img.setPixel(x, y, 2, b);
            }
        }
    }

    // Bottom-right
    for (int y = img.height - size; y < img.height; y++) {
        for (int x = img.width - size; x < img.width; x++) {
            if (x > img.width - thickness || y > img.height - thickness) {
                img.setPixel(x, y, 0, r);
                img.setPixel(x, y, 1, g);
                img.setPixel(x, y, 2, b);
            }
        }
    }
}


void Apply_frame_filter(Image &img, int thickness, int style,
                        unsigned char r1, unsigned char g1, unsigned char b1,
                        unsigned char r2, unsigned char g2, unsigned char b2) {
    if (thickness <= 0 || thickness > img.width/2 || thickness > img.height/2)
        return;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            bool isBorder = (y < thickness || y >= img.height - thickness ||
                             x < thickness || x >= img.width - thickness);
            if (!isBorder) continue;

            unsigned char r=0,g=0,b=0;

            if (style == 1) { // Solid
                r=r1; g=g1; b=b1;
            }
            else if (style == 2) { // Gradient
                float t = (float)(x + y) / (img.width + img.height);
                r = (1 - t) * r1 + t * r2;
                g = (1 - t) * g1 + t * g2;
                b = (1 - t) * b1 + t * b2;
            }
            else if (style == 3) { // Striped
                if ((y / 10) % 2 == 0) { r=r1; g=g1; b=b1; }
                else { r=255; g=255; b=255; }
            }
            else if (style == 4) { // Checkered
                if (((x/10) + (y/10)) % 2 == 0) { r=r1; g=g1; b=b1; }
                else { r=255; g=255; b=255; }
            }
            else if (style == 5) { // Decorated
                r=r1; g=g1; b=b1;
            }

            img.setPixel(x, y, 0, r);
            img.setPixel(x, y, 1, g);
            img.setPixel(x, y, 2, b);
        }
    }

    if (style == 5) {
        draw_Corner_Decorations(img, thickness, 255, 255, 255);
    }
}


// filter 10

void Apply_Edge_Detection_Filter(Image &img, int threshold ) {
    Image edgeImage(img.width, img.height);

    for (int y = 0; y < img.height - 1; y++) {
        for (int x = 0; x < img.width - 1; x++) {
            unsigned char r1 = img.getPixel(x, y, 0);
            unsigned char g1 = img.getPixel(x, y, 1);
            unsigned char b1 = img.getPixel(x, y, 2);
            int avg1 = (r1 + g1 + b1) / 3;

            unsigned char r2 = img.getPixel(x + 1, y, 0);
            unsigned char g2 = img.getPixel(x + 1, y, 1);
            unsigned char b2 = img.getPixel(x + 1, y, 2);
            int avg2 = (r2 + g2 + b2) / 3;

            unsigned char r3 = img.getPixel(x, y + 1, 0);
            unsigned char g3 = img.getPixel(x, y + 1, 1);
            unsigned char b3 = img.getPixel(x, y + 1, 2);
            int avg3 = (r3 + g3 + b3) / 3;

            int diff = abs(avg1 - avg2) + abs(avg1 - avg3);
            unsigned char edgeColor = (diff > threshold) ? 0 : 255;

            edgeImage.setPixel(x, y, 0, edgeColor);
            edgeImage.setPixel(x, y, 1, edgeColor);
            edgeImage.setPixel(x, y, 2, edgeColor);
        }
    }

    img = edgeImage;
}

// filter 11

void Apply_Resize_Filter(Image& img, int new_W, int new_H) {
    if (new_W <= 0 || new_H <= 0) {
        return;
    }

    Image resized(new_W, new_H);
    for (int i = 0; i < new_W; i++) {
        for (int j = 0; j < new_H; j++) {
            int srcX = i * img.width / new_W;
            int srcY = j * img.height / new_H;
            for (int c = 0; c < 3; c++) {
                unsigned char val = img.getPixel(srcX, srcY, c);
                resized.setPixel(i, j, c, val);
            }
        }
    }
    img = resized;
}

// filter 12

void Apply_Blur_Filter(Image &img, int strength) {
    if (strength <= 0) {
        // strength غير صالح، ممكن ترجع خطأ للـ GUI بدل cout
        return;
    }

    Image temp = img;  // نسخة مؤقتة لتجنب تأثير القيم المعدلة أثناء المعالجة
    int offset = strength;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            long sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int ky = -offset; ky <= offset; ky++) {
                for (int kx = -offset; kx <= offset; kx++) {
                    int nx = x + kx;
                    int ny = y + ky;

                    if (nx >= 0 && nx < img.width && ny >= 0 && ny < img.height) {
                        sumR += temp.getPixel(nx, ny, 0);
                        sumG += temp.getPixel(nx, ny, 1);
                        sumB += temp.getPixel(nx, ny, 2);
                        count++;
                    }
                }
            }

            unsigned char r = (count > 0) ? (sumR / count) : temp.getPixel(x, y, 0);
            unsigned char g = (count > 0) ? (sumG / count) : temp.getPixel(x, y, 1);
            unsigned char b = (count > 0) ? (sumB / count) : temp.getPixel(x, y, 2);


            img.setPixel(x, y, 0, r);
            img.setPixel(x, y, 1, g);
            img.setPixel(x, y, 2, b);
        }
    }
    // بدل cout ممكن ترجع رسالة للـ GUI لو حبيت
}

// filter 13

void Apply_Sunlight_filter(Image &img) {
    int width = img.width;
    int height = img.height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);

            int newR = r + 50;
            int newG = g + 30;
            int newB = b;

            if (newR > 255) newR = 255;
            if (newG > 255) newG = 255;
            if (newB > 255) newB = 255;

            img.setPixel(x, y, 0, (unsigned char)newR);
            img.setPixel(x, y, 1, (unsigned char)newG);
            img.setPixel(x, y, 2, (unsigned char)newB);
        }
    }
}

// filter 14

void Apply_OilPainting_filter(Image &img) {
    int levels = 20;
    int radius = 4;
    Image result(img.width, img.height);
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int intensityCount[20] = {0};
            int rSum[20] = {0};
            int gSum[20] = {0};
            int bSum[20] = {0};
            for (int ny = -radius; ny <= radius; ny++) {
                for (int nx = -radius; nx <= radius; nx++) {
                    int px = x + nx;
                    int py = y + ny;
                    if (px >= 0 && px < img.width && py >= 0 && py < img.height) {
                        unsigned char r = img.getPixel(px, py, 0);
                        unsigned char g = img.getPixel(px, py, 1);
                        unsigned char b = img.getPixel(px, py, 2);
                        int intensity = ((r + g + b) / 3) * levels / 256;
                        if (intensity >= levels) intensity = levels - 1;
                        intensityCount[intensity]++;
                        rSum[intensity] += r;
                        gSum[intensity] += g;
                        bSum[intensity] += b;
                    }
                }
            }
            int maxIndex = 0;
            for (int i = 1; i < levels; i++) {
                if (intensityCount[i] > intensityCount[maxIndex]) maxIndex = i;
            }
            int count = intensityCount[maxIndex];
            unsigned char newR = (count > 0) ? (rSum[maxIndex] / count) : img.getPixel(x, y, 0);
            unsigned char newG = (count > 0) ? (gSum[maxIndex] / count) : img.getPixel(x, y, 1);
            unsigned char newB = (count > 0) ? (bSum[maxIndex] / count) : img.getPixel(x, y, 2);
            result.setPixel(x, y, 0, newR);
            result.setPixel(x, y, 1, newG);
            result.setPixel(x, y, 2, newB);
        }
    }
    img = result;
}

// filter 15

void Apply_TV_Noise_Filter(Image &img) {
    srand(time(0));

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {

            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);


            unsigned char gray = (r + g + b) / 3;
            r = (r + gray) / 2;
            g = (g + gray) / 2;
            b = (b + gray) / 2;


            int noise = (rand() % 100) - 50;
            int nr = max(0, min(255, r + noise));
            int ng = max(0, min(255, g + noise));
            int nb = max(0, min(255, b + noise));

            if (y % 3 == 0) {
                nr = nr / 2;
                ng = ng / 2;
                nb = nb / 2;
            }

            img.setPixel(x, y, 0, nr);
            img.setPixel(x, y, 1, ng);
            img.setPixel(x, y, 2, nb);
        }
    }
}

// filter 16

void Apply_Purple_filter(Image &img) {

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);

            int newR = r + 50;
            int newG = g * 0.5;
            int newB = b + 70;

            if (newR > 255) newR = 255;
            if (newB > 255) newB = 255;

            img.setPixel(x, y, 0, (unsigned char)newR);
            img.setPixel(x, y, 1, (unsigned char)newG);
            img.setPixel(x, y, 2, (unsigned char)newB);
        }
    }
}

// filter 17

void Apply_Infrared_filter(Image &img) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char R = img(x, y, 0);
            unsigned char G = img(x, y, 1);
            unsigned char B = img(x, y, 2);

            int newR = min(255, (int)(1.4 * R + 0.6 * G));
            int newG = min(255, (int)(0.5 * R + 0.3 * G));
            int newB = min(255, (int)(0.2 * R + 0.2 * G + 0.2 * B));

            img(x, y, 0) = newR;
            img(x, y, 1) = newG;
            img(x, y, 2) = newB;
        }
    }
}

// filter 18

void Apply_Skew_Filter(Image &img, int degree, const std::string &direction) {
    if (degree == 0) return; // لا تغيير إذا الدرجة صفر

    Image temp = img;

    double angle = degree * M_PI / 180.0;
    double shear = tan(angle);

    int maxShift = static_cast<int>(fabs(shear) * img.height);
    int newWidth = img.width + maxShift;

    Image output(newWidth, img.height);

    // ملء الخلفية باللون الأبيض
    for (int y = 0; y < output.height; y++) {
        for (int x = 0; x < output.width; x++) {
            output.setPixel(x, y, 0, 255);
            output.setPixel(x, y, 1, 255);
            output.setPixel(x, y, 2, 255);
        }
    }

    for (int y = 0; y < img.height; y++) {
        int shift = static_cast<int>(shear * y);

        for (int x = 0; x < img.width; x++) {
            int newX;

            if (direction == "right" || direction == "Right") {
                newX = x + shift;
            } else {
                newX = x - shift + maxShift;
            }

            if (newX >= 0 && newX < output.width) {
                output.setPixel(newX, y, 0, temp.getPixel(x, y, 0));
                output.setPixel(newX, y, 1, temp.getPixel(x, y, 1));
                output.setPixel(newX, y, 2, temp.getPixel(x, y, 2));
            }
        }
    }

    img = output;
    // بدل cout يمكن تحديث QLabel أو إرسال إشارة للـ GUI
}

// filter 19

void Apply_Film_Filter(Image &img, int level) {
    int width = img.width;
    int height = img.height;

    float contrastFactor, tintR, tintG, tintB, vignetteStrength;

    if (level == 1) {
        contrastFactor = 1.1f;
        tintR = 1.05f; tintG = 1.0f; tintB = 0.95f;
        vignetteStrength = 0.3f;
    } else if (level == 2) {
        contrastFactor = 1.2f;
        tintR = 1.1f; tintG = 0.95f; tintB = 0.9f;
        vignetteStrength = 0.5f;
    } else {
        contrastFactor = 1.3f;
        tintR = 1.15f; tintG = 0.9f; tintB = 0.85f;
        vignetteStrength = 0.7f;
    }

    float cx = width / 2.0f;
    float cy = height / 2.0f;
    float maxDist = sqrt(cx * cx + cy * cy);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);

            float newR = ((r / 255.0f - 0.5f) * contrastFactor + 0.5f) * 255.0f;
            float newG = ((g / 255.0f - 0.5f) * contrastFactor + 0.5f) * 255.0f;
            float newB = ((b / 255.0f - 0.5f) * contrastFactor + 0.5f) * 255.0f;

            newR *= tintR;
            newG *= tintG;
            newB *= tintB;

            float dx = x - cx;
            float dy = y - cy;
            float dist = sqrt(dx * dx + dy * dy);
            float vignette = 1.0f - vignetteStrength * (dist / maxDist);
            vignette = std::max(0.0f, std::min(1.0f, vignette));

            newR *= vignette;
            newG *= vignette;
            newB *= vignette;

            newR = std::min(255.0f, std::max(0.0f, newR));
            newG = std::min(255.0f, std::max(0.0f, newG));
            newB = std::min(255.0f, std::max(0.0f, newB));

            img.setPixel(x, y, 0, static_cast<unsigned char>(newR));
            img.setPixel(x, y, 1, static_cast<unsigned char>(newG));
            img.setPixel(x, y, 2, static_cast<unsigned char>(newB));
        }
    }

    // بدل cout يمكن إرسال إشارة للـ GUI لتحديث حالة التطبيق
}

// filter 20

void Apply_Motion_Blur_Filter(Image &img, int blurStrength, double angle) {
    int width = img.width;
    int height = img.height;

    if (blurStrength < 1) blurStrength = 1;
    if (blurStrength > 50) blurStrength = 50;

    Image blurred(width, height);

    double rad = angle * M_PI / 180.0;
    double dx = cos(rad);
    double dy = sin(rad);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int k = 0; k < blurStrength; k++) {
                int nx = x + k * dx;
                int ny = y + k * dy;

                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    sumR += img.getPixel(nx, ny, 0);
                    sumG += img.getPixel(nx, ny, 1);
                    sumB += img.getPixel(nx, ny, 2);
                    count++;
                }
            }

            if (count > 0) {
                unsigned char avgR = sumR / count;
                unsigned char avgG = sumG / count;
                unsigned char avgB = sumB / count;

                blurred.setPixel(x, y, 0, avgR);
                blurred.setPixel(x, y, 1, avgG);
                blurred.setPixel(x, y, 2, avgB);
            }
        }
    }

    img = blurred;

    // مفيش cout، يمكن للـ GUI تحديث حالة التطبيق بعد التطبيق
}

// filter 21

void Apply_Sepia_Filter(Image &img) {
    int width = img.width;
    int height = img.height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);

            int newR = (int)(0.393 * r + 0.769 * g + 0.189 * b);
            int newG = (int)(0.349 * r + 0.686 * g + 0.168 * b);
            int newB = (int)(0.272 * r + 0.534 * g + 0.131 * b);

            if (newR > 255) newR = 255;
            if (newG > 255) newG = 255;
            if (newB > 255) newB = 255;

            img.setPixel(x, y, 0, (unsigned char)newR);
            img.setPixel(x, y, 1, (unsigned char)newG);
            img.setPixel(x, y, 2, (unsigned char)newB);
        }
    }
    // لا cout هنا، الواجهة هي اللي هتعرض رسالة
}

// filter 22

void Apply_Pencil_Sketch_Filter(Image &img) {
    int width = img.width;
    int height = img.height;

    Image gray(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);
            unsigned char grayVal = (r + g + b) / 3;
            gray.setPixel(x, y, 0, grayVal);
            gray.setPixel(x, y, 1, grayVal);
            gray.setPixel(x, y, 2, grayVal);
        }
    }

    Image inverted(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char g = gray.getPixel(x, y, 0);
            unsigned char inv = 255 - g;
            inverted.setPixel(x, y, 0, inv);
            inverted.setPixel(x, y, 1, inv);
            inverted.setPixel(x, y, 2, inv);
        }
    }

    Image blurred(width, height);
    int blurSize = 3;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sum = 0;
            int count = 0;
            for (int dy = -blurSize; dy <= blurSize; dy++) {
                for (int dx = -blurSize; dx <= blurSize; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        sum += inverted.getPixel(nx, ny, 0);
                        count++;
                    }
                }
            }
            unsigned char blurredVal = sum / count;
            blurred.setPixel(x, y, 0, blurredVal);
            blurred.setPixel(x, y, 1, blurredVal);
            blurred.setPixel(x, y, 2, blurredVal);
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char g = gray.getPixel(x, y, 0);
            unsigned char bVal = blurred.getPixel(x, y, 0);
            int result = g * 255 / (255 - bVal + 1);
            if (result > 255) result = 255;
            img.setPixel(x, y, 0, result);
            img.setPixel(x, y, 1, result);
            img.setPixel(x, y, 2, result);
        }
    }
}



