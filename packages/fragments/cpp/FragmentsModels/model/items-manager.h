#ifndef ITEMS_MANAGER_H
#define ITEMS_MANAGER_H

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
#include "./model-types.h"
#include "./fragments-model.h"
#include "./item.h"

using namespace js;

// Forward declarations
class ItemsManager;

class ItemsManager {
public:
    ItemsManager() = default;
    virtual auto getItem(FragmentsModel model, Identifier id);
    virtual auto getItemsData(FragmentsModel model, js::array<Identifier> ids, std::optional<Partial> config = std::nullopt);
    virtual auto getItemsChildren(FragmentsModel model, js::array<Identifier> ids);
};

#endif // ITEMS_MANAGER_H