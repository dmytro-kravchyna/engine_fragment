#ifndef INT_HELPER_H
#define INT_HELPER_H

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
class IntHelper;

class IntHelper {
public:
    IntHelper() = default;
    auto check(js::number data);
private:
    auto _max;
    auto _min;
};

#endif // INT_HELPER_H