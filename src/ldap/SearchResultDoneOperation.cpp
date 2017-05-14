/*
 * SearchResultDoneOperation.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <asn-one-objects/LdapSearchResultDoneAsnOneObject.h>
#include <ldap/SearchResultDoneOperation.h>

namespace Flix {

SearchResultDoneOperation::SearchResultDoneOperation():
    GenericSimpleResponseOperation(OperationType::SEARCH_RESULT_DONE)
{
}

SearchResultDoneOperation::~SearchResultDoneOperation()
{
}

GenericAsnOneObject* SearchResultDoneOperation::getAsnOneObject(void) const
{
    return GenericSimpleResponseOperation::getAsnOneObject(new LdapSearchResultDoneAsnOneObject());
}

std::string SearchResultDoneOperation::dump(void) const
{
    return GenericSimpleResponseOperation::dump("SearchResultDone");
}

} /* namespace Flix */
