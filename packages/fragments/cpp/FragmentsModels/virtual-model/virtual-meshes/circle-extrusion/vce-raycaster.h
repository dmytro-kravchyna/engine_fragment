#ifndef VCE_RAYCASTER_H
#define VCE_RAYCASTER_H

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
class VceRaycaster;

class VceRaycaster {
public:
    VceRaycaster(Meshes meshes);
    virtual auto raycast(js::number id, js::any ray);
private:
    std::shared_ptr<Meshes> _meshes;
    js::array<js::any> _results;
    auto _circleExtrusion;
    auto _axis;
    virtual auto getTraverseWiresEvent(js::any ray, js::number radius);
    virtual auto castCurveExtrusion(js::any a, js::any b, js::any ray, js::number radius);
    virtual auto getTraverseCircleCurveEvent(js::any ray, js::number radius);
    virtual auto traverseAllCurves(js::any ray, js::number radius);
};

#endif // VCE_RAYCASTER_H