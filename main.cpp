#include <iostream>
#include <fstream>
#include <string>

const int HEIGHT = 250;
const int WIDTH = 300;

void createImage(unsigned char image[][WIDTH], int height);
bool writeImage(const unsigned char image[][WIDTH], int height, const std::string fileName);
void drawRect(unsigned char image[][WIDTH], int imgHeight, int rectTop, int rectLeft, int rectHeight, int rectWidth, unsigned char grayLevel);
void drawCircle(unsigned char image[][WIDTH], int height, int centerX, int centerY, int radius, unsigned char grayLevel);


int main()
{
	// set array to white
	unsigned char image[HEIGHT][WIDTH];
	createImage(image, HEIGHT);
	writeImage(image, HEIGHT, "foo.pgm");
}

void createImage(unsigned char image[][WIDTH], int height) {
	// Initializes the image to a blank white background
	for (int row = 0; row < WIDTH; row++) {
		for (int column = 0; column < HEIGHT; column++) {
			image[column][row] = 255;
		}
	}
	
	
	drawRect(image, HEIGHT, 120, 20, 40, 20, 20);
	drawRect(image, HEIGHT, 223, 65, 24, 50, 20);
	drawCircle(image, HEIGHT, 50, 50, 31, 0);
	drawCircle(image, HEIGHT, 72, 143, 42, 0);
}

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

void drawCircle(unsigned char image[][WIDTH], int height, int centerX, int centerY, int radius, unsigned char grayLevel) {
	int x = radius;
	int y = 0;
	int err = 0;
 
	while (x >= y) {
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

bool writeImage(const unsigned char image[][WIDTH], int height, const std::string fileName) {
	std::ofstream myfile;
	myfile.open (fileName);
	
	//myfile << static_cast<char>(HEIGHT) << " " << static_cast<char>(WIDTH) << std::endl << static_cast<char>(256) << std::endl;
	myfile << "P2" << std::endl << "# " << fileName << std::endl << std::endl << WIDTH << " " << HEIGHT << std::endl << 256 << std::endl;
	
	for (int row = 0; row < HEIGHT; row++) {
		for (int column = 0; column < WIDTH; column++) {
			myfile << static_cast<int>(image[row][column]) << " ";
		}
		myfile << std::endl;
	}
	myfile.close();
	return true;
}