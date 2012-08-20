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
    explicit error(const std::string &message) : runtime_error(message) {};
};

/**
 * Base class for I/O errors thrown by libwasteland.
 */
class io_error: public error
{
public:
    explicit io_error(const std::string &message) : error(message) {};
};

/**
 * Base class for huffman encoding/decoding problems.
 */
class huffman_error: public io_error
{
public:
    explicit huffman_error(const std::string &message) : io_error(message) {};
};

/**
 * Error thrown when a huffman enoding/decoding error occurred.
 */
class huffman_eos_error: public huffman_error
{
public:
    explicit huffman_eos_error(const std::string &message
        = "Unexpected end of stream") : huffman_error(message) {};
};

}

#endif
