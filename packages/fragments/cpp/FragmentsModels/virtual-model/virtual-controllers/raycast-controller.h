#ifndef RAYCAST_CONTROLLER_H
#define RAYCAST_CONTROLLER_H

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
#include "../../model/model-types.h"
#include "../../bounding-boxes.h"
#include <...h>
#include "../../utils.h"
#include "../../../../Schema.h"
#include "./item-config-controller.h"

using namespace js;

// Forward declarations
class RaycastController;

class RaycastController {
public:
    RaycastController(Model model, VirtualBoxController boxes, VirtualTilesController tiles, ItemConfigController items);
    auto cast(VirtualMeshManager mesh, Representation representation, js::any ray, js::any frustum, std::optional<SnappingClass> snap = std::nullopt);
    virtual auto raycast(js::any ray, js::any frustum, js::array<unknown> planes);
    virtual auto snapRaycast(js::any ray, js::any frustum, js::array<Snap> snaps, js::array<unknown> planes);
    virtual auto rectangleRaycast(js::any frustum, js::array<unknown> planes, bool fullyInside);
private:
    std::shared_ptr<Meshes> _meshes;
    std::shared_ptr<Model> _model;
    std::shared_ptr<VirtualBoxController> _boxes;
    std::shared_ptr<VirtualTilesController> _tiles;
    std::shared_ptr<ItemConfigController> _items;
    auto _edgeThreshold;
    auto _raycastMultiplier;
    auto _maxDuration;
    auto _precission;
    auto _temp;
    virtual auto snapCastEdges(CastData data, js::array<Snap> snaps);
    virtual auto filterVisible(js::array<js::number> ids);
    virtual auto computeSnaps(js::array<Snap> snaps, CastData data, js::number id, js::array<js::any> results);
    virtual auto computeEdgesCast(CastData data, js::array<Snap> snaps, js::array<js::any> results);
    virtual auto addDistanceToEdgeResult(js::array<js::any> input, js::any ray);
    virtual auto getRawEdges(CastData data);
    virtual js::array<js::number> sortBoxes(js::any ray, js::array<js::number> boxes, std::optional<js::number> limit = std::nullopt);
    virtual auto castBox(js::any input, js::array<unknown> planes);
    virtual auto dataSort(js::array<js::number> ids, js::array<js::number> data);
    virtual auto localIdsFromItemIds(js::array<js::number> raycastedItemIds);
    virtual auto getNearest(js::array<js::any> hits);
    virtual auto getEdges(CastData data, js::array<Snap> snaps, js::array<js::any> results);
    virtual auto getNearScore(js::any input);
    virtual auto setupSampleCastData(CastData data);
    virtual auto addLocalId(js::any raycast);
    virtual auto fetchSampleData(js::number sampleId);
    virtual auto computeRaycastList(js::array<js::number> ids, CastData data);
    virtual auto formatRaycastResult(js::array<js::any> results, js::number id, CastData data);
    virtual auto findAll(js::array<js::number> sortedIds, js::array<js::number> byRay, CastData data);
    virtual auto isTimeExceeded(js::number start);
    virtual auto getFilteredSampleCast(CastData data);
    virtual auto getSnaps(js::any first, CastData data, js::array<Snap> snaps, js::array<js::any> results);
    virtual auto filterOnFront(js::array<js::any> results);
    virtual auto setCastSide(js::any input, js::any ray);
    virtual auto getFaces(js::array<Snap> snaps, CastData data, js::any first, js::array<js::any> results);
    virtual auto setCastPlane(js::any input);
    virtual auto castSample(js::number id, CastData data);
    virtual auto isValidSnap(SnappingClass snapClass);
    virtual auto transform(js::array<unknown> planes, js::any transform);
    virtual auto setupPlanesForSampleCast(CastData data);
};

#endif // RAYCAST_CONTROLLER_H