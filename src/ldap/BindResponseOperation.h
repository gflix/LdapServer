/*
 * BindResponseOperation.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_BINDRESPONSEOPERATION_H_
#define SRC_LDAP_BINDRESPONSEOPERATION_H_

#include <ldap/GenericOperation.h>

namespace Flix {

class BindResponseOperation: public GenericOperation {
public:
    BindResponseOperation();
    virtual ~BindResponseOperation();

    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_LDAP_BINDRESPONSEOPERATION_H_ */
