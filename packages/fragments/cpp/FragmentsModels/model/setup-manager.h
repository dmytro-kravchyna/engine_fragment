#ifndef SETUP_MANAGER_H
#define SETUP_MANAGER_H

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
#include <three.h>
#include "./model-types.h"
#include "./fragments-model.h"

using namespace js;

// Forward declarations
class SetupManager;

class SetupManager {
public:
    SetupManager() = default;
    virtual auto setup(FragmentsModel model, js::any bbox, ArrayBuffer modelData, std::optional<bool> raw = std::nullopt, std::optional<VirtualModelConfig> config = std::nullopt);
private:
    virtual auto formatModelData(ArrayBuffer modelData);
    virtual auto updateBox(js::any bbox, js::any result);
    virtual auto getCreateModelMessage(FragmentsModel model, ArrayBuffer modelData, js::typed::Nullable<bool> raw, js::typed::Nullable<VirtualModelConfig> config);
};

#endif // SETUP_MANAGER_H