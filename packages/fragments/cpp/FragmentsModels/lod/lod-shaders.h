#ifndef LOD_SHADERS_H
#define LOD_SHADERS_H

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

// Forward declarations
class LodShaders;

class LodShaders {
public:
    LodShaders() = default;
    auto vertex;
    auto fragment;
};

#endif // LOD_SHADERS_H