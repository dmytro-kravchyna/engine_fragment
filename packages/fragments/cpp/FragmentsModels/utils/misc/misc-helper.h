#ifndef MISC_HELPER_H
#define MISC_HELPER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"

using namespace js;

// Forward declarations
class MiscHelper;

class MiscHelper {
public:
    MiscHelper() = default;
    auto fixNumber(js::number value);
    auto forEach(js::any items, ForEachCallback callback);
};

#endif // MISC_HELPER_H