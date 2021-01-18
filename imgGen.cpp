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

const int HEIGHT = 512;
const int WIDTH = 512;

struct Color {
	unsigned char red;
	unsigned char blue;
	unsigned char green;
	
	Color() {
		red = 0;
		blue = 0;
		green = 0;
	}
	
	Color(int r_, int g_, int b_) {
		red = static_cast<char>(r_);
		green = static_cast<char>(g_);
		blue = static_cast<char>(b_);
	}
};

struct Coords {
	int x;
	int y;
	
	Coords() {
		x = 0;
		y = 0;
	}
	
	Coords (int x_, int y_) {
		x = x_;
		y = y_;
	}
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

/**
*	Flood-fills a section of the image.
*
*	@param	image - the 2D array containing the image
*			x - the x-coordinate to start filling from
*			y - the y-coordinate to start filling from
*			oldColor - the color to fill over
*			newColor - the color to fill with
*/

void floodFill(Color image[][WIDTH], int x, int y, Color oldColor, Color newColor);

/**
*	Helper function for bezier.
*/

int getPt( int n1 , int n2 , float perc );

/**
*	Draws a bezier curve.
*
*	@param	image - the 2D array containing the image
*			coords (1-4) - the coordinates to make a bezier curve with. There are 3 of them for a triangular bezier, and 4 for a cubic.
*			color - the color to draw with
*/

void bezier(Color image[][WIDTH], Coords coords1, Coords coords2, Coords coords3, Color color);

void bezier(Color image[][WIDTH], Coords coords1, Coords coords2, Coords coords3, Coords coords4, Color color);


int main()
{
	// set array to white
	Color image[HEIGHT][WIDTH];
	createImage(image, HEIGHT);
	writeImage(image, HEIGHT, "Wildflowers.ppm");
}

// ------------------------------------------------------

void createImage(Color image[][WIDTH], int height) {
	// Initializes the image to a blank white background
	Color red = Color(163, 66, 58);
	Color white = Color(255, 255, 255);
	Color yellow = Color(224, 175, 113);
	Color brown = Color(149, 130, 100);
	Color black = Color(0, 0, 0);
	
	for (int row = 0; row < WIDTH; row++) {
		for (int column = 0; column < height; column++) {
			image[column][row] = brown;
		}
	}

	drawCircle(image, height, 256, 256, 90, red);
	floodFill(image, 256, 256, image[256][256], red);
	
	// Flower
	bezier(image, Coords(238, 263), Coords(233, 272), Coords(225, 293), Coords(225, 304), white);
	bezier(image, Coords(237, 320), Coords(233, 319), Coords(225, 316), Coords(225, 304), white);
	bezier(image, Coords(237, 320), Coords(241, 321), Coords(245, 315), Coords(245, 311), white);
	bezier(image, Coords(245, 311), Coords(245, 306), Coords(242, 302), Coords(237, 302), white);
	bezier(image, Coords(237, 302), Coords(232, 302), Coords(234, 310), Coords(236, 310), white);
	bezier(image, Coords(236, 310), Coords(238, 311), Coords(238, 305), white);
	
	bezier(image, Coords(237, 263), Coords(235, 268), Coords(219, 295), Coords(208, 296), white);
	bezier(image, Coords(196, 277), Coords(190, 281), Coords(196, 296), Coords(208, 296), white);
	bezier(image, Coords(196, 277), Coords(202, 273), Coords(207, 277), Coords(207, 279), white);
	bezier(image, Coords(202, 285), Coords(207, 285), Coords(208, 280), Coords(207, 279), white);
	bezier(image, Coords(202, 285), Coords(197, 285), Coords(200, 277), Coords(203, 280), white);
	
	bezier(image, Coords(276, 263), Coords(281, 272), Coords(290, 293), Coords(290, 304), white);
	bezier(image, Coords(278, 320), Coords(282, 319), Coords(290, 316), Coords(290, 304), white);
	bezier(image, Coords(278, 320), Coords(274, 321), Coords(269, 315), Coords(269, 311), white);
	bezier(image, Coords(278, 302), Coords(273, 302), Coords(269, 306), Coords(269, 311), white);
	bezier(image, Coords(278, 302), Coords(283, 302), Coords(281, 310), Coords(279, 310), white);
	bezier(image, Coords(276, 305), Coords(277, 311), Coords(279, 310), white);
	
	bezier(image, Coords(311, 280), Coords(316, 278), Coords(317, 285), Coords(312, 285), white);
	bezier(image, Coords(307, 279), Coords(307, 280), Coords(307, 285), Coords(312, 285), white);
	bezier(image, Coords(307, 279), Coords(308, 277), Coords(312, 273), Coords(318, 277), white);
	bezier(image, Coords(307, 296), Coords(318, 296), Coords(324, 281), Coords(318, 277), white);
	bezier(image, Coords(307, 296), Coords(296, 295), Coords(279, 268), Coords(278, 263), white);
	
	bezier(image, Coords(267, 235), Coords(271, 226), Coords(281, 226), yellow);
	bezier(image, Coords(297, 243), Coords(297, 236), Coords(292, 226), Coords(281, 226), yellow);
	bezier(image, Coords(297, 243), Coords(297, 250), Coords(288, 257), Coords(281, 256), yellow);
	bezier(image, Coords(267, 246), Coords(275, 256), Coords(281, 256), yellow);
	bezier(image, Coords(281, 241), Coords(284, 242), Coords(284, 242), white);
	
	bezier(image, Coords(249, 237), Coords(240, 226), Coords(233, 226), yellow);
	bezier(image, Coords(217, 251), Coords(217, 232), Coords(226, 226), Coords(233, 226), yellow);
	bezier(image, Coords(217, 242), Coords(217, 251), Coords(227, 257), Coords(232, 257), yellow);
	bezier(image, Coords(249, 245), Coords(238, 257), Coords(232, 257), yellow);
	bezier(image, Coords(230, 243), Coords(232, 241), Coords(232, 241), white);
	
	bezier(image, Coords(241, 211), Coords(241, 218), Coords(255, 230), yellow);
	bezier(image, Coords(241, 211), Coords(241, 203), Coords(248, 195), Coords(256, 195), yellow);
	bezier(image, Coords(271, 212), Coords(271, 205), Coords(264, 195), Coords(256, 195), yellow);
	bezier(image, Coords(271, 212), Coords(271, 219), Coords(260, 228), yellow);
	bezier(image, Coords(256, 209), Coords(257, 212), Coords(257, 212), white);
	
	bezier(image, Coords(256, 252), Coords(243, 263), Coords(243, 271), yellow);
	bezier(image, Coords(243, 271), Coords(243, 279), Coords(254, 286), Coords(259, 286), yellow);
	bezier(image, Coords(259, 286), Coords(265, 286), Coords(273, 281), Coords(273, 272), yellow);
	bezier(image, Coords(273, 272), Coords(273, 264), Coords(256, 252), yellow);
	bezier(image, Coords(258, 269), Coords(258, 272), Coords(258, 272), white);
	
	// "Wildflowers"
	bezier(image, Coords(112, 385), Coords(112, 402), Coords(108, 407), black);
	bezier(image, Coords(108, 407), Coords(108, 407), Coords(117, 397), black);
	bezier(image, Coords(117, 397), Coords(117, 409), Coords(121, 408), black);
	bezier(image, Coords(121,408), Coords(125,407), Coords(135, 392), Coords(126,383), black);
	bezier(image, Coords(135, 394), Coords(131, 404), Coords(133, 405), black);
	bezier(image, Coords(133, 405), Coords(135, 406), Coords(149, 384), Coords(147, 383), black);
	bezier(image, Coords(147, 383), Coords(143, 383), Coords(140, 409), black);
	bezier(image, Coords(140, 409), Coords(151, 394), Coords(154, 394), black);
	bezier(image, Coords(147, 407), Coords(142, 407), Coords(151, 394), black);
	bezier(image, Coords(147, 407), Coords(153, 407), Coords(157, 394), Coords(154, 394), black);
	bezier(image, Coords(155, 394), Coords(159, 393), Coords(160, 384), Coords(158, 384), black);
	bezier(image, Coords(158, 384), Coords(157, 384), Coords(154, 406), Coords(154, 408), black);
	bezier(image, Coords(154, 408), Coords(155, 409), Coords(164, 394), black);
	bezier(image, Coords(164, 394), Coords(167, 378), Coords(151, 425), Coords(154, 424), black);
	bezier(image, Coords(163, 394), Coords(163, 394), Coords(172, 388), black);
	bezier(image, Coords(172, 388), Coords(172, 388), Coords(168, 407), black);
	bezier(image, Coords(168, 407), Coords(168, 407), Coords(174, 401), black);
	
	// "Tom"
	bezier(image, Coords(189, 143), Coords(200, 97), Coords(200, 97), black);
	bezier(image, Coords(182, 100), Coords(226, 92), Coords(226, 92), black);
	bezier(image, Coords(212, 115), Coords(216, 118), Coords(215, 122), black);
	bezier(image, Coords(215, 122), Coords(214, 127), Coords(208, 129), Coords(206, 127), black);
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

void floodFill(Color image[][WIDTH], int x,int y, Color oldColor, Color newColor) {
	std::cout << "x: " << x << " y: " << y << std::endl;
	if((image[x][y].red == oldColor.red) && (image[x][y].green == oldColor.green) && (image[x][y].blue == oldColor.blue)) {
		image[x][y] = newColor;
		if (x + 1 < WIDTH-1) floodFill(image, x+1,y, oldColor, newColor);
		if (y + 1 < HEIGHT-1) floodFill(image, x,y+1, oldColor, newColor);
		if (x - 1 > 0) floodFill(image, x-1,y, oldColor, newColor);
		if (y - 1 > 0) floodFill(image, x,y-1, oldColor, newColor);
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

int getPt( int n1 , int n2 , float perc ) {
	int diff = n2 - n1;

	return n1 + ( diff * perc );
}

void bezier(Color image[][WIDTH], Coords coords1, Coords coords2, Coords coords3, Color color) {
	int x = 0;
	int y = 0;
	int ya = 0;
	int yb = 0;
	int xa = 0;
	int xb = 0;
	
	for( float i = 0 ; i < 1 ; i += 0.01 ) {
		// The Green Line
		xa = getPt(coords1.x, coords2.x, i);
		ya = getPt(coords1.y, coords2.y, i);
		xb = getPt(coords2.x, coords3.x, i);
		yb = getPt(coords2.y, coords3.y, i);
	
		// The Black Dot
		x = getPt(xa,xb,i);
		y = getPt(ya,yb,i);
	
		image[y][x] = color;
	}
}

void bezier(Color image[][WIDTH], Coords coords1, Coords coords2, Coords coords3, Coords coords4, Color color) {

	int x;
	int y;
	int ya;
	int yb;
	int yc;
	int xa;
	int xb;
	int xc;
	
	int ym;
	int xm;
	int yn;
	int xn;

	for (float i = 0 ; i < 1 ; i += 0.01){
		// The Green Lines
		xa = getPt( coords1.x , coords2.x , i );
		ya = getPt( coords1.y , coords2.y , i );
		xb = getPt( coords2.x , coords3.x , i );
		yb = getPt( coords2.y , coords3.y , i );
		xc = getPt( coords3.x , coords4.x , i );
		yc = getPt( coords3.y , coords4.y, i );
	
		// The Blue Line
		xm = getPt( xa , xb , i );
		ym = getPt( ya , yb , i );
		xn = getPt( xb , xc , i );
		yn = getPt( yb , yc , i );
	
		// The Black Dot
		x = getPt( xm , xn , i );
		y = getPt( ym , yn , i );
	
		image[y][x] = color;
	}
}