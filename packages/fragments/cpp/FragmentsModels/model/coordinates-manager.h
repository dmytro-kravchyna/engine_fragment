#ifndef COORDINATES_MANAGER_H
#define COORDINATES_MANAGER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "runtime/async.h"
#include <three.h>
#include "./fragments-model.h"

using namespace js;

// Forward declarations
class CoordinatesManager;

class CoordinatesManager {
public:
    CoordinatesManager() = default;
    virtual auto getCoordinationMatrix(FragmentsModel model);
    virtual auto getCoordinates(FragmentsModel model);
    virtual auto getPositions(FragmentsModel model, std::optional<js::array<js::number>> localIds = std::nullopt);
private:
    auto _coordinationMatrices;
    virtual auto getAbsolutePositions(js::array<js::any> result, FragmentsModel model);
};

#endif // COORDINATES_MANAGER_H