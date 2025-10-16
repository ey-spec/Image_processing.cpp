# Image Processing Filters (Qt GUI Edition)

---

## **Course Information**
**Course:** CS213 – Object Oriented Programming  
**Instructor:** Dr. Mohamed El Ramly   

---

## **Team Members**
- Eyad Hatem – 20240097 / S26 
- Sherif Ahmed – 20240277  / All-B
- Karim Ashraf – 20240419 / S26

---

## **Project Overview**
This project is a C++ image processing application developed using the Qt Framework to provide an interactive graphical user interface (GUI).  
It allows users to load, view, edit, and save images using a wide range of filters and visual effects.  
The project demonstrates the use of Object-Oriented Programming (OOP) principles such as encapsulation, modularity, inheritance, and reusability.

---

## **Main Features**
- Load and preview images directly in the GUI.  
- Apply multiple filters and effects to images.  
- Undo the last applied filter.  
- Save the edited image with a custom name.  
- Simple, user-friendly interface built with Qt Widgets.  
- Organized and modular code based on OOP concepts.  

---

## **Implemented Filters**

### **Basic Filters**
1. **Grayscale** – Convert the image into shades of gray.  
2. **Black & White** – Convert to pure black and white.  
3. **Invert** – Invert all colors (255 - RGB).  
4. **Merge** – Combine two images into one.  
5. **Flip** – Flip the image horizontally or vertically.  
6. **Rotate** – Rotate the image by 90°, 180°, or 270°.  
7. **Darken & Lighten** – Adjust the brightness.  
8. **Crop** – Select and cut a specific region of the image.  
9. **Resize** – Change the image dimensions.  
10. **Add Frame** – Add a colored or decorated border.  
11. **Edge Detection** – Highlight edges using gradient-based filtering.  
12. **Blur** – Soften the image for a smoother look.  

### **Artistic and Advanced Filters**
13. **Natural Sunlight** – Add warm sunlight tones.  
14. **Oil Painting Effect** – Simulate an artistic oil painting.  
15. **TV Noise** – Add random static noise.  
16. **Purple Effect** – Apply a violet or purple tint.  
17. **Infrared Effect** – Simulate infrared-style photography.  
18. **Image Skewing** – Skew the image left or right.  
19. **Sepia Effect** – Add a classic warm vintage tone.  
20. **Motion Blur** – Add a motion-like blur effect.  
21. **Pencil Sketch** – Convert the image to a pencil drawing style.  
22. **Film Effect** – Add cinematic colors and tones.  
23. **Frame Styles** – Choose between different frame templates.  

---

## **GUI Overview**
The graphical interface was created using Qt Widgets and designed for simplicity and ease of use.  

### **Main Components**
- **Load Button** – Choose and open an image from your device.  
- **Filter Buttons** – Apply selected filters with one click.  
- **Save Button** – Save the edited image to a file.  
- **Undo Button** – Revert to the previous image.  
- **Preview Label** – Displays the image in real-time.  
- **Dialogs** – Used for file selection, color picking, and text input.  

---

## **Technical Details**
- **Language:** C++  
- **Framework:** Qt 6 (Qt Widgets)  
- **Compiler:** MinGW 64-bit  
- **Build System:** CMake  
- **Programming Paradigm:** Object-Oriented Programming (OOP)  

---

## **Code Structure**

### **File Descriptions:**
- **main.cpp:** Entry point of the application.  
- **widget.h / widget.cpp:** Handles GUI logic and user interaction.  
- **filters.h / filters.cpp:** Contains all implemented image filters.  
- **image_class.h:** Handles image loading, saving, and pixel manipulation.  
- **CMakeLists.txt:** Build configuration file for the project.  

---

> **Note:** The program loads images from the same directory where the executable file is located.  
> You can also select any image manually using the "Load" button in the GUI.  

---

## **How to Run the Program**

### **Option 1: Run from Qt Creator**
1. Open the project using the `.pro` or `CMakeLists.txt` file.  
2. Build the project by clicking the **Run** button.  
3. The GUI window will open automatically.  
4. Use the buttons to apply filters, undo, or save images.  

### **Option 2: Run from Visual Studio Code**
1. Open the folder in VS Code.  
2. Press **Ctrl + Shift + B** to build and compile the executable.  
3. Run the generated `.exe` file.  
4. Make sure the image files are in the same folder as the executable.  

---

## **Undo Feature**
Before each filter is applied, the program saves a backup copy of the current image.  
You can restore the previous version anytime by pressing the **Undo** button.  

---

## **Future Enhancements**
- Add live preview for filters before applying them.  
- Support drag and drop image loading.  
- Add AI-based filters such as background removal or style transfer.  

---

## **Conclusion**
This project demonstrates how C++ and the Qt Framework can be combined to build a functional and user-friendly image editor.  
It applies key OOP principles to ensure modularity, maintainability, and extensibility.  
Each team member contributed to different parts of the project, resulting in a stable and organized application that supports a wide variety of image filters.  


## **File and Folder Setup**

