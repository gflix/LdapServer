/*
 * StreamBuffer.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <iomanip>
#include <common/Log.h>
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
        std::vector<unsigned char>::push_back(*data);
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

void StreamBuffer::push_back(const StreamBuffer& elements)
{
    insert(this->end(), elements.cbegin(), elements.cend());
}

void StreamBuffer::push_back(unsigned char value)
{
    std::vector<unsigned char>::push_back(value);
}

void StreamBuffer::dump(void) const
{
    std::stringstream dumpStream;

    bool firstElement = true;
    for (auto element = cbegin(); element != cend(); ++element) {
        if (firstElement) {
            firstElement = false;
        } else {
            dumpStream << ", ";
        }
        dumpStream << std::hex << std::setw(2) << std::setfill('0') << (int) *element;
    }

    LOG_DEBUG("StreamBuffer[" << dumpStream.str() << "]");
}

} /* namespace Flix */
