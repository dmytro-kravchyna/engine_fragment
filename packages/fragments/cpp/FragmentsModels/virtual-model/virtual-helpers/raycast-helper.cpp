#include "index_generated.h"
#include "raycast-helper.h"

using namespace js;

js::any RaycastHelper::raycast(VirtualFragmentsModel model, js::any ray, js::any frustum) {
    {
            if (model["view"]) {
                        {
                                        return model["raycaster"]["raycast"](ray, frustum, model["view"]["clippingPlanes"]);
                        }
            }
            return js::undefined;
    }
}

js::array<js::any> RaycastHelper::snapRaycast(VirtualFragmentsModel model, js::any ray, js::any frustum, js::array<SnappingClass> snappingClass) {
    {
            if (model["view"]) {
                        {
                                        return model["raycaster"]["snapRaycast"](ray, frustum, snappingClass, model["view"]["clippingPlanes"]);
                        }
            }
            return js::array<js::any>{};
    }
}

js::array<js::number> RaycastHelper::rectangleRaycast(VirtualFragmentsModel model, js::any frustum, bool fullyIncluded) {
    {
            if (model["view"]) {
                        {
                                        return model["raycaster"]["rectangleRaycast"](frustum, model["view"]["clippingPlanes"], fullyIncluded);
                        }
            }
            return js::array<js::any>{};
    }
}
