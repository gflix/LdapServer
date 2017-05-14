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

#define PDU_CLASS_UNIVERSAL (0)
#define PDU_CLASS_APPLICATION (1)
#define PDU_CLASS_CONTEXT (2)

#define PDU_TYPE_UNIVERSAL_INTEGER (2)
#define PDU_TYPE_UNIVERSAL_OCTET_STRING (4)
#define PDU_TYPE_UNIVERSAL_ENUMERATED (10)
#define PDU_TYPE_UNIVERSAL_SEQUENCE (16)

#define PDU_TYPE_APPLICATION_LDAP_BIND_REQUEST (0)
#define PDU_TYPE_APPLICATION_LDAP_BIND_RESPONSE (1)

#define PDU_TYPE_CONTEXT_LDAP_BIND_CREDENTIAL (0)

namespace Flix {

enum class AsnOneObjectType {
    UNKNOWN,
    INTEGER,
    ENUMERATED,
    SEQUENCE,
    OCTET_STRING,
    LDAP_BIND_REQUEST,
    LDAP_BIND_RESPONSE
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
    bool isType(AsnOneObjectType requestedType) const;
    int getSubObjectCount(void) const;
    GenericAsnOneObject* getSubObject(int subObject) const;

    void appendSubObject(GenericAsnOneObject* subObject);

    virtual StreamBuffer serialize(void) const = 0;
    virtual std::string dump(void) const = 0;

    static GenericAsnOneObject* decode(const StreamBuffer& buffer, ssize_t& consumedBytes, AsnOneDecodeStatus& decodeStatus);
    friend std::ostream& operator<<(std::ostream& stream, const GenericAsnOneObject& asnOneObject);

protected:
    AsnOneObjectType type;
    AsnOneObjects subObjects;

    bool decodeSequence(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);

    StreamBuffer addAsnOneHeader(int pduClass, bool pduCombinedFlag, int pduType, const StreamBuffer& payload) const;
    StreamBuffer serializeSequence(int pduClass, int pduType) const;
};

std::ostream& operator<<(std::ostream& stream, AsnOneDecodeStatus decodeStatus);

} /* namespace Flix */

#endif /* SRC_GENERICASNONEOBJECT_H_ */
