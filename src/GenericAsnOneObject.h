/*
 * GenericAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_GENERICASNONEOBJECT_H_
#define SRC_GENERICASNONEOBJECT_H_

#include <list>
#include <ostream>
#include <StreamBuffer.h>

namespace Flix {

enum class AsnOneObjectType {
    UNKNOWN,
    SEQUENCE,
    INTEGER,
    LDAP_BIND,
};

enum class AsnOneDecodeStatus {
    UNKNOWN,
    NOT_SUPPORTED,
    INCOMPLETE,
    INVALID_TAG,
    OK,
};

class GenericAsnOneObject;

typedef std::list<GenericAsnOneObject*> AsnOneObjects;

class GenericAsnOneObject {
public:
    GenericAsnOneObject(AsnOneObjectType type);
    virtual ~GenericAsnOneObject();

    static GenericAsnOneObject* decode(const StreamBuffer& buffer, ssize_t& consumedBytes, AsnOneDecodeStatus& decodeStatus);

protected:
    AsnOneObjectType type;
    AsnOneObjects subObjects;

    void appendSubObject(GenericAsnOneObject* subObject);
};

std::ostream& operator<<(std::ostream& stream, AsnOneDecodeStatus decodeStatus);

} /* namespace Flix */

#endif /* SRC_GENERICASNONEOBJECT_H_ */
