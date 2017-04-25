#include "tgaimage.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
	bool steep = false;
	// if the line is steep, we transpose the image
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	// make it left−to−right 
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror = std::abs(dy) * 2;
	int error = 0;
	int y = y0;

	for (int x = x0; x <= x1; ++x)
	{
		if (steep)
			image.set(y, x, color); // if transposed, de−transpose 
		else
			image.set(x, y, color);

		error += derror;

		if (error > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}

void dot(int x, int y, TGAImage &image, TGAColor color)
{
	image.set(x, y, color);
}

int main(int argc, char** argv)
{
	TGAImage image(100, 100, TGAImage::RGB);

	//line(13, 20, 80, 40, image, white);
	line(20, 13, 40, 80, image, red);
	line(80, 40, 13, 20, image, red);

	image.flip_vertically(); // set the pivot to the left lower corner.
	image.write_tga_file("output.tga");

	//std::cin.get();

	return 0;
}