/*
 * LdapBindAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAPBINDASNONEOBJECT_H_
#define SRC_LDAPBINDASNONEOBJECT_H_

#include <GenericAsnOneObject.h>

namespace Flix {

class LdapBindAsnOneObject: public GenericAsnOneObject {
public:
    LdapBindAsnOneObject();
    virtual ~LdapBindAsnOneObject();

    static LdapBindAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
};

} /* namespace Flix */

#endif /* SRC_LDAPBINDASNONEOBJECT_H_ */
