#include "index_generated.h"
#include "vce-line-raycaster.h"

using namespace js;

VceLineRaycaster::VceLineRaycaster(Meshes meshes) {
    {
            this->_meshes = meshes;
    }
}

auto VceLineRaycaster::lineRaycast(js::number id, js::any ray) {
    {
            this->_found.length() = js::number(0);
            this->_meshes.circleExtrusions(id, this->_circleExtrusion);
            const js::any count = this->_circleExtrusion.axesLength();
            for (js::number index = js::number(0); (index < count); index++) {
                        {
                                        this->_circleExtrusion.axes(index, this->_axis);
                                        this->processLineRaycast(index, ray);
                        }
            }
            return this->_found;
    }
}

auto VceLineRaycaster::wireSetRaycast(js::any ray, std::optional<js::number> radius) {
    {
            const js::any axis = this->_axis;
            VceCasterUtils::traverseWireSets(axis, [&](js::any start, js::any end) -> auto {
            this->cylinderRaycast(start, end, ray, radius);
            });
    }
}

auto VceLineRaycaster::exclusiveCylinderRaycast(js::any ray, js::number radius) {
    {
            const js::any axis = this->_axis;
            const js::any event = this->getCylinderRaycastEvent(ray, radius);
            VceCasterUtils::traverseWires(axis, event);
    }
}

auto VceLineRaycaster::processLineRaycast(js::number id, js::any ray) {
    {
            const js::any width = this->_circleExtrusion.radius(id);
            this->exclusiveCylinderRaycast(ray, width);
            this->circleCurveRaycast(ray, width);
            this->wireSetRaycast(ray, width);
    }
}

auto VceLineRaycaster::getCylinderRaycastEvent(js::any ray, js::number radius) {
    {
            return [&](js::any start, js::any end) -> auto {
            this->cylinderRaycast(start, end, ray, radius);
            };
    }
}

auto VceLineRaycaster::processCircleCurveBody(js::array<unknown> body, js::any ray, js::number radius) {
    {
            for (js::number i = js::number(0); (i < body.length()); i++) {
                        {
                                        if (i === js::number(0)) {
                                                            continue;
                                        }
                                        const js::any mid = body[i];
                                        const js::any past = body[(i - js::number(1))];
                                        this->cylinderRaycast(past, mid, ray, radius);
                        }
            }
    }
}

auto VceLineRaycaster::getCircleCurveRaycastEvent(js::any ray, js::number radius) {
    {
            return [&](js::any first, js::array<unknown> body, js::any last) -> auto {
            this->cylinderRaycast(first, body[js::number(0)], ray, radius);
            this->processCircleCurveBody(body, ray, radius);
            const js::any nextToLast = body[(body.length() - js::number(1))];
            this->cylinderRaycast(nextToLast, last, ray, radius);
            };
    }
}

auto VceLineRaycaster::fetchCylinderRaycastResult(js::any ray, js::any first, js::any last) {
    {
            ray["distanceSqToSegment"](first, last, js::undefined, this->_wirePoint);
            const js::any resultData = this->newResult(first, last);
            this->_found.push(resultData);
    }
}

auto VceLineRaycaster::circleCurveRaycast(js::any ray, js::number radius) {
    {
            const js::any divisionLogic = VceCasterUtils::circleCurve3Divisions;
            const js::any event = this->getCircleCurveRaycastEvent(ray, radius);
            VceCasterUtils::traverseCircleCurve(this->_axis, event, divisionLogic);
    }
}

auto VceLineRaycaster::newResult(js::any first, js::any last) {
    {
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("point", this->_wirePoint.clone());
                  obj_temp_0.set("raySquaredDistance", js::undefined);
                  obj_temp_0.set("snappedEdgeP1", first["clone"]());
                  obj_temp_0.set("snappedEdgeP2", last["clone"]());
                  return js::any(obj_temp_0);
                }();
    }
}

auto VceLineRaycaster::cylinderRaycast(js::any first, js::any last, js::any ray, js::number radius) {
    {
            const js::any u = VceCasterUtils;
            const js::any results = u["raycastCircleExtr"](first, last, ray, radius);
            for (const auto& result : results) {
                        {
                                        if (!result->point) {
                                                            continue;
                                        }
                                        this->fetchCylinderRaycastResult(ray, first, last);
                        }
            }
    }
}
