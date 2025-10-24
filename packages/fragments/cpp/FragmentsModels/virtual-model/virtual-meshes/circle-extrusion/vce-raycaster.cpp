#include "index_generated.h"
#include "vce-raycaster.h"

using namespace js;

VceRaycaster::VceRaycaster(Meshes meshes) {
    {
            this->_meshes = meshes;
    }
}

auto VceRaycaster::raycast(js::number id, js::any ray) {
    {
            this->_results.length() = js::number(0);
            this->_meshes.circleExtrusions(id, this->_circleExtrusion);
            for (js::number i = js::number(0);
            js::any l = this->_circleExtrusion.axesLength(); (i < l); i++) {
                        {
                                        this->_circleExtrusion.axes(i, this->_axis);
                                        const js::any radius = this->_circleExtrusion.radius(i);
                                        this->traverseAllCurves(ray, radius);
                        }
            }
            return this->_results;
    }
}

auto VceRaycaster::getTraverseWiresEvent(js::any ray, js::number radius) {
    {
            return [&](js::any start, js::any end) -> auto {
            this->castCurveExtrusion(start, end, ray, radius);
            };
    }
}

auto VceRaycaster::castCurveExtrusion(js::any a, js::any b, js::any ray, js::number radius) {
    {
            const js::any u = VceCasterUtils;
            const js::any result1 = u["raycastCircleExtr"](a, b, ray, radius);
            for (const auto& result : result1) {
                        {
                                        this->_results.push(result);
                        }
            }
    }
}

auto VceRaycaster::getTraverseCircleCurveEvent(js::any ray, js::number radius) {
    {
            return [&](js::any first, js::array<unknown> mids, js::any last) -> auto {
            const js::any second = mids[js::number(0)];
            this->castCurveExtrusion(first, second, ray, radius);
            for (js::number i = js::number(0); (i < mids.length()); i++) {
                        {
                                        if (i === js::number(0)) {
                                                            continue;
                                        }
                                        const js::any first = mids[(i - js::number(1))];
                                        const js::any second = mids[i];
                                        this->castCurveExtrusion(first, second, ray, radius);
                        }
            }
            const js::any nextToLast = mids[(mids.length() - js::number(1))];
            this->castCurveExtrusion(nextToLast, last, ray, radius);
            };
    }
}

auto VceRaycaster::traverseAllCurves(js::any ray, js::number radius) {
    {
            const js::any wireEvent = this->getTraverseWiresEvent(ray, radius);
            VceCasterUtils::traverseWires(this->_axis, wireEvent);
            const js::any circleCurveEvent = this->getTraverseCircleCurveEvent(ray, radius);
            const js::any divider = VceCasterUtils::circleCurve3Divisions;
            VceCasterUtils::traverseCircleCurve(this->_axis, circleCurveEvent, divider);
            const js::any wireSetEvent = this->getTraverseWiresEvent(ray, radius);
            VceCasterUtils::traverseWireSets(this->_axis, wireSetEvent);
    }
}
