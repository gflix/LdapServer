/*
 * GenericAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_GENERICASNONEOBJECT_H_
#define SRC_GENERICASNONEOBJECT_H_

#include <ostream>
#include <vector>
#include <common/StreamBuffer.h>

namespace Flix {

enum class AsnOneObjectType {
    UNKNOWN,
    INTEGER,
    SEQUENCE,
    OCTET_STRING,
    LDAP_BIND,
};

enum class AsnOneDecodeStatus {
    UNKNOWN,
    NOT_SUPPORTED,
    INCOMPLETE,
    INVALID_TAG,
    INVALID_COMPOUND,
    OK,
};

class GenericAsnOneObject;

typedef std::vector<GenericAsnOneObject*> AsnOneObjects;

class GenericAsnOneObject {
public:
    GenericAsnOneObject(AsnOneObjectType type);
    virtual ~GenericAsnOneObject();

    AsnOneObjectType getType(void) const;
    virtual std::string dump(void) const = 0;

    static GenericAsnOneObject* decode(const StreamBuffer& buffer, ssize_t& consumedBytes, AsnOneDecodeStatus& decodeStatus);
    friend std::ostream& operator<<(std::ostream& stream, const GenericAsnOneObject& asnOneObject);

protected:
    AsnOneObjectType type;
    AsnOneObjects subObjects;

    bool decodeSequence(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    void appendSubObject(GenericAsnOneObject* subObject);
};

std::ostream& operator<<(std::ostream& stream, AsnOneDecodeStatus decodeStatus);

} /* namespace Flix */

#endif /* SRC_GENERICASNONEOBJECT_H_ */
