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
#include <three.h>
#include "../../../../../Schema.h"

using namespace js;

// Interface LinkPoint
class ILinkPoint {
public:
    virtual ~ILinkPoint() = default;
    // TODO: Interface members
};

#endif // TYPES_H