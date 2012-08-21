/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_EXCEPTIONS_H
#define LIBWASTELAND_EXCEPTIONS_H

#include <stdexcept>

namespace wasteland
{

/**
 * Base class for errors thrown by libwasteland.
 */
class error: public std::runtime_error
{
public:
    /**
     * Constructs a new error with the specified error message.
     *
     * @param message
     *            The error message.
     */
    explicit error(const std::string &message) : runtime_error(message) {};
};

/**
 * Base class for I/O errors thrown by libwasteland.
 */
class io_error: public error
{
public:
    /**
     * Constructs a new I/O error with the specified error message.
     *
     * @param message
     *            The error message.
     */
    explicit io_error(const std::string &message) : error(message) {};
};

/**
 * Base class for huffman encoding/decoding problems.
 */
class huffman_error: public io_error
{
public:
    /**
     * Constructs a new huffman error with the specified error message.
     *
     * @param message
     *            The error message.
     */
    explicit huffman_error(const std::string &message) : io_error(message) {};
};

/**
 * Error thrown when a huffman enoding/decoding error occurred.
 */
class eos_error: public io_error
{
public:
    /**
     * Constructs a new end-of-stream error with the specified error
     * message.
     *
     * @param message
     *            Optional error message. Defaults to a fixed message.
     */
    explicit eos_error(const std::string &message
        = "Unexpected end of stream") : io_error(message) {};
};

}

#endif
