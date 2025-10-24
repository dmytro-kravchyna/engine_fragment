#ifndef HIGHLIGHT_HELPER_H
#define HIGHLIGHT_HELPER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../../model/model-types.h"
#include "../virtual-fragments-model.h"

using namespace js;

// Forward declarations
class HighlightHelper;

class HighlightHelper {
public:
    HighlightHelper() = default;
    virtual void resetHighlight(VirtualFragmentsModel model, js::array<js::number> items);
    virtual auto getHighlight(VirtualFragmentsModel model, js::array<js::number> localIds);
    virtual auto getHighlightItems(VirtualFragmentsModel model);
    virtual auto highlight(VirtualFragmentsModel model, js::array<js::number> items, MaterialDefinition material);
private:
    auto _highlightProps;
    virtual auto getFetchEvent(VirtualFragmentsModel model, js::array<MaterialDefinition> found);
    virtual auto setHighlightProperty(MaterialDefinition newHigh, MaterialDefinition pastHigh, js::string key);
    virtual auto getNewHighFromPast(VirtualFragmentsModel model, js::number past, MaterialDefinition highlightMaterial);
    virtual auto getCheckEvent(VirtualFragmentsModel model, MaterialDefinition highlightMaterial, js::array<MaterialDefinition> materials);
    virtual auto getCreateEvent(VirtualFragmentsModel model, js::array<js::number> ids);
    virtual auto resetHighlightForItems(js::array<js::number> itemIds, VirtualFragmentsModel model);
};

#endif // HIGHLIGHT_HELPER_H