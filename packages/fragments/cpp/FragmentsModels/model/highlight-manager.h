#ifndef HIGHLIGHT_MANAGER_H
#define HIGHLIGHT_MANAGER_H

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
#include "./material-manager.h"

using namespace js;

// Forward declarations
class HighlightManager;

class HighlightManager {
public:
    HighlightManager() = default;
    virtual auto getHighlight(FragmentsModel model, std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto highlight(FragmentsModel model, js::typed::Nullable<js::array<js::number>> localIds, MaterialDefinition highlightMaterial);
    virtual auto getHighlightItemIds(FragmentsModel model);
    virtual auto resetHighlight(FragmentsModel model, std::optional<js::array<js::number>> localIds = std::nullopt);
};

#endif // HIGHLIGHT_MANAGER_H