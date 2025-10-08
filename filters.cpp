/*
=============================================
Project: Image processing (filters)

File Explanation:
   This C++ file implements a simple image processing program.
   The program allows the user to:
     - Load an image from file
     - Apply filters (Grayscale, Black & White, Invert, Merge, Flip, Rotate)
     - Save the processed image
     - Display a menu to choose options until the user exits

   Each filter is implemented in a separate function for clarity.
   The main function handles user input.

Team Members:
  - Karim Ashraf (ID: 20240419) : Invert + Rotate
  - Eyad Hatem (ID: 20240097) : Grayscale + Merge
  - Sherif Ahmed  (ID: 20240277): Black & White + Flip
=============================================
*/




#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Image_Class.h"
using namespace std;
void Display_Menu() {
    cout << "\n==== Image Processing Menu ====\n";
    cout << "1. Load New Image\n";
    cout << "2. Apply Grayscale Filter\n";
    cout << "3. Apply Black & White Filter\n";
    cout << "4. Apply Invert Filter\n";
    cout << "5. Merge Two Images\n";
    cout << "6. Flip Image\n";
    cout << "7. Rotate Image\n";
    cout << "8. Darken and Lighten Image\n";
    cout << "9. Crop Images\n";
    cout << "10. Adding a Frame to the Picture\n"; //
    cout << "11. Detect Image Edges\n";
    cout << "12. Resizing Images\n";
    cout << "13. Blur Images\n"; //
    cout << "14. Apply Natural Sunlight filter\n";
    cout << "15. Apply Oil painting filter\n";
    cout << "16. Apply TV noise Filter\n"; //
    cout << "17. Purple Image\n";
    cout << "18. Infrared Image\n";
    cout << "19. Image skewing\n"; //
    cout << "20. Save Current Image\n";
    cout << "21. Exit\n";
    cout << "Choose option: "<<"\n";
}

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
    cout << "[Grayscale filter is applied]\n";
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
    cout << "[Black & White filter is applied]\n";
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
    cout << "[Invert filter is applied]\n";
}

// Resize image

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

// filter 4

void Apply_Merge_filter(Image &img) {
    string filename2;
    cout << "Enter the filename of the second image: ";
    cin >> filename2;

    try {
        Image img2;
        img2.loadNewImage(filename2);
        if (img.width == img2.width && img.height == img2.height) {
            for (int y = 0; y < img.height; y++) {
                for (int x = 0; x < img.width; x++) {
                    for (int c = 0; c < 3; c++) {
                        unsigned char p1 = img.getPixel(x, y, c);
                        unsigned char p2 = img2.getPixel(x, y, c);
                        unsigned char merged = (p1 + p2) / 2;
                        img.setPixel(x, y, c, merged);
                    }
                }
            }
            cout << "[Merge filter applied successfully (same size)]\n";
            return;
        }
        cout << "The two images have different sizes.\n";
        cout << "Choose merge option:\n";
        cout << "1. Resize smaller image to match the bigger\n";
        cout << "2. Merge only the common area\n";
        int opt; cin >> opt;

        if (opt == 1) {
            int newW = max(img.width, img2.width);
            int newH = max(img.height, img2.height);

            Image resized1 = resizeImage(img, newW, newH);
            Image resized2 = resizeImage(img2, newW, newH);

            for (int y = 0; y < newH; y++) {
                for (int x = 0; x < newW; x++) {
                    for (int c = 0; c < 3; c++) {
                        unsigned char p1 = resized1.getPixel(x, y, c);
                        unsigned char p2 = resized2.getPixel(x, y, c);
                        unsigned char merged = (p1 + p2) / 2;
                        resized1.setPixel(x, y, c, merged);
                    }
                }
            }

            img = resized1;
            cout << "[Merge filter applied with resize]\n";
        }
        else if (opt == 2) {
            int minW = min(img.width, img2.width);
            int minH = min(img.height, img2.height);

            for (int y = 0; y < minH; y++) {
                for (int x = 0; x < minW; x++) {
                    for (int c = 0; c < 3; c++) {
                        unsigned char p1 = img.getPixel(x, y, c);
                        unsigned char p2 = img2.getPixel(x, y, c);
                        unsigned char merged = (p1 + p2) / 2;
                        img.setPixel(x, y, c, merged);
                    }
                }
            }
            cout << "[Merge filter applied on common area]\n";
        }
        else {
            cout << "Invalid option. Merge canceled.\n";
        }

    } catch (exception &e) {
        cerr << "Error loading second image: " << e.what() << endl;
    }
}

