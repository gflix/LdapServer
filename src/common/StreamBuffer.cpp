/*
 * StreamBuffer.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <common/StreamBuffer.h>

namespace Flix {

StreamBuffer::StreamBuffer()
{
}

StreamBuffer::StreamBuffer(const StreamBuffer::const_iterator& a, const StreamBuffer::const_iterator& b):
    std::vector<unsigned char>(a, b)
{
}

StreamBuffer::~StreamBuffer()
{
}

ssize_t StreamBuffer::put(unsigned char* data, size_t elements)
{
    if (!data) {
        return -1;
    }

    ssize_t elementsWritten = 0;
    while (elements > 0) {
        push_back(*data);
        ++data;
        --elements;
        ++elementsWritten;
    }
    return elementsWritten;
}

ssize_t StreamBuffer::get(unsigned char* data, size_t elements)
{
    if (!data) {
        return -1;
    }

    ssize_t elementsRetreived = 0;
    auto element = begin();
    while (elements > 0 && element != end()) {
        *data = *element;
        ++data;
        --elements;
        ++element;
        ++elementsRetreived;
    }
    erase(begin(), element);

    return elementsRetreived;
}

} /* namespace Flix */
