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

// Interface ProgressData
class IProgressData {
public:
    virtual ~IProgressData() = default;
    // TODO: Interface members
};
// Interface ProcessData
class IProcessData {
public:
    virtual ~IProcessData() = default;
    // TODO: Interface members
};

#endif // TYPES_H