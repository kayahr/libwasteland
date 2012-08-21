/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_TILE_H
#define LIBWASTELAND_TILE_H

#include <iostream>
#include "image.h"
#include "tile_reader.h"
#include "tile_writer.h"

namespace wasteland
{

/**
 * Container for a tile image (From one of the ALLHTDS files).
 *
 * Tile images are 16x16 images without transparency which are grouped into
 * tilesets. Multiple tilesets are stored in the two ALLHTDS files. To read
 * tiles you have to use the {@link tile_reader} like this:
 *
 * @code
 * tile img;
 * ifstream in("/path/allhtds1");
 * tile_reader reader(in);
 * while (reader)
 * {
 *     int tiles = reader.count_tiles();
 *     for (i = 0; i < tiles; i += 1)
 *     {
 *          reader >> img;
 *          // Do something with the tile image
 *     }
 * }
 * @endcode
 *
 * The while-loop iterates over all tilesets and the for-loop inside iterates
 * over all tiles in the tileset.
 *
 * The colors of all tile pixels can be read with the {@link get_color} method
 * and can be changed with the {@link set_color} method. So you can invert
 * a color for example like this:
 *
 * @code
 * img.set_color(x, y, img.get_color(x, y) ^ 0xf);
 * @endcode
 *
 * To write tiles back into a file you have to use a {@link tile_writer} like
 * this:
 *
 * @code
 * ofstream out("/path/newallhtds1");
 * tile_writer writer(out);
 * writer << tile_0_of_set_0;
 * writer << tile_1_of_set_0;
 * writer << tile_2_of_set_0;
 * writer.flush();
 * writer << tile_0_of_set_1;
 * writer << tile_1_of_set_1;
 * writer.flush();
 * @endcode
 *
 * So you simply have to stream all the tiles into the writer and call the
 * flush method every time you have completed a tile set.
 *
 * But be warned: Because of the huffman-compression of tiles the offsets of
 * the tilesets inside the file will be different to the original game files
 * so you can't simply create your own tilesets and use them in Wasteland.
 * You have to ensure that the compressed size of each tileset is smaller
 * or equal to the original tileset size and you have to write additional
 * fill bytes to the output stream to enforce the correct offsets.
 */
class tile: public image
{
    /**
     * Reads the tile image data from the specified tile reader.
     *
     * @return The tile reader.
     */
    friend tile_reader& operator>>(tile_reader&, tile&);

    /**
     * Writes the tile image data to the specified tile writer.
     *
     * @return The tile writer.
     */
    friend tile_writer& operator<<(tile_writer&, const tile&);

public:
    /**
     * Constructs a new empty tile image. All colors are set to black.
     */
    tile();

    /**
     * Constructs a new tile image initialized with the image data from
     * the specified tile image.
     *
     * @param other
     *            The image to copy the image data from.
     */
    tile(const tile& other);

    /**
     * Destructs this tile image.
     */
    virtual ~tile();

    /**
     * Copies the image data of the given tile to this tile.
     *
     * @param other
     *            The tile image to copy the image data from.
     */
    virtual tile& operator=(const tile& other);

    /**
     * Compares this tile image with the given tile image.
     *
     * @param other
     *            The other tile image to compare this one with.
     * @return True if tile images are equal, false if not.
     */
    virtual bool operator==(const tile& other) const;

    /**
     * Compares this tile image with the given tile image.
     *
     * @param other
     *            The other tile image to compare this one with.
     * @return  False if tile images are equal, true if not.
     */
    virtual bool operator!=(const tile& other) const;

    virtual size get_width() const;
    virtual size get_height() const;
    virtual color get_color(const coord x, const coord y) const;
    virtual void set_color(const coord x, const coord y, const color color);

private:
    uint8_t *data;
};

}

#endif
