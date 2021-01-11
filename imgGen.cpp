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

const int HEIGHT = 250;
const int WIDTH = 300;

/**
*	Creates the image.
*
*	@param	image - the 2D array to plot grayscale colors on
*				height - the height of the array
*/

void createImage(unsigned char image[][WIDTH], int height);

/**
*	Writes the 2D array to disk as a PGM file.
*
*	@param	image - the 2D array containing the image
*				height - the height of the array
*			fileName - the filename (relative to the directory that imgGen is run in) to write the image to.
*	@return true if image write is successful,
*		 false otherwise
*/

bool writeImage(const unsigned char image[][WIDTH], int height, const std::string fileName);

/**
*	Draws a rectangle to the 2D array.
*
*	@param	image - the 2D array containing the image
*			imgHeight - the height of the image's 2D array
*			rectTop - the upper bound of the rectangle
*			rectLeft - the left bound of the rectangle
*			rectHeight - the height of the rectangle
*			rectWidth - the width of the rectangle
*			grayLevel - the intensity of gray to draw with
*/

void drawRect(unsigned char image[][WIDTH], int imgHeight, int rectTop, int rectLeft, int rectHeight, int rectWidth, unsigned char grayLevel);

/**
*	Draws a circle to the 2D array.
*
*	@param	image - the 2D array containing the image
*			height - the height of the image's 2D array
*			centerX - the x-coordinate of the center of the circle
*			centerY - the y-coordinate of the center of the circle
*			radius - the radius of the circle
*			grayLevel - the intensity of gray to draw with
*/

void drawCircle(unsigned char image[][WIDTH], int height, int centerX, int centerY, int radius, unsigned char grayLevel);


int main()
{
	// set array to white
	unsigned char image[HEIGHT][WIDTH];
	createImage(image, HEIGHT);
	writeImage(image, HEIGHT, "foo.pgm");
}

// ------------------------------------------------------

void createImage(unsigned char image[][WIDTH], int height) {
	// Initializes the image to a blank white background
	for (int row = 0; row < WIDTH; row++) {
		for (int column = 0; column < height; column++) {
			image[column][row] = 255;
		}
	}
	
	drawRect(image, height, 120, 20, 40, 20, 20);
	drawRect(image, height, 223, 65, 24, 50, 20);
	drawCircle(image, height, 50, 50, 31, 0);
	drawCircle(image, height, 72, 143, 42, 0);
}

// ------------------------------------------------------

void drawRect(unsigned char image[][WIDTH], int imgHeight, int rectTop, int rectLeft, int rectHeight, int rectWidth, unsigned char grayLevel) {
	// Draws the top and bottom line of the rectangle
	for (int horizontalPosition = rectLeft; horizontalPosition < rectLeft + rectWidth; horizontalPosition++) {
		image[rectTop][horizontalPosition] = grayLevel;
		image[rectTop + rectHeight - 1][horizontalPosition] = grayLevel;
	}
	// Draws the left and right lines of the rectangle
	for (int verticalPosition = rectTop; verticalPosition < rectTop + rectHeight; verticalPosition++) {
		image[verticalPosition][rectLeft] = grayLevel;
		image[verticalPosition][rectLeft + rectWidth - 1] = grayLevel;
	}
}

// ------------------------------------------------------

void drawCircle(unsigned char image[][WIDTH], int height, int centerX, int centerY, int radius, unsigned char grayLevel) {
	int x = radius;
	int y = 0;
	int err = 0;
 
	while (x >= y) {
		// Fill in all 4 quadrants at once.
		image[centerY + y][centerX + x] = grayLevel;
		image[centerY + x][centerX + y] = grayLevel;
		image[centerY + x][centerX - y] = grayLevel;
		image[centerY + y][centerX - x] = grayLevel;
		image[centerY - y][centerX - x] = grayLevel;
		image[centerY - x][centerX - y] = grayLevel;
		image[centerY - x][centerX + y] = grayLevel;
		image[centerY - y][centerX + x] = grayLevel;
	
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

bool writeImage(const unsigned char image[][WIDTH], int height, const std::string fileName) {
	std::ofstream myfile;
	myfile.open (fileName);
	
	myfile << "P2" << std::endl << "# " << fileName << std::endl << std::endl << WIDTH << " " << height << std::endl << 256 << std::endl;
	
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < WIDTH; column++) {
			myfile << static_cast<int>(image[row][column]) << " ";
		}
		myfile << std::endl;
	}
	myfile.close();
	return true;
}