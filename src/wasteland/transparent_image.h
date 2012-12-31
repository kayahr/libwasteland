/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_TRANSPARENT_IMAGE_H
#define LIBWASTELAND_TRANSPARENT_IMAGE_H

#include "image.h"

namespace wasteland
{

/**
 * Abstract base class for all transparent images.
 */
class transparent_image : public image
{
public:
    /**
     * Checks if the pixel at the specified position is transparent or not. If
     * the position is outside of the image then true (transparent) is
     * returned.
     *
     * @param x
     *            The X position of the pixel.
     * @param y
     *            The Y position of the pixel.
     * @return True if pixel is transparent, false if not.
     */
    virtual bool is_transparent(const coord x, const coord y) const = 0;

    /**
     * Enables or disables transparency of the pixel at the specified position.
     * If the position is outside of the image then this method does nothing.
     *
     * @param x
     *            The X position of the pixel.
     * @param y
     *            The Y position of the pixel.
     * @param transparent
     *            True to make the pixel transparent (Default), false to make
     *            it opaque.
     */
    virtual void set_transparent(const coord x, const coord y,
        const bool transparent = true) = 0;

    /**
     * Checks if the pixel at the specified position is opaque or not. If
     * the position is outside of the image then false (transparent) is
     * returned.
     *
     * @param x
     *            The X position of the pixel.
     * @param y
     *            The Y position of the pixel.
     * @return True if pixel is transparent, false if not.
     */
    virtual bool is_opaque(const coord x, const coord y) const;

    /**
     * Makes the pixel at the specified position opaque or transparent.
     * If the position is outside of the image then this method does nothing.
     *
     * @param x
     *            The X position of the pixel.
     * @param y
     *            The Y position of the pixel.
     * @param opaque
     *            True to make the pixel opaque (Default), false to make
     *            it transparent.
     */
    virtual void set_opaque(const coord x, const coord y,
        const bool opaque = true);
};

}

#endif
