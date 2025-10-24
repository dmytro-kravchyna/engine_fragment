#ifndef VIRTUAL_TILES_CONTROLLER_H
#define VIRTUAL_TILES_CONTROLLER_H

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
#include "../virtual-meshes.h"
#include "../../model/model-types.h"
#include "../../bounding-boxes.h"
#include "../../utils.h"
#include "../../multithreading/connection.h"
#include "../../../../Schema.h"
#include "./item-config-controller.h"
#include "../../multithreading/mesh-connection.h"
#include "./raycast-controller.h"
#include "./virtual-memory-controller.h"

using namespace js;

// Forward declarations
class VirtualTilesController;

// Enum TileDimension
namespace TileDimension {
    extern const js::number SMALL;
    extern const js::number MEDIUM;
    extern const js::number LARGE;
    js::string getName(js::number key);
}

class VirtualTilesController {
public:
    std::shared_ptr<Meshes> meshes;
    auto tilesUpdated;
    VirtualTilesController(VirtualTileData data);
    virtual auto restart();
    virtual auto fetchSample(js::number id, CurrentLod lod);
    virtual auto dispose();
    virtual auto generate();
    virtual auto setupView(js::any view);
    virtual auto updateVirtualMeshes(js::array<js::number> itemIds);
    virtual auto getSampleTransform(js::number id);
    virtual auto update(js::number time);
    virtual auto raycast(Representation representation, js::any ray, js::any frustum, std::optional<SnappingClass> snap = std::nullopt);
private:
    auto _graphicMemoryConsumed;
    js::number _sampleAmount;
    js::number _tileDimension;
    js::array<js::any> _tileBySample;
    js::array<js::number> _lodBySample;
    std::shared_ptr<VirtualMeshes> _virtualMeshes;
    std::shared_ptr<MeshConnection> _meshConnection;
    std::shared_ptr<ItemConfigController> _samples;
    auto _tileIdGenerator;
    auto _tiles;
    auto _tilesChanged;
    auto _sizeByTile;
    std::shared_ptr<DataBuffer> _samplesDimensions;
    std::shared_ptr<DataBuffer> _sampleLodClass;
    std::shared_ptr<DataBuffer> _sampleLodState;
    std::shared_ptr<DataBuffer> _sampleLodSize;
    std::shared_ptr<VirtualBoxController> _boxes;
    std::shared_ptr<ItemConfigController> _items;
    js::array<js::number> _materials;
    js::string _modelId;
    auto _lastView;
    auto _params;
    auto _temp;
    auto _currentSample;
    js::array<unknown> _virtualPlanes;
    auto _changedSamples;
    js::any _virtualView;
    virtual auto init();
    virtual auto initSampleLod(js::number id);
    virtual auto fetchSampleAndRepresentation(js::number id);
    virtual auto fetchCurrentMesh();
    virtual auto fetchCurrentMaterial();
    virtual auto fetchSampleLodSize();
    virtual auto setupTileVisibilityAndHighlight();
    virtual auto addLodToTile(VirtualMeshManager mesh, js::number id, js::number material);
    virtual auto addBoxLodToTile(js::number id, js::number material);
    virtual auto notifyUpdateFinished();
    virtual auto updatePositionIfNeeded();
    virtual auto updateCurrentSample();
    virtual auto processSamplesDimension();
    virtual auto setupViewPlanes();
    virtual auto updateOrientationIfNeeded();
    virtual auto getCurrentViewOrientation();
    virtual auto resetUpdateProcess();
    virtual auto manageRaycast(VirtualMeshManager mesh, Representation repr, js::any ray, js::any frustum, std::optional<SnappingClass> snap = std::nullopt);
    virtual auto setTileShellBuffer(TileData tile);
    virtual auto getTileWhenSamplePut(js::number tileId, TileData tileData, js::number material);
    virtual auto getPerspTrueDim(js::number fov, js::number distance);
    virtual auto getTileHighlight(TileData tile, js::array<js::number> locations);
    virtual auto setupTileSampleAttributes(TileData tile, js::number location, js::any geometry, js::any sample);
    virtual auto getTileVisibility(TileData tile, js::array<js::number> locations);
    virtual auto memoryOverflow();
    virtual auto updateMesh(js::number sample);
    virtual auto tileLoadSample(TileData tile, js::any sample, js::number geomIndex);
    virtual auto updateSampleIfSeen(CurrentLod current, js::number sample);
    virtual auto hideHighlightedLods(CurrentLod current, js::number sample);
    virtual auto updateVisible(CurrentLod past, CurrentLod current, js::number sample);
    virtual auto makeInvisibleFromTile(js::number tileId, js::number sample);
    virtual auto updateSample(js::number id, CurrentLod lod);
    virtual auto hasHighlightChanged(js::number id, js::number highlight);
    virtual auto hasVisibleChanged(js::number id, bool visible);
    virtual auto newTile(ObjectClass objectClass, js::number material, CurrentLod lod);
    virtual auto createLod(js::any box);
    virtual auto sampleTemplate(js::number id);
    virtual auto makeSampleInvisible(js::number id, CurrentLod lod);
    virtual auto setSample(js::number id, bool vis, js::number high, CurrentLod lod);
    virtual auto getTileIds(js::number sample, js::number lod);
    virtual auto addBasicTileData(TileData a, js::number sample, js::number id);
    virtual auto buildNewVirtualTile(TileData tile, js::number tileId);
    virtual auto deleteTileIfNeeded(TileData tile, js::number tileId);
    virtual auto getShouldDeleteTile(TileData tile);
    virtual auto checkTileMemoryOverflow(js::number tileId, TileData tileData);
    virtual auto updateTileData(TileData tile, js::number sample, bool visible, js::number highlight);
    virtual auto getKeepUpdating(js::number sampleId, js::number time);
    virtual auto computeTileSize();
    virtual auto newTileId(js::number sample, js::number material, TileData tileData);
    virtual auto logBufferOverflowIfNeeded(TileData tileData);
    virtual auto fetchLodLevel(js::number sample);
    virtual auto generateTileCode(js::number sample, js::number material, TileData tile, CurrentLod lod);
    virtual auto processTileDataId(TileData tile, js::number material, CurrentLod lod);
    virtual auto deleteGeometry(js::number tileId);
    virtual auto processTileSpatialId(js::number sample, CurrentLod lod);
    virtual auto addCustomLodToTile(VirtualMeshManager mesh, js::number id, js::number material);
    virtual auto getTileLocations(TileData tile);
    virtual auto getTileDimension(CurrentLod lod);
    virtual auto processTileDimensionId(js::any box);
    virtual auto tileAppend(TileData a, TileData b, js::number sample, js::number id);
    virtual auto putSampleInTiles(js::number sample, js::number material, js::any tiles);
    virtual auto hasLodChanged(js::number id, CurrentLod lod);
    virtual auto getTileIdsWhenSamplePut(js::any tileIds, js::number tileId);
    virtual auto updateTile(js::number tileId, js::number sample, js::number highlight, bool visible);
    virtual auto getLodTileWhenPutSample(js::number tileId, js::number material);
    virtual auto lodTileAppendSample(js::number sample, js::number material);
    virtual auto addSampleToTile(VirtualMeshManager mesh, js::number id, js::number material);
    virtual auto setTileBuffer(TileData tile, js::any key, bool unsigned);
    virtual auto updateTiles(js::number time);
    virtual auto sampleGeoms(js::any sample, CurrentLod lod, VirtualMeshManager mesh);
    virtual auto generateSampleInTiles(js::number id);
    virtual auto buildSampleInTile(TileData tile, js::number position, js::any sample, bool isStart, js::number id);
    virtual auto getSampleGeometries(js::any sample, js::number geomIndex);
    virtual auto constructTile(TileData tile);
    virtual auto fetchSampleTransform(TileData tile, js::any sample);
    virtual auto hasChanged(js::number id, CurrentLod lod, bool vis, js::number high);
    virtual auto setupTileLocation(TileData tile, js::any geometry, js::any sample);
    virtual auto getTileData(TileData tile);
    virtual auto updateMemoryOnTileLoad(TileData tile);
    virtual auto fetchTileMatrixOnLoad(TileData tile);
    virtual auto updateItem(js::number itemId);
    virtual auto screenSize(js::number dimension, js::number distance);
    virtual auto getTileDimensionClass(js::any box);
    virtual auto getViewDimension(js::number distance);
    virtual auto loadTile(js::number tileId, TileData tile);
    virtual auto getFaceIds(TileData tile);
    virtual auto meshData(VirtualMeshManager mesh, bool allowVoid, js::number lod);
    virtual auto tileAppendAttribute(TileData a, TileData b, js::string name, bool equal);
    virtual auto itemId(js::number sample);
};

#endif // VIRTUAL_TILES_CONTROLLER_H