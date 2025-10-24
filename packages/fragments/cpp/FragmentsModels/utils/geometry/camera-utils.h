#ifndef CAMERA_UTILS_H
#define CAMERA_UTILS_H

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
#include "./planes-utils.h"

using namespace js;

// Forward declarations
class CameraUtils;

class CameraUtils {
public:
    CameraUtils() = default;
    auto transform(js::any input, js::any transform, auto result = std::make_shared<three::Frustum>());
    auto isIncluded(js::any box, js::array<unknown> ps);
    auto collides(js::any box, js::array<unknown> ps);
};

#endif // CAMERA_UTILS_H