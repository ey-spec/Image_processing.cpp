Image Processing Filters

Course: CS213 – Object Oriented Programming

Instructor: Dr. Mohamed El Ramly

Section: All-B

Members:

Eyad Hatem – 20240097

Sherif Ahmed – 20240277

Karim Ashraf – 20240419

Project Overview

This project is a C++ image processing program that allows users to load, edit, and save images using different filters.
It applies object-oriented programming (OOP) concepts such as encapsulation and modular design.
Each filter is implemented as a separate function for better organization and readability.

The program provides a simple menu system that guides the user through all available options.

Main Features

Load a new image from file.

Apply various filters and effects.

Undo the last filter.

Save the edited image.

Exit the program safely.

Implemented Filters


1	Grayscale:	Convert the image into shades of gray.

2	Black & White:	Convert the image to pure black and white.

3	Invert:	Invert all image colors (255 - RGB).

4	Merge:	Combine two different images into one.

5	Flip:	Flip the image horizontally or vertically.

6	Rotate:	Rotate the image by 90°, 180°, or 270°.

7	Darken & Lighten:	Adjust the brightness of the image.

8	Crop:	Select and cut a specific part of the image.

9	Add Frame:	Add a colored or decorated frame.

10	Edge Detection:	Highlight the edges in the image.

11	Resize:	Change image width and height.

12	Blur:	Soften the image for a smoother look.

13	Natural Sunlight:	Add warm sunlight color tones.

14	Oil Painting:	Create an artistic oil painting effect.

15	TV Noise:	Add random noise similar to old TV static.

16	Purple Effect:	Apply a purple hue to the image.

17	Infrared:	Simulate infrared photography with red tones.

18	Image Skewing:	Skew the image left or right by a chosen degree.

—	Undo:	Restore the previous image before the last change.

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

Image class – handles loading, saving, and pixel manipulation.

Individual filter functions – apply transformations to the image.

main() function – manages user input and calls the right functions.

Conclusion

This project shows how C++ and OOP principles can be used to build a functional image editor.
It focuses on modularity, teamwork, and creativity in image transformation.
Each member contributed effectively to make the project stable, organized, and easy to use.
