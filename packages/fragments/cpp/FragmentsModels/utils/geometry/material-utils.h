#ifndef MATERIAL_UTILS_H
#define MATERIAL_UTILS_H

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
#include "../../../../Schema.h"
#include "../../model/model-types.h"

using namespace js;

// Forward declarations
class MaterialUtils;

class MaterialUtils {
public:
    MaterialUtils() = default;
    auto isSame(MaterialDefinition a, MaterialDefinition b);
private:
    bool checkSame(js::any a, js::any b, js::any fallback);
    auto checkSameColor(js::any a, js::any b);
};

#endif // MATERIAL_UTILS_H