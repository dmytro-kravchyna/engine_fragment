#ifndef GPU_H
#define GPU_H

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
class GPU;

class GPU {
public:
    GPU() = default;
    auto estimateCapacity();
private:
    auto capacityFactor;
};

#endif // GPU_H