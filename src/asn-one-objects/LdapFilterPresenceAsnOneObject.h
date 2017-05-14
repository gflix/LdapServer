/*
 * LdapFilterPresenceAsnOneObject.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_ASN_ONE_OBJECTS_LDAPFILTERPRESENCEASNONEOBJECT_H_
#define SRC_ASN_ONE_OBJECTS_LDAPFILTERPRESENCEASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class LdapFilterPresenceAsnOneObject: public GenericAsnOneObject {
public:
    LdapFilterPresenceAsnOneObject();
    virtual ~LdapFilterPresenceAsnOneObject();

    const std::string& getValue(void) const;

    void setValue(const std::string& value);

    static LdapFilterPresenceAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static LdapFilterPresenceAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;

private:
    std::string value;
};

} /* namespace Flix */

#endif /* SRC_ASN_ONE_OBJECTS_LDAPFILTERPRESENCEASNONEOBJECT_H_ */
