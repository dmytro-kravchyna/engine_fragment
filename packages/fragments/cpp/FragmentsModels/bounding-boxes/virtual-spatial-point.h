#ifndef VIRTUAL_SPATIAL_POINT_H
#define VIRTUAL_SPATIAL_POINT_H

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
#include "./virtual-box.h"

using namespace js;

// Forward declarations
class VirtualSpatialPoint;

class VirtualSpatialPoint {
public:
    std::shared_ptr<VirtualBox> box;
    auto data;
    VirtualSpatialPoint(js::number position, DataBuffer data);
    virtual auto transform(js::number size, VirtualBox box, bool group);
private:
    auto _data;
};

#endif // VIRTUAL_SPATIAL_POINT_H