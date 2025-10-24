#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

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
#include "./alignments-manager.h"
#include "./fragments-model.h"
#include "./mesh-manager.h"

using namespace js;

// Forward declarations
class DataManager;

class DataManager {
public:
    DataManager() = default;
    virtual auto dispose(FragmentsModel model, MeshManager meshes, AlignmentsManager alignments);
    virtual auto getBuffer(FragmentsModel model, bool raw);
    virtual auto getCategories(FragmentsModel model);
    virtual auto getMaxLocalId(FragmentsModel model);
    virtual auto getLocalIdsByGuids(FragmentsModel model, js::array<js::string> guids);
    virtual auto getSpatialStructure(FragmentsModel model);
    virtual auto getItemsWithGeometry(FragmentsModel model);
    virtual auto getItemsWithGeometryCategories(FragmentsModel model);
    virtual auto getItemsIdsWithGeometry(FragmentsModel model);
    virtual auto getItemsOfCategories(FragmentsModel model, js::array<RegExp> categories);
    virtual auto getItemsByQuery(FragmentsModel model, ItemsQueryParams params);
    virtual auto getMetadata(FragmentsModel model);
    virtual auto getGuidsByLocalIds(FragmentsModel model, js::array<js::number> localIds);
private:
    virtual auto requestModelDelete(FragmentsModel model);
    virtual auto deleteAllTiles(FragmentsModel model);
};

#endif // DATA_MANAGER_H