// filter 5

void Apply_Flip_filter(Image &img) {
    cout << "Choose flip type:\n";
    cout << "1 - Horizontal Flip (Left Right)\n";
    cout << "2 - Vertical Flip (Top Bottom)\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    Image flipped_pic(img.width, img.height);
    if (choice == 1) { // Horizontal flip
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned char val = img.getPixel(i, j, k);
                    flipped_pic.setPixel(img.width - 1 - i, j, k, val);
                }
            }
        }
    }
    else if (choice == 2) { // Vertical flip
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned char val = img.getPixel(i, j, k);
                    flipped_pic.setPixel(i, img.height - 1 - j, k, val);
                }
            }
        }
    }
    else {
        cout << "Invalid choice. Flip canceled.\n";
        return;
    }
    img = flipped_pic;
    cout << "[Flip filter is applied]\n";
}

// filter 6

void Apply_rotate_filter(Image &img, int angle){

    int width = img.width;
    int height = img.height;
    Image rotated_image;

    if (angle == 90){
        rotated_image = Image(height,width);
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                for(int z = 0; z < 3; z++){
                    rotated_image (y, width - 1 - x, z) = img (x, y, z);
                }
            }
        }
    }


    else if (angle == 180) {
        rotated_image = Image(width, height);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                for (int z = 0; z < 3; z++) {
                    rotated_image (width - 1 - x, height - 1 - y, z) = img(x, y, z);
                }
            }
        }
    }
    else if (angle == 270) {
        rotated_image = Image(height, width);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                for (int z = 0; z < 3; z++) {
                    rotated_image(height - 1 - y, x, z) = img(x, y, z);
                }
            }
        }
    }
    else {
        cout << "Invalid angle, please use 90, 180, or 270." << "\n";
        return;
    }

    img = rotated_image;
    cout << "[Rotate filter is applied]\n";
}

// filter 7 (custom percentage)

void Apply_Lighten_Darken_filter(Image &img) {
    cout << "Choose an option:\n";
    cout << "1 - Lighten Image (make brighter)\n";
    cout << "2 - Darken Image (make darker)\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    double percentage;
    cout << "Enter percentage (0 - 100): ";
    cin >> percentage;

    if (percentage < 0 || percentage > 100) {
        cout << "Invalid percentage. Must be between 0 and 100.\n";
        return;
    }

    double factor = percentage / 100.0;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < 3; c++) {
                unsigned char pix = img.getPixel(x, y, c);
                int newValue;
                if (choice == 1) { // Lighten
                    newValue = pix + (pix * factor);
                    if (newValue > 255) newValue = 255;
                } else if (choice == 2) { // Darken
                    newValue = pix - (pix * factor);
                    if (newValue < 0) newValue = 0;
                } else {
                    cout << "Invalid choice. No changes made.\n";
                    return;
                }
                img.setPixel(x, y, c, (unsigned char)newValue);
            }
        }
    }

    if (choice == 1)
        cout << "[Lighten filter applied by " << percentage << "%]\n";
    else if (choice == 2)
        cout << "[Darken filter applied by " << percentage << "%]\n";
}

//filter 8 

void Apply_Crop_filter(Image& img) {
    int x, y, W, H;
    cout << "Enter starting point (x y): ";
    cin >> x >> y;
    cout << "Enter width (W) and height (H) for cropping: ";
    cin >> W >> H;

    if (x < 0 || y < 0 || x + W > img.width || y + H > img.height) {
        cout << "the Crop dimensions are out of the image's boundaries.\n";
        return;
    }
    Image cropped(W, H);
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            for (int c = 0; c < 3; c++) {
                unsigned char val = img.getPixel(x + i, y + j, c);
                cropped.setPixel(i, j, c, val);
            }
        }
    }
    img = cropped;
    cout << "[Crop filter applied successfully]\n";
}

// a function that take colors from user and apply it 

void get_colors_from_user(int choice, unsigned char &r, unsigned char &g, unsigned char &b) {
    if (choice == 1) { r=0; g=0; b=0; }             // Black
    else if (choice == 2) { r=255; g=255; b=255; }  // White
    else if (choice == 3) { r=0; g=255; b=0; }      // Green
    else if (choice == 4) { r=0; g=0; b=255; }      // Blue
    else if (choice == 5) { r=128; g=0; b=128; }    // Purple
    else if (choice == 6) { r=255; g=165; b=0; }    // Orange
    else if (choice == 7) { r=255; g=255; b=0; }    // Yellow
    else if (choice == 8) { r=255; g=0; b=0; }      // Red
    else if (choice == 9) { r=255; g=192; b=203; }  // Pink
    else if (choice == 10) { r=165; g=42; b=42; }   // Brown
    else if (choice == 11) { r=128; g=128; b=128; } // Gray
    else if (choice == 12) { r=255; g=215; b=0; }   // Gold
    else { r=0; g=0; b=0; }                         // Default Black
}

// Corner decorations

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


// Filter 9
void Apply_frame_filter(Image &img) {
    int thickness, colorChoice, style;
    unsigned char r1,g1,b1,r2,g2,b2;

    cout << "Enter frame thickness: ";
    cin >> thickness;

    cout << "Choose frame style:\n";
    cout << "1. Solid color\n";
    cout << "2. Gradient (between two colors)\n";
    cout << "3. Striped (horizontal stripes)\n";
    cout << "4. Checkered (chess pattern)\n";
    cout << "5. Decorated Frame (with corners)\n";
    cin >> style;

    if (style == 1 || style == 3 || style == 4 || style == 5) {
        cout << "Choose color:\n"
             << "1. Black   2. White   3. Green\n"
             << "4. Blue    5. Purple  6. Orange\n"
             << "7. Yellow  8. Red     9. Pink\n"
             << "10. Brown  11. Gray   12. Gold\n";

        cin >> colorChoice;
        get_colors_from_user(colorChoice, r1, g1, b1);
    }
    else if (style == 2) { // Gradient
        cout << "Choose first color:\n";
        cin >> colorChoice;
        get_colors_from_user(colorChoice, r1, g1, b1);

        cout << "Choose second color:\n";
        cin >> colorChoice;
        get_colors_from_user(colorChoice, r2, g2, b2);
    }

    if (thickness <= 0 || thickness > img.width/2 || thickness > img.height/2) {
        cout << "Invalid thickness value!\n";
        return;
    }

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
            else if (style == 5) { // Decorated (base frame first)
                r=r1; g=g1; b=b1;
            }

            img.setPixel(x, y, 0, r);
            img.setPixel(x, y, 1, g);
            img.setPixel(x, y, 2, b);
        }
    }

    if (style == 5) {
        draw_Corner_Decorations(img, thickness, 255, 255, 255); // زخرفة بالأبيض
    }
}



// filter 10

void Apply_Edge_Detection_filter(Image &img) {
    Image edgeImage(img.width, img.height);

    int threshold = 30;

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

            unsigned char edgeColor = (diff > threshold) ? 255 : 0;

            edgeImage.setPixel(x, y, 0, edgeColor);
            edgeImage.setPixel(x, y, 1, edgeColor);
            edgeImage.setPixel(x, y, 2, edgeColor);
        }
    }

    img = edgeImage;
    cout << "[Edge Detection filter applied successfully]\n";
}

// filter 11 

void Apply_Resize_filter(Image& img) {
    int new_W, new_H;
    cout << "Enter new width and height: ";
    cin >> new_W >> new_H;

    if (new_W <= 0 || new_H <= 0) {
        cout << "Invalid dimensions.\n";
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
    cout << "[Resize filter applied successfully]\n";
}



// filter 12

void Apply_Blur_Filter(Image &img) {
    int strength;
    cout << "Enter blur strength (1 (light) , 5 (mid) , 10 (heavy) ): ";
    cin >> strength;

    if (strength <= 0) {
        cout << "Invalid strength!\n";
        return;
    }

    Image temp = img;

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

            unsigned char r = sumR / count;
            unsigned char g = sumG / count;
            unsigned char b = sumB / count;

            img.setPixel(x, y, 0, r);
            img.setPixel(x, y, 1, g);
            img.setPixel(x, y, 2, b);
        }
    }
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

    cout << "[Sunlight filter applied]\n";
}




// Filter 15
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

    cout << "[Purple filter applied]\n";
}


// Filter 18
void Apply_Skew_Filter(Image &img) {
    int degree;
    char direction;

    cout << "Enter skew degree: ";
    cin >> degree;

    cout << "Choose direction (R = right, L = left): ";
    cin >> direction;

    if (degree == 0) {
        cout << "No skew applied.\n";
        return;
    }

    Image temp = img;

    double angle = degree * M_PI / 180.0;
    double shear = tan(angle);

    // حساب أقصى إزاحة
    int maxShift = (int)(fabs(shear) * img.height);
    int newWidth = img.width + maxShift;

    Image output(newWidth, img.height);

    // خلفية بيضاء
    for (int y = 0; y < output.height; y++) {
        for (int x = 0; x < output.width; x++) {
            output.setPixel(x, y, 0, 255);
            output.setPixel(x, y, 1, 255);
            output.setPixel(x, y, 2, 255);
        }
    }

    // skew يمين أو شمال
    for (int y = 0; y < img.height; y++) {
        int shift = (int)(shear * y);

        for (int x = 0; x < img.width; x++) {
            int newX;

            if (direction == 'R' || direction == 'r') {
                // skew يمين
                newX = x + shift;
            } else {
                // skew شمال
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
}


int main() {
    Image img;
    bool loaded = false;
    bool modified = false;
    int choice;

    // Load first image
    while (!loaded) {
        string filename;
        cout << "Enter the image filename to start: ";
        cin >> filename;
        try {
            img.loadNewImage(filename);
            loaded = true;
            cout << "Image loaded successfully.\n";
        } catch (exception &e) {
            cerr << "Error: " << e.what() << "\nTry again.\n";
        }
    }

    // Menu
    while (true) {
        Display_Menu();
        cin >> choice;

        if (choice == 1) { // Load new image
            if (modified) {
                cout << "Do you want to save the current image before loading new one? (y/n): ";
                char ans; cin >> ans;
                if (ans == 'y' || ans == 'Y') {
                    string out;
                    cout << "Enter filename to save: ";
                    cin >> out;
                    img.saveImage(out);
                    cout << "Image saved.\n";
                }
            }
            string filename;
            cout << "Enter new image filename: ";
            cin >> filename;
            try {
                img.loadNewImage(filename);
                modified = false;
                cout << "New image loaded successfully.\n";
            } catch (exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 2) {
            Apply_Grayscale_filter(img);
            modified = true;
        }
        else if (choice == 3) {
            Apply_black_white_filter(img);
            modified = true;
        }
        else if (choice == 4) {
            Apply_Invert_filter(img);
            modified = true;
        }
        else if (choice == 5) {
            Apply_Merge_filter(img);
            modified = true;
        }
        else if (choice == 6) {
            Apply_Flip_filter(img);
            modified = true;
        }
        else if (choice == 7) {
            int angle;
            cout<< "Enter angle from (90, 180, 270): " ;
            cin>>angle;
            Apply_rotate_filter(img,angle);
            modified = true;
        }
        else if (choice == 8) {
            Apply_Lighten_Darken_filter(img);
            modified = true;
        }
        else if (choice == 9) {
            Apply_Crop_filter(img);
            modified = true;
        }
        else if (choice == 10) {
            Apply_frame_filter(img);
            modified = true;
        }
        else if (choice == 11) {
            Apply_Edge_Detection_filter(img);
            modified = true;
        }
        else if (choice == 13) {
            Apply_Blur_Filter(img);
            modified = true;
        }
        else if (choice == 14) {
            Apply_Sunlight_filter(img);
            modified = true;
        }
        
        else if (choice == 16) {
            Apply_TV_Noise_Filter(img);
            modified = true;
        }
        else if (choice == 17) {
            Apply_Purple_filter(img);
            modified = true;
        }
        
        else if (choice == 19) {
            Apply_Skew_Filter(img);
            modified = true;
        }
        else if (choice == 20) {
            string out;
            cout << "Enter filename (with extension .jpg/.png/.bmp): ";
            cin >> out;
            try {
                img.saveImage(out);
                modified = false;
                cout << "Image saved successfully.\n";
            } catch (exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 21) {
            if (modified) {
                cout << "Do you want to save before exit? (y/n): ";
                char ans; cin >> ans;
                if (ans == 'y' || ans == 'Y') {
                    string out;
                    cout << "Enter filename to save: ";
                    cin >> out;
                    try {
                        img.saveImage(out);
                        cout << "Image saved successfully.\n";
                    } catch (exception &e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                }
            }
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}




