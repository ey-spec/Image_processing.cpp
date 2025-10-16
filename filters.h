#ifndef FILTERS_H
#define FILTERS_H

#include "Image_Class.h"
#include <string>

// Enums
enum MergeOption {
    ResizeToMatch = 1,
    CommonArea = 2
};

enum FlipType {
    Horizontal = 1,
    Vertical = 2
};

enum BrightnessType {
    Lighten = 1,
    Darken = 2
};

// Filter function declarations
void Apply_Grayscale_filter(Image &img);
void Apply_black_white_filter(Image &img);
void Apply_Invert_filter(Image &img);
void Apply_Merge_Filter(Image &img1, const Image &img2, MergeOption option = CommonArea);
void Apply_Flip_Filter(Image &img, FlipType type);
void Apply_Rotate_Filter(Image &img, int angle);
void Apply_Lighten_Darken_Filter(Image &img, BrightnessType type, double percentage);
void Apply_Crop_Filter(Image &img, int startX, int startY, int cropW, int cropH);
void get_color_from_index(int index, unsigned char &r, unsigned char &g, unsigned char &b);
void draw_Corner_Decorations(Image &img, int thickness, unsigned char r, unsigned char g, unsigned char b);
void Apply_frame_filter(Image &img, int thickness, int style,
                        unsigned char r1, unsigned char g1, unsigned char b1,
                        unsigned char r2=0, unsigned char g2=0, unsigned char b2=0);
void Apply_Edge_Detection_Filter(Image &img, int threshold = 45);
void Apply_Resize_Filter(Image& img, int new_W, int new_H);
void Apply_Blur_Filter(Image &img, int strength);
void Apply_Sunlight_filter(Image &img);
void Apply_OilPainting_filter(Image &img);
void Apply_TV_Noise_Filter(Image &img);
void Apply_Purple_filter(Image &img);
void Apply_Infrared_filter(Image &img);
void Apply_Skew_Filter(Image &img, int degree, const std::string &direction);
void Apply_Film_Filter(Image &img, int level);
void Apply_Motion_Blur_Filter(Image &img, int blurStrength, double angle);
void Apply_Sepia_Filter(Image &img);
void Apply_Pencil_Sketch_Filter(Image &img);

#endif // FILTERS_H
