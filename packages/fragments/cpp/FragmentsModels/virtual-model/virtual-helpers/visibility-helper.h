#ifndef VISIBILITY_HELPER_H
#define VISIBILITY_HELPER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../virtual-fragments-model.h"

using namespace js;

// Forward declarations
class VisibilityHelper;

class VisibilityHelper {
public:
    VisibilityHelper() = default;
    virtual auto resetVisible(VirtualFragmentsModel model);
    virtual auto getVisible(VirtualFragmentsModel model, js::array<js::number> items);
    virtual auto getItemsByVisibility(VirtualFragmentsModel model, bool visible);
    virtual auto toggleVisible(VirtualFragmentsModel model, js::array<js::number> localIds);
    virtual void setVisible(VirtualFragmentsModel model, js::array<js::number> localIds, bool visible);
private:
    virtual auto getSetEvent(VirtualFragmentsModel model, bool visible);
    virtual auto getVisibleCondition(VirtualFragmentsModel model, bool visible);
    virtual auto getToggleEvent(VirtualFragmentsModel model);
};

#endif // VISIBILITY_HELPER_H