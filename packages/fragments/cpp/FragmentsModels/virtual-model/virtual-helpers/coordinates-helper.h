#ifndef COORDINATES_HELPER_H
#define COORDINATES_HELPER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../virtual-fragments-model.h"

using namespace js;

// Forward declarations
class CoordinatesHelper;

class CoordinatesHelper {
public:
    CoordinatesHelper() = default;
    virtual auto getPositions(VirtualFragmentsModel model, js::array<js::number> localIds);
    virtual js::array<js::number> getCoordinates(VirtualFragmentsModel model);
};

#endif // COORDINATES_HELPER_H