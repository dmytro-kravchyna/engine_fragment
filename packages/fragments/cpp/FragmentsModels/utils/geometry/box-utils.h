#ifndef BOX_UTILS_H
#define BOX_UTILS_H

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
class BoxUtils;

class BoxUtils {
public:
    BoxUtils() = default;
    auto getWidth(js::any box);
private:
    auto _temp;
};

#endif // BOX_UTILS_H