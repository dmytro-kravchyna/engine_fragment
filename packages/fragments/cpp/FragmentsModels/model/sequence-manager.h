#ifndef SEQUENCE_MANAGER_H
#define SEQUENCE_MANAGER_H

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

using namespace js;

// Forward declarations
class SequenceManager;

class SequenceManager {
public:
    SequenceManager() = default;
    virtual auto getSequenced(FragmentsModel model, T result, js::array<U> fromItems, std::optional<js::any> inputs = std::nullopt);
};

#endif // SEQUENCE_MANAGER_H