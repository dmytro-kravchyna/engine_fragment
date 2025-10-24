#ifndef RAYCAST_HELPER_H
#define RAYCAST_HELPER_H

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
#include "../virtual-fragments-model.h"
#include "../../model/model-types.h"

using namespace js;

// Forward declarations
class RaycastHelper;

class RaycastHelper {
public:
    RaycastHelper() = default;
    virtual js::any raycast(VirtualFragmentsModel model, js::any ray, js::any frustum);
    virtual js::array<js::any> snapRaycast(VirtualFragmentsModel model, js::any ray, js::any frustum, js::array<SnappingClass> snappingClass);
    virtual js::array<js::number> rectangleRaycast(VirtualFragmentsModel model, js::any frustum, bool fullyIncluded);
};

#endif // RAYCAST_HELPER_H