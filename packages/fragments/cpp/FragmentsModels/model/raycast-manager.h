#ifndef RAYCAST_MANAGER_H
#define RAYCAST_MANAGER_H

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
#include "./mesh-manager.h"
#include "../utils.h"

using namespace js;

// Forward declarations
class RaycastManager;

// Interface Point
class IPoint {
public:
    virtual ~IPoint() = default;
    // TODO: Interface members
};
class RaycastManager {
public:
    RaycastManager() = default;
    virtual auto raycast(FragmentsModel model, RaycastData data);
    virtual auto rectangleRaycast(FragmentsModel model, MeshManager meshes, RectangleRaycastData data);
    virtual auto raycastWithSnapping(FragmentsModel model, SnappingRaycastData data);
private:
    auto _caster;
    auto _ray;
    auto _frustum;
    auto _inverseTransform;
    auto _t;
    auto _r;
    auto _b;
    auto _l;
    auto _n;
    auto _f;
    auto _tl;
    auto _tr;
    auto _bl;
    auto _br;
    auto _tln;
    auto _brn;
    auto _tlp;
    auto _brp;
    auto distance;
    virtual auto screenRectToFrustum(js::any screenTopLeft, js::any screenBottomRight, HTMLElement container, js::any camera);
    virtual auto screenToCasterPoint(Point point, js::any viewer, js::any camera);
    virtual auto setPlanes(js::any camera);
    virtual auto setVectors(js::any camera);
    virtual auto newFrustum();
    virtual auto setEnds(js::any camera);
    virtual auto screenToCast(Point p, js::any element, auto result = std::make_shared<three::Vector2>());
    virtual auto setVector(js::any v1, js::any v2, js::any v3, js::number value, js::any camera);
    virtual auto setPlane(js::any plane, js::any v1, js::any v2, js::any v3);
    virtual auto setBasePoints();
    virtual auto setupRay(js::typed::Nullable<unknown> ray, js::any message);
    virtual auto setupMatrix(js::any object);
    virtual auto getRequest(FragmentsModel model, js::any frustum, std::optional<js::any> ray = std::nullopt);
    virtual auto getRayAndFrustum(RaycastData data);
    virtual auto getFrustum(js::any data);
    virtual auto getCorners(js::any mouse);
    virtual auto getResult(js::any data);
    virtual auto updateCamera(js::any camera);
    virtual auto newCastRequest(js::any object, js::string modelId, js::typed::Nullable<unknown> ray, js::any frustum);
    virtual auto setSnapEdge(FragmentsModel model, js::any hit, Partial result, js::any key);
    virtual auto setNormal(FragmentsModel model, js::any hit, Partial result);
    virtual auto setDistance(FragmentsModel model, js::any hit, Partial result);
    virtual auto setPoint(FragmentsModel model, js::any hit, Partial result);
    virtual auto newRaycastSnapResult(js::any response, js::any frustum, js::any ray, FragmentsModel model);
    virtual auto newRectangleCastResponse(js::any response, MeshManager meshes);
    virtual auto setRayDistance(FragmentsModel model, js::any hit, Partial result);
    virtual auto setBasicHitData(FragmentsModel model, js::any hit, Partial result, js::typed::Nullable<unknown> ray, js::any frustum);
};

#endif // RAYCAST_MANAGER_H