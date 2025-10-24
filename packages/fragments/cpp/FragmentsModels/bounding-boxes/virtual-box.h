#ifndef VIRTUAL_BOX_H
#define VIRTUAL_BOX_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../model/model-types.h"

using namespace js;

// Forward declarations
class VirtualBox;

class VirtualBox {
public:
    VirtualBox(std::optional<js::number> position = std::nullopt, std::optional<DataBuffer> data = std::nullopt);
    virtual auto set(js::array<js::number> values);
    virtual auto get(js::any coord, js::any point);
    virtual void clone(VirtualBox box);
    virtual void combine(VirtualBox box1, VirtualBox box2);
private:
    std::shared_ptr<DataBuffer> _dataBuffer;
    js::number _dataPosition;
    auto _data;
    virtual auto setValue(js::number position, js::number value);
    virtual auto getDefaultData();
    virtual auto getPosition(js::any coord, js::any point);
    virtual auto save(js::any coord, js::any point, VirtualBox first, VirtualBox second);
};

#endif // VIRTUAL_BOX_H