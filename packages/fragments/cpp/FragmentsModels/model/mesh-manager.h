#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include <three.h>
#include "./material-manager.h"
#include "./model-types.h"
#include "./fragments-model.h"
#include "../../../Utils.h"
#include "./requests-manager.h"
#include "./lod-manager.h"

using namespace js;

// Forward declarations
class MeshManager;

class MeshManager {
public:
    auto list;
    auto materials;
    auto lod;
    auto requests;
    MeshManager(std::function<void()> onUpdate);
    virtual auto forceUpdateFinish(auto rate = js::number(200));
    virtual auto update();
private:
    auto updateThreshold;
    auto _updateFinished;
    std::shared_ptr<std::function<void()>> _onUpdate;
    virtual auto setTileData(BIMMesh mesh, js::any request);
    virtual auto processTileRequest(js::any request);
    virtual auto createMesh(js::any request);
    virtual auto setupBoundings(BIMMesh mesh, js::any aabb);
    virtual BIMMesh create(js::any request);
    virtual auto updateStatus(BIMMesh mesh, js::any request);
    virtual auto cleanAttributeMemory(js::any geometry, js::string name);
    virtual auto setPositions(js::any positions, js::any geometry);
    virtual auto setFaceIds(js::any faceIds, js::any geometry);
    virtual auto setIndex(js::any geometry, js::any indices);
    virtual auto setNormals(js::any normals, js::any geometry);
    virtual auto setItemIds(js::any itemIds, js::any geometry);
    virtual auto deleteAttribute(js::any _geometry);
    virtual auto setMeshData(BIMMesh mesh, js::any tileId, js::any itemId, js::any matrix);
};

#endif // MESH_MANAGER_H