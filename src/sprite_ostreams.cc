/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "sprite_ostreams.h"

using std::ostream;

namespace wasteland
{

/**
 * Constructs a new sprite output stream container using the specified color
 * output stream and opacity output stream.
 *
 * @param color_stream
 *            The output stream to write color information from.
 * @param opacity_stream
 *            The output stream to write opacity information from.
 */
sprite_ostreams::sprite_ostreams(ostream &color_stream, ostream &opacity_stream) :
    color_stream(color_stream), opacity_stream(opacity_stream)
{
}

/**
 * Returns the output stream for writing color information.
 *
 * @return The color information output stream.
 */
ostream &sprite_ostreams::color() const
{
    return color_stream;
}

/**
 * Returns the output stream for writing opacity information.
 *
 * @return The opacity information output stream.
 */
ostream &sprite_ostreams::opacity() const
{
    return opacity_stream;
}

}
