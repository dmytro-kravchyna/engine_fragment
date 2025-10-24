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
#include "../../model/model-types.h"
#include "../../utils.h"
#include <cmath>

using namespace js;

extern const js::number normalizationValue;
// Const enum LodClass
namespace LodClass {
    constexpr int NONE = 0;
    constexpr int AABB = 1;
    constexpr int CUSTOM = 2;
}

// Interface TileBasicData
class ITileBasicData {
public:
    virtual ~ITileBasicData() = default;
    // TODO: Interface members
};
// Interface TileData
class ITileData {
public:
    virtual ~ITileData() = default;
    // TODO: Interface members
};

#endif // TYPES_H