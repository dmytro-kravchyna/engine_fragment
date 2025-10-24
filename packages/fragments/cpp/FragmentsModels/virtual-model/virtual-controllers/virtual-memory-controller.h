#ifndef VIRTUAL_MEMORY_CONTROLLER_H
#define VIRTUAL_MEMORY_CONTROLLER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include <lru-cache.h>
#include "../virtual-meshes.h"

using namespace js;

// Forward declarations
class VirtualMemoryController;

class VirtualMemoryController {
public:
    VirtualMemoryController() = default;
    auto get(js::number id);
    auto lockIn(AnyTileBasicData mesh);
    auto add(js::number id, AnyTileData mesh);
    auto delete(Iterable ids);
    auto updateMeshMemory;
    auto setCapacity(js::number value);
private:
    auto oneHundredMb;
    auto _meshes;
    js::number _capacity;
    js::array<js::string> _memoryAttributes;
    auto setupMeshes(std::optional<js::number> size = std::nullopt);
    js::number computeCapacity();
    auto getDataSetMemory(js::array<TileData> mesh);
    auto getSizeCalculationEvent();
};

#endif // VIRTUAL_MEMORY_CONTROLLER_H