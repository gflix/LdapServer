/*
 * SearchRequestOperation.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <cassert>
#include <sstream>
#include <asn-one-objects/OctetStringAsnOneObject.h>
#include <ldap/SearchRequestOperation.h>

namespace Flix {

SearchRequestOperation::SearchRequestOperation():
    GenericOperation(OperationType::SEARCH_REQUEST),
    searchScope(SearchScope::BASE),
    dereferenceAliases(DereferenceAliases::NEVER),
    sizeLimit(0),
    timeLimit(0),
    onlyTypesFlag(false)
{
}

SearchRequestOperation::~SearchRequestOperation()
{
}

const std::string& SearchRequestOperation::getBaseDn(void) const
{
    return baseDn;
}

SearchScope SearchRequestOperation::getSearchScope(void) const
{
    return searchScope;
}

DereferenceAliases SearchRequestOperation::getDereferenceAliases(void) const
{
    return dereferenceAliases;
}

int SearchRequestOperation::getSizeLimit(void) const
{
    return sizeLimit;
}

int SearchRequestOperation::getTimeLimit(void) const
{
    return timeLimit;
}

bool SearchRequestOperation::getOnlyTypesFlag(void) const
{
    return onlyTypesFlag;
}

void SearchRequestOperation::setBaseDn(const std::string& baseDn)
{
    this->baseDn = baseDn;
}

void SearchRequestOperation::setSearchScope(SearchScope searchScope)
{
    this->searchScope = searchScope;
}

void SearchRequestOperation::setDereferenceAliases(DereferenceAliases dereferenceAliases)
{
    this->dereferenceAliases = dereferenceAliases;
}

void SearchRequestOperation::setSizeLimit(int sizeLimit)
{
    this->sizeLimit = sizeLimit;
}

void SearchRequestOperation::setTimeLimit(int timeLimit)
{
    this->timeLimit = timeLimit;
}

void SearchRequestOperation::setOnlyTypesFlag(bool onlyTypesFlag)
{
    this->onlyTypesFlag = onlyTypesFlag;
}

GenericOperation* SearchRequestOperation::execute(void) const
{
    return nullptr;
}

GenericAsnOneObject* SearchRequestOperation::getAsnOneObject(void) const
{
    // Not supported
    assert(false);
    return nullptr;
}

std::string SearchRequestOperation::dump(void) const
{
    std::stringstream dumpedOperation;

    dumpedOperation << "SearchRequestOperation(baseDn=\"" <<
        baseDn << "\"" << ")";

    return dumpedOperation.str();
}

SearchRequestOperation* SearchRequestOperation::fromAsnOneObject(LdapSearchRequestAsnOneObject* asnOneObject)
{
    if (!asnOneObject || !asnOneObject->isValid()) {
        return nullptr;
    }

    SearchRequestOperation* operation = new SearchRequestOperation();
    operation->setBaseDn(OctetStringAsnOneObject::castObject(asnOneObject->getSubObject(0))->getValue());
//    operation->setAuthenticationDn(OctetStringAsnOneObject::castObject(asnOneObject->getSubObject(1))->getValue());
//    operation->setPassword(OctetStringAsnOneObject::castObject(asnOneObject->getSubObject(2))->getValue());

    return operation;
}

} /* namespace Flix */
