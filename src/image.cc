/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "image.h"

using std::istream;

namespace wasteland
{

/**
 * Constructor.
 *
 * @param width
 *            The image width.
 * @param height
 *            The image height.
 * @param transparent
 *            If image can have transparent pixels. Defaults to false.
 */
image::image(const int width, const int height, const bool transparent) :
    width_(width), height_(height), dummy_(0)
{
	pixels_ = new color[width * height];
	transparency_ = transparent ? -1 : 0;
}

/**
 * Destructor.
 */
image::~image()
{
	delete[] pixels_;
}

/**
 * Returns the image width.
 *
 * @return The image width.
 */
int image::width() const
{
	return width_;
}

/**
 * Returns the image height.
 *
 * @return The image height.
 */
int image::height() const
{
	return height_;
}

/**
 * Returns a read-only reference to the color at the specified position of the
 * image.
 *
 * @param x
 *            The X position in the image.
 * @param y
 *            The Y position in the image.
 * @return The reference to the color.
 */
const image::color& image::operator()(const int x, const int y) const
{
	if (y < 0 || x < 0 || x >= width_ || y >= height_)
		return transparency_;
	return pixels_[width_ * y + x];
}

/**
 * Returns a reference to the color at the specified position of the image.
 *
 * @param x
 *            The X position in the image.
 * @param y
 *            The Y position in the image.
 * @return The reference to the color.
 */
image::color& image::operator()(const int x, const int y)
{
	if (y < 0 || x < 0 || x >= width_ || y >= height_)
		return dummy_ = transparency_;
	return pixels_[width_ * y + x];
}

}
