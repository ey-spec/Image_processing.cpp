Image Processing Filters

Course: CS213 – Object Oriented Programming
Instructor: Dr. Mohamed El Ramly

Members:

Eyad Hatem – 20240097/S26

Sherif Ahmed – 20240277/All-B

Karim Ashraf – 20240419/S26

Project Overview

This project is a C++ image processing program that allows users to load, edit, and save images using different filters.
It applies object-oriented programming (OOP) concepts such as encapsulation and modular design.
Each filter is implemented as a separate function for better organization and readability.

The program provides a simple menu system that guides the user through all available options.
Additionally, a graphical user interface (GUI) was developed using the Qt framework to provide a more interactive and user-friendly experience.

Main Features

Load a new image from file.

Apply various filters and effects.

Undo the last filter.

Save the edited image.

Exit the program safely.

Implemented Filters

Grayscale: Convert the image into shades of gray.

Black & White: Convert the image to pure black and white.

Invert: Invert all image colors (255 - RGB).

Merge: Combine two different images into one.

Flip: Flip the image horizontally or vertically.

Rotate: Rotate the image by 90°, 180°, or 270°.

Darken & Lighten: Adjust the brightness of the image.

Crop: Select and cut a specific part of the image.

Add Frame: Add a colored or decorated frame.

Edge Detection: Highlight the edges in the image.

Resize: Change image width and height.

Blur: Soften the image for a smoother look.

Natural Sunlight: Add warm sunlight color tones.

Oil Painting: Create an artistic oil painting effect.

TV Noise: Add random noise similar to old TV static.

Purple Effect: Apply a purple hue to the image.

Infrared: Simulate infrared photography with red tones.

Image Skewing: Skew the image left or right by a chosen degree.

Film Effect: Apply a cinematic film color tone for a classic movie look.

Motion Blur: Simulate motion blur to give a sense of movement.

Sepia Tone: Add a warm brown tint to create a vintage photo style.

Pencil Sketch: Convert the image to a pencil-drawn sketch style.

— Undo: Restore the previous image before the last change.

How to Use

Run the program.

Enter the name of the image file you want to load.

Choose a filter from the displayed menu.

Apply as many filters as you want.

Use the Undo option if you want to revert the last filter.

Save your final image with a new name.

Technical Details

Language: C++

Programming Paradigm: Object-Oriented Programming (OOP)

Main Components:

Image class: Handles loading, saving, and pixel manipulation.

Individual filter functions: Apply transformations to the image.

main() function: Manages user input and calls the right functions.

GUI (Qt): Provides an interactive visual interface for easier image manipulation.

Conclusion

This project demonstrates how C++ and OOP principles can be used to build a functional and extensible image editor.
It focuses on modularity, teamwork, and creativity in image transformation.
Each member contributed effectively to make the project stable, organized, and easy to use.
The addition of a Qt-based GUI enhances the overall usability and visual interaction of the program.
