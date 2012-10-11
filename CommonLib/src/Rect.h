#ifndef RECT_H
#define RECT_H

struct Rect
{
	int x, y;
	int width, height;

	Rect(int p_x, int p_y, int p_width, int p_height)
	{
		x		= p_x;
		y		= p_y;
		width	= p_width;
		height	= p_height;
	}
	Rect()
	{
		x		= 0;
		y		= 0;
		width	= 0;
		height	= 0;
	}
};

#endif