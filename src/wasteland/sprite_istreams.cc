/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "sprite_istreams.h"

using std::istream;

namespace wasteland
{

/**
 * Constructs a new sprite input stream container using the specified color
 * input stream and opacity input stream.
 *
 * @param color_stream
 *            The input stream to read color information from.
 * @param opacity_stream
 *            The input stream to read opacity information from.
 */
sprite_istreams::sprite_istreams(istream &color_stream, istream &opacity_stream) :
    color_stream(color_stream), opacity_stream(opacity_stream)
{
}

/**
 * Casts this object to a boolean so it can be used for EOF checks.
 */
sprite_istreams::operator bool() const
{
    return (bool) color_stream && (bool) opacity_stream;
}

/**
 * Returns the input stream for reading color information.
 *
 * @return The color information input stream.
 */
istream &sprite_istreams::color() const
{
    return color_stream;
}

/**
 * Returns the input stream for reading opacity information.
 *
 * @return The opacity information input stream.
 */
istream &sprite_istreams::opacity() const
{
    return opacity_stream;
}

}
