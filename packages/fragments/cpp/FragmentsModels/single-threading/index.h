#ifndef INDEX_H
#define INDEX_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include <pako.h>
#include "../model.h"
#include "../virtual-model/virtual-fragments-model.h"

using namespace js;

// Forward declarations
class SingleThreadedFragmentsModel;

class SingleThreadedFragmentsModel {
public:
    SingleThreadedFragmentsModel(js::string modelId, js::Uint8Array modelData, auto raw = false);
    virtual auto dispose();
    virtual auto getSpatialStructure();
    virtual auto getLocalIdsByGuids(js::array<js::string> guids);
    virtual auto getCategories();
    virtual auto getItemsWithGeometry();
    virtual auto getMetadata();
    virtual auto getGuidsByLocalIds(js::array<js::number> localIds);
    virtual auto getBuffer(auto raw = false);
    virtual auto getItemsOfCategories(js::array<RegExp> categories);
    virtual auto getMaxLocalId();
    virtual auto getItemsChildren(js::array<Identifier> ids);
    virtual auto getItemsData(js::array<js::number> ids, std::optional<Partial> config = std::nullopt);
    virtual auto getPositions(js::array<js::number> localIds);
    virtual auto getCoordinates();
private:
    js::string _modelId;
    std::shared_ptr<VirtualFragmentsModel> _virtualModel;
};

#endif // INDEX_H