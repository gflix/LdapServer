/*
 * BindResponseOperation.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_BINDRESPONSEOPERATION_H_
#define SRC_LDAP_BINDRESPONSEOPERATION_H_

#include <ldap/GenericSimpleResponseOperation.h>

namespace Flix {

class BindResponseOperation: public GenericSimpleResponseOperation {
public:
    BindResponseOperation();
    virtual ~BindResponseOperation();

    virtual GenericAsnOneObject* getAsnOneObject(void) const;
    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_LDAP_BINDRESPONSEOPERATION_H_ */
