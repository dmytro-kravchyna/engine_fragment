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

// Enum PolygonSize
namespace PolygonSize {
    extern const js::number four;
    extern const js::number three;
    js::string getName(js::number key);
}

// Interface ShellHoleData
class IShellHoleData {
public:
    virtual ~IShellHoleData() = default;
    // TODO: Interface members
};
// Interface DataSizes
class IDataSizes {
public:
    virtual ~IDataSizes() = default;
    // TODO: Interface members
};

#endif // TYPES_H