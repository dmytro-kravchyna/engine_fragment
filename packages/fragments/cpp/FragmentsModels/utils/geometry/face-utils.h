#ifndef FACE_UTILS_H
#define FACE_UTILS_H

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
class FaceUtils;

class FaceUtils {
public:
    FaceUtils() = default;
    auto getEarcutDimensions(js::any normal);
};

#endif // FACE_UTILS_H