#ifndef VCE_POINT_RAYCASTER_H
#define VCE_POINT_RAYCASTER_H

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
#include "../../../../../Schema.h"
#include "./vce-utils.h"
#include "./vce-caster-utils.h"

using namespace js;

// Forward declarations
class VcePointRaycaster;

class VcePointRaycaster {
public:
    VcePointRaycaster(Meshes meshes);
    virtual auto pointRaycast(js::number id, js::any ray);
private:
    std::shared_ptr<Meshes> _meshes;
    js::array<js::any> _results;
    auto _circleExtrusion;
    auto _axis;
    auto _normal;
    auto _point;
    auto _plane;
    virtual auto fetchOrientation(js::any p1, js::any p2);
    virtual auto getTraverseWiresEvent(js::any ray, js::number radius);
    virtual auto traverseAllCircleExtrusions(js::any ray);
    virtual auto setupCuttedCircleExtrusion(js::any origin);
    virtual auto getTraverseCircleCurveEvent(js::any ray, js::number radius);
    virtual auto computeCutCircleExtrCast(js::any origin, js::number radius, js::any ray);
    virtual auto raycastCutCircleExtrusion(js::any origin, js::any ray, js::number radius);
    virtual auto getCleanResults();
    virtual auto traverseAllCurves(js::any ray, js::number radius);
};

#endif // VCE_POINT_RAYCASTER_H