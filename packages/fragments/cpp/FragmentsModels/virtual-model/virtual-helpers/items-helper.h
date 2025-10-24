#ifndef ITEMS_HELPER_H
#define ITEMS_HELPER_H

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
class ItemsHelper;

class ItemsHelper {
public:
    ItemsHelper() = default;
    virtual auto traverse(VirtualFragmentsModel model, js::array<js::number> itemIds, std::function<void(js::number, js::number)> onItem);
    virtual auto getItemsByConfig(VirtualFragmentsModel model, std::function<bool(js::number)> condition);
private:
    virtual auto traverseItems(js::array<js::number> itemIds, std::function<void(js::number, js::number)> onItem);
    virtual auto traverseAllItems(VirtualFragmentsModel model, std::function<void(js::number, js::number)> onItem);
};

#endif // ITEMS_HELPER_H