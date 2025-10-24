#ifndef ITEM_ATTRIBUTES_H
#define ITEM_ATTRIBUTES_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "./model-types.h"

using namespace js;

// Forward declarations
class ItemAttributes;

class ItemAttributes : public Map {
public:
    js::typed::Nullable<Map> tracker;
    js::number localId;
    ItemAttributes(js::number localId, std::optional<js::any> iterable = std::nullopt);
    std::shared_ptr<std::function<bool(js::string, AttributeData)>> guard;
    auto set(js::string key, AttributeData attr) override;
    auto setValue(js::string key, js::any value) override;
    auto setType(js::string key, js::number type) override;
    auto delete(js::string key) override;
    auto getValue(js::string key) override;
    auto getType(js::string key) override;
};

#endif // ITEM_ATTRIBUTES_H