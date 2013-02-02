/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_PIC_ANIM_H
#define LIBWASTELAND_PIC_ANIM_H

#include <vector>
#include <iostream>
#include "pic_anim_frame.h"
#include "pic_anim_update.h"

namespace wasteland
{

/**
 * Container for the end animation of Wasteland (end.cpa file).
 *
 * The end animation of Wasteland consists of a huffman and vertical-xor
 * encoded base frame of 288x128 pixels and huffman encoded animation frames.
 * The animation does not support transparency.
 *
 * To read the animation simply create an instance of this class and then
 * stream the file into it:
 *
 * @code
 * pic_animation anim;
 * ifstream in("/path/end.cpa");
 * in >> anim;
 * @endcode
 *
 * Initially the animation is reset to the base frame. Use the
 * {@link next_frame} method to advance to the next frame after some delay
 * (See @link get_next_delay}).
 */
class pic_anim
{
    /**
     * Reads the end animation from the specified input stream.
     *
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream&, pic_anim&);

    /**
     * Writes the end animation to the specified output stream.
     *
     * @return The output streams.
     */
    friend std::ostream& operator<<(std::ostream&, const pic_anim&);

public:
    /**
     * Constructs a new empty PIC animation. All colors are set to black.
     */
    pic_anim();

    /**
     * Constructs a new end animation initialized with the data from
     * the specified end animation picture.
     *
     * @param other
     *            The end animation to copy the data from.
     */
    pic_anim(const pic_anim& other);

    /**
     * Destructs this end animation.
     */
    virtual ~pic_anim();

    /**
     * Copies the data of the given end animation to this end animation.
     *
     * @param other
     *            The end animation to copy the data from.
     */
    virtual pic_anim& operator=(const pic_anim& other);

    /**
     * Compares this end animation with the given end animation.
     *
     * @param other
     *            The other end animation to compare this one with.
     * @return True if end animations are equal, false if not.
     */
    virtual bool operator==(const pic_anim& other) const;

    /**
     * Compares this end animation with the given end animation.
     *
     * @param other
     *            The other end animation to compare this one with.
     * @return  False if end animations are equal, true if not.
     */
    virtual bool operator!=(const pic_anim& other) const;

    /**
     * Returns the base frame.
     *
     * @return The base frame.
     */
    virtual const pic_anim_frame& get_base_frame() const;

    /**
     * Returns the base frame.
     *
     * @return The base frame.
     */
    virtual pic_anim_frame& get_base_frame();

    /**
     * Returns the list of animation frame updates.
     *
     * @return The animation frame updates.
     */
    virtual const std::vector<pic_anim_update> &get_updates() const;

    /**
     * Returns the list of animation frame updates.
     *
     * @return The animation frame updates.
     */
    virtual std::vector<pic_anim_update> &get_updates();

    /**
     * Adds the specified update to the animation.
     *
     * @param update
     *            The update to add.
     */
    virtual void add_update(const pic_anim_update& update);

private:
    pic_anim_frame base_frame;
    std::vector<pic_anim_update> updates;
};

}

#endif
