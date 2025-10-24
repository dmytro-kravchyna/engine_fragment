#ifndef ITEM_RELATIONS_H
#define ITEM_RELATIONS_H

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
#include "./item.h"
#include "./model-types.h"

using namespace js;

// Forward declarations
class ItemRelations;

class ItemRelations : public Map {
public:
    js::typed::Nullable<Map> tracker;
    js::number localId;
    ItemRelations(js::number localId, std::optional<js::any> iterable = std::nullopt);
    std::shared_ptr<std::function<bool(js::string, Set)>> guard;
    auto set(js::string key, Set value) override;
    auto add(js::string key, js::number item) override;
    auto remove(js::string key, js::number item) override;
    auto delete(js::string key) override;
    js::typed::Nullable<std::function<std::future<js::array<Item>>(js::array<js::number>, bool)>> onItemsRequested;
    auto getItems(js::string key) override;
};

#endif // ITEM_RELATIONS_H