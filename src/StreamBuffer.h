/*
 * StreamBuffer.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_STREAMBUFFER_H_
#define SRC_STREAMBUFFER_H_

#include <sys/types.h>
#include <vector>

namespace Flix {

class StreamBuffer: public std::vector<unsigned char> {
public:
    StreamBuffer();
    StreamBuffer(const StreamBuffer::const_iterator& a, const StreamBuffer::const_iterator& b);
    virtual ~StreamBuffer();

    ssize_t put(unsigned char* data, size_t elements);
    ssize_t get(unsigned char* data, size_t elements);
};

} /* namespace Flix */

#endif /* SRC_STREAMBUFFER_H_ */
