/** --------------------------------------------------------
	
	@file    imgGen.cpp
	@author  Charlie Welsh
	@version 1.0
	
	CS162-01 - Assignment 1.1
		Generates image file in PGM format
	
* ------------------------------------------------------------ */


#include <iostream>
#include <fstream>
#include <string>

const int HEIGHT = 500;
const int WIDTH = 512;

struct Color {
	unsigned char red;
	unsigned char blue;
	unsigned char green;
};

/**
*	Creates the image.
*
*	@param	image - the 2D array of Color structs to plot colors on
*			height - the height of the array
*/

void createImage(Color image[][WIDTH], int height);

/**
*	Writes the 2D array to disk as a PGM file.
*
*	@param	image - the 2D array containing the image
*				height - the height of the array
*			fileName - the filename (relative to the directory that imgGen is run in) to write the image to.
*	@return true if image write is successful,
*		 false otherwise
*/

bool writeImage(const Color image[][WIDTH], int height, const std::string fileName);

/**
*	Draws a rectangle to the 2D array.
*
*	@param	image - the 2D array containing the image
*			imgHeight - the height of the image's 2D array
*			rectTop - the upper bound of the rectangle
*			rectLeft - the left bound of the rectangle
*			rectHeight - the height of the rectangle
*			rectWidth - the width of the rectangle
*			color - the color to draw with
*/

void drawRect(Color image[][WIDTH], int imgHeight, int rectTop, int rectLeft, int rectHeight, int rectWidth, Color color);

/**
*	Draws a circle to the 2D array.
*
*	@param	image - the 2D array containing the image
*			height - the height of the image's 2D array
*			centerX - the x-coordinate of the center of the circle
*			centerY - the y-coordinate of the center of the circle
*			radius - the radius of the circle
*			color - the color to draw with
*/

void drawCircle(Color image[][WIDTH], int height, int centerX, int centerY, int radius, Color color);


int main()
{
	// set array to white
	Color image[HEIGHT][WIDTH];
	createImage(image, HEIGHT);
	writeImage(image, HEIGHT, "foo.ppm");
}

// ------------------------------------------------------

void createImage(Color image[][WIDTH], int height) {
	// Initializes the image to a blank white background
	for (int row = 0; row < WIDTH; row++) {
		for (int column = 0; column < height; column++) {
			image[column][row].red = 255;
			image[column][row].green = 255;
			image[column][row].blue = 255;
		}
	}
	
	Color red = { .red = 163, .green = 66, .blue = 58 };
	
	//drawRect(image, height, 120, 20, 40, 20, red);
	//drawRect(image, height, 223, 65, 24, 50, red);
	drawCircle(image, height, 256, 250, 89, red);
	//drawCircle(image, height, 72, 143, 42, red);
}

// ------------------------------------------------------

void drawRect(Color image[][WIDTH], int imgHeight, int rectTop, int rectLeft, int rectHeight, int rectWidth, Color color) {
	// Draws the top and bottom line of the rectangle
	for (int horizontalPosition = rectLeft; horizontalPosition < rectLeft + rectWidth; horizontalPosition++) {
		image[rectTop][horizontalPosition] = color;
		image[rectTop + rectHeight - 1][horizontalPosition] = color;
	}
	// Draws the left and right lines of the rectangle
	for (int verticalPosition = rectTop; verticalPosition < rectTop + rectHeight; verticalPosition++) {
		image[verticalPosition][rectLeft] = color;
		image[verticalPosition][rectLeft + rectWidth - 1] = color;
	}
}

// ------------------------------------------------------

void drawCircle(Color image[][WIDTH], int height, int centerX, int centerY, int radius, Color color) {
	int x = radius;
	int y = 0;
	int err = 0;
 
	while (x >= y) {
		// Fill in all 4 quadrants at once.
		image[centerY + y][centerX + x] = color;
		image[centerY + x][centerX + y] = color;
		image[centerY + x][centerX - y] = color;
		image[centerY + y][centerX - x] = color;
		image[centerY - y][centerX - x] = color;
		image[centerY - x][centerX - y] = color;
		image[centerY - x][centerX + y] = color;
		image[centerY - y][centerX + x] = color;
	
		if (err <= 0) {
			y += 1;
			err += 2*y + 1;
		}
	 
		if (err > 0) {
			x -= 1;
			err -= 2*x + 1;
		}
	}
}

// ------------------------------------------------------

bool writeImage(const Color image[][WIDTH], int height, const std::string fileName) {
	std::ofstream myfile;
	myfile.open (fileName);
	
	myfile << "P3" << std::endl << "# " << fileName << std::endl << std::endl << WIDTH << " " << height << std::endl << 255 << std::endl;
	
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < WIDTH; column++) {
			myfile << static_cast<int>(image[row][column].red) << " " << static_cast<int>(image[row][column].green) << " " << static_cast<int>(image[row][column].blue) << " ";
		}
		myfile << std::endl;
	}
	myfile.close();
	return true;
}