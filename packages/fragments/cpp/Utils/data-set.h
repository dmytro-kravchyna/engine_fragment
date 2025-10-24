#ifndef DATA_SET_H
#define DATA_SET_H

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
class DataSet;

template<typename T>
class DataSet : public Set {
public:
    auto onUpdated;
    auto onItemAdded;
    auto onBeforeDelete;
    auto onItemDeleted;
    auto onCleared;
    DataSet(std::optional<js::typed::Nullable<Iterable>> iterable = std::nullopt);
    auto clear() override;
    auto add(Args... value) override;
    std::shared_ptr<std::function<bool(T)>> guard;
    auto delete(T value) override;
    auto deleteIf(std::function<bool(T)> predicate) override;
    auto getIndex(T item) override;
    auto dispose() override;
};

#endif // DATA_SET_H