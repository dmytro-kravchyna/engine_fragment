#ifndef TYPES_H
#define TYPES_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"

using namespace js;

// Interface ReferenceAttr
class IReferenceAttr {
public:
    virtual ~IReferenceAttr() = default;
    // TODO: Interface members
};
// Interface AttrValue
class IAttrValue {
public:
    virtual ~IAttrValue() = default;
    // TODO: Interface members
};
// Interface RawEntityAttrs
class IRawEntityAttrs {
public:
    virtual ~IRawEntityAttrs() = default;
    // TODO: Interface members
};

#endif // TYPES_H