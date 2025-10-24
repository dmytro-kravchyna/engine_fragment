#ifndef DATA_MAP_H
#define DATA_MAP_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "./event.h"

using namespace js;

// Forward declarations
class DataMap;

template<typename K, typename V>
class DataMap : public Map {
public:
    auto onItemSet;
    auto onItemUpdated;
    auto onItemDeleted;
    auto onBeforeDelete;
    auto onCleared;
    DataMap(std::optional<js::any> iterable = std::nullopt);
    auto clear() override;
    auto set(K key, V value) override;
    std::shared_ptr<std::function<bool(K, V)>> guard;
    auto delete(K key) override;
    auto getKey(V item) override;
    auto update(V item) override;
    auto deleteIf(std::function<bool(V, K)> predicate) override;
    auto replaceKey(K oldKey, K newKey, auto fullReplace = false) override;
    auto dispose() override;
};

#endif // DATA_MAP_H