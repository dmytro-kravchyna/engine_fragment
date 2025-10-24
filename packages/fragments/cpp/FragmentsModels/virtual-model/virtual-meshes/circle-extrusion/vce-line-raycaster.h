#ifndef VCE_LINE_RAYCASTER_H
#define VCE_LINE_RAYCASTER_H

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
#include "./vce-caster-utils.h"

using namespace js;

// Forward declarations
class VceLineRaycaster;

class VceLineRaycaster {
public:
    VceLineRaycaster(Meshes meshes);
    virtual auto lineRaycast(js::number id, js::any ray);
private:
    std::shared_ptr<Meshes> _meshes;
    auto _found;
    auto _circleExtrusion;
    auto _axis;
    auto _wirePoint;
    virtual auto wireSetRaycast(js::any ray, std::optional<js::number> radius = std::nullopt);
    virtual auto exclusiveCylinderRaycast(js::any ray, js::number radius);
    virtual auto processLineRaycast(js::number id, js::any ray);
    virtual auto getCylinderRaycastEvent(js::any ray, js::number radius);
    virtual auto processCircleCurveBody(js::array<unknown> body, js::any ray, js::number radius);
    virtual auto getCircleCurveRaycastEvent(js::any ray, js::number radius);
    virtual auto fetchCylinderRaycastResult(js::any ray, js::any first, js::any last);
    virtual auto circleCurveRaycast(js::any ray, js::number radius);
    virtual auto newResult(js::any first, js::any last);
    virtual auto cylinderRaycast(js::any first, js::any last, js::any ray, js::number radius);
};

#endif // VCE_LINE_RAYCASTER_H