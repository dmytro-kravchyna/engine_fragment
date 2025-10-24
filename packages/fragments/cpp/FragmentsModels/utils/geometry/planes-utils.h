#ifndef PLANES_UTILS_H
#define PLANES_UTILS_H

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

using namespace js;

// Forward declarations
class PlanesUtils;

class PlanesUtils {
public:
    PlanesUtils() = default;
    auto containedInParallelPlanes(js::array<unknown> ps, js::any point);
    auto collides(js::any box, js::array<unknown> ps, bool included);
private:
    auto tempPoint;
    auto dimensions;
    auto getPointDistance(js::any plane, bool included, js::any box);
};

#endif // PLANES_UTILS_H