#ifndef VISIBILITY_MANAGER_H
#define VISIBILITY_MANAGER_H

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
#include "./fragments-model.h"

using namespace js;

// Forward declarations
class VisibilityManager;

class VisibilityManager {
public:
    VisibilityManager() = default;
    virtual auto resetVisible(FragmentsModel model);
    virtual auto getItemsByVisibility(FragmentsModel model, bool visible);
    virtual auto getVisible(FragmentsModel model, js::array<js::number> localIds);
};

#endif // VISIBILITY_MANAGER_H