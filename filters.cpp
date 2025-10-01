#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

void Display_Menu() {
    cout << "\n=== Image Processing Menu ===\n";
    cout << "1. Load New Image\n";
    cout << "2. Apply Grayscale Filter\n";
    cout << "3. Apply Black & White Filter\n";
    cout << "4. Apply Invert Filter\n";
    cout << "5. Merge Two Images\n";
    cout << "6. Flip Image\n";
    cout << "7. Rotate Image\n";
    cout << "8. Save Current Image\n";
    cout << "9. Exit\n";
    cout << "Choose option: ";
}
//Filter 1: Grayscale Filter
void Apply_Grayscale(Image &img) {
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
//Filter 2: Black and White Filter
void Apply_black_white(Image &img) {
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
//Filter 3:Invert Filter

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

// Filter 4: Merge Two Images 
void Apply_Merge(Image &img) {
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
//Filter 5: Flip Image
void Apply_Flip(Image &img) {
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
//Filter 6: Rotate Image

void Apply_rotate_filter(Image &img , int angle){
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


int main() {
    Image img;
    bool loaded = false;
    bool modified = false;
    int choice;

    //Load first image 
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
            Apply_Grayscale(img);
            modified = true;
        }
        else if (choice == 3) {
            Apply_black_white(img);
            modified = true;
        }
        else if (choice == 4) {
            Apply_Invert_filter(img);
            modified = true;
        }
        else if (choice == 5) {
            Apply_Merge(img);
            modified = true;
        }
        else if (choice == 6) {
            Apply_Flip(img);
            modified = true;
        }
        else if (choice == 7) {
            Apply_rotate_filter(img);
            modified = true;
        }
        else if (choice == 8) {
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
        else if (choice == 9) {
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






