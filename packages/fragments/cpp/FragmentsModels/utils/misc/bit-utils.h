#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../../model/model-types.h"

using namespace js;

// Forward declarations
class BitUtils;

class BitUtils {
public:
    BitUtils() = default;
    auto check(DataBuffer data, js::number id, ItemConfigClass config);
    void apply(DataBuffer data, js::number id, ItemConfigClass config, bool value);
    auto checkMemory(js::number id);
private:
    auto get(js::number value);
};

#endif // BIT_UTILS_H