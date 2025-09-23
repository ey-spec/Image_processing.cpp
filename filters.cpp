#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

void displayMenu() {
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
// ===== Filter 1: Grayscale Conversion =====
void applyGrayscale(Image &img) {
    int width = img.width;
    int height = img.height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);

            unsigned char gray = static_cast<unsigned char>((r + g + b) / 3);

            img.setPixel(x, y, 0, gray);
            img.setPixel(x, y, 1, gray);
            img.setPixel(x, y, 2, gray);
        }
    }
    cout << "[Grayscale filter is applied]\n";
}
int main() {
    Image img;        // current image
    bool loaded = false;
    bool modified = false;
    int choice;

    // ====== STEP 1: Load initial image ======
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

    // ====== STEP 2: Main Loop ======
    while (true) {
        displayMenu();
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
            applyGrayscale(img);
            modified = true;
        }
        else if (choice == 3) {
            cout << "[Black & White filter is applied]\n";
            modified = true;
        }
        else if (choice == 4) {
            cout << "[Invert filter is applied]\n";
            modified = true;
        }
        else if (choice == 5) {
            cout << "[Merge filter is applied]\n";
            modified = true;
        }
        else if (choice == 6) {
            cout << "[Flip filter is applied]\n";
            modified = true;
        }
        else if (choice == 7) {
            cout << "[Rotate filter is applied]\n";
            modified = true;
        }
        else if (choice == 8) { // Save
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
        else if (choice == 9) { // Exit
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
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
