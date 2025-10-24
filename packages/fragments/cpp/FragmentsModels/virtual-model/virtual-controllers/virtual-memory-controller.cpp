#include "index_generated.h"
#include "virtual-memory-controller.h"

using namespace js;

auto VirtualMemoryController::get(js::number id) {
    {
            return this->_meshes.get(id);
    }
}

auto VirtualMemoryController::lockIn(AnyTileBasicData mesh) {
    {
            js::Object::seal(mesh);
    }
}

auto VirtualMemoryController::add(js::number id, AnyTileData mesh) {
    {
            this->_meshes.set(id, mesh);
    }
}

auto VirtualMemoryController::delete(Iterable ids) {
    {
            for (const auto& id : ids) {
                        {
                                        this->_meshes.delete(id);
                        }
            }
    }
}

auto VirtualMemoryController::setCapacity(js::number value) {
    {
            if (value === this->_capacity) {
                        return;
            }
            this->_meshes.clear();
            this->_meshes = this->setupMeshes(value);
            this->_capacity = value;
    }
}

auto VirtualMemoryController::setupMeshes(std::optional<js::number> size) {
    {
            const js::any maxSize = js::Math::max((size.has_value() ? size : this->computeCapacity()), js::number(1));
            const js::any sizeCalculation = this->getSizeCalculationEvent();
            const js::any lruInput = []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("maxSize", maxSize);
                  obj_temp_0.set("sizeCalculation", sizeCalculation);
                  return js::any(obj_temp_0);
                }();
            return std::make_shared<LRUCache>(lruInput);
    }
}

js::number VirtualMemoryController::computeCapacity() {
    {
            const js::any deviceMemory = (js::null ? js::null : js::null);
            const js::number fallbackMemory = js::number(2);
            const js::any baseMemory = (js::null ? js::null : js::null);
            const js::number result = (this->oneHundredMb * baseMemory);
            return js::Math::trunc(result);
    }
}

auto VirtualMemoryController::getDataSetMemory(js::array<TileData> mesh) {
    {
            js::number usedMemory = js::number(0);
            for (const auto& item : mesh) {
                        {
                                        usedMemory += item->usedMemory;
                        }
            }
            return js::Math::max(usedMemory, js::number(1));
    }
}

auto VirtualMemoryController::getSizeCalculationEvent() {
    {
            return [&](AnyTileData mesh) -> auto {
            if (!js::array.isArray(mesh)) {
                        {
                                        return js::Math::max(mesh["usedMemory"], js::number(1));
                        }
            }
            return this->getDataSetMemory(mesh);
            };
    }
}
