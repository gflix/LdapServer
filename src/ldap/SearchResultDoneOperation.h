/*
 * SearchResultDoneOperation.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_SEARCHRESULTDONEOPERATION_H_
#define SRC_LDAP_SEARCHRESULTDONEOPERATION_H_

#include <ldap/GenericSimpleResponseOperation.h>

namespace Flix {

class SearchResultDoneOperation: public GenericSimpleResponseOperation {
public:
    SearchResultDoneOperation();
    virtual ~SearchResultDoneOperation();

    virtual GenericAsnOneObject* getAsnOneObject(void) const;
    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_LDAP_SEARCHRESULTDONEOPERATION_H_ */
