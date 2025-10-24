#include "index_generated.h"
#include "vce-point-raycaster.h"

using namespace js;

VcePointRaycaster::VcePointRaycaster(Meshes meshes) {
    {
            this->_meshes = meshes;
    }
}

auto VcePointRaycaster::pointRaycast(js::number id, js::any ray) {
    {
            this->_results.length() = js::number(0);
            this->_meshes.circleExtrusions(id, this->_circleExtrusion);
            this->traverseAllCircleExtrusions(ray);
            return this->getCleanResults();
    }
}

auto VcePointRaycaster::fetchOrientation(js::any p1, js::any p2) {
    {
            VceUtils::temp::vector::copy(p1);
            VceUtils::temp::vector::sub(p2);
            VceUtils::temp::vector::normalize();
            const js::any rot = VceUtils::temp::rotation;
            rot["setFromUnitVectors"](VceUtils::up, VceUtils::temp::vector);
    }
}

auto VcePointRaycaster::getTraverseWiresEvent(js::any ray, js::number radius) {
    {
            return [&](js::any first, js::any last) -> auto {
            this->fetchOrientation(first, last);
            const js::any result1 = this->raycastCutCircleExtrusion(first, ray, radius);
            const js::any result2 = this->raycastCutCircleExtrusion(last, ray, radius);
            this->_results.push(result1, result2);
            };
    }
}

auto VcePointRaycaster::traverseAllCircleExtrusions(js::any ray) {
    {
            const js::any count = this->_circleExtrusion.axesLength();
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        this->_circleExtrusion.axes(i, this->_axis);
                                        const js::any radius = this->_circleExtrusion.radius(i);
                                        const js::any count = VceUtils::vertexLength(radius);
                                        VceUtils::setPathVertices(count);
                                        this->traverseAllCurves(ray, radius);
                        }
            }
    }
}

auto VcePointRaycaster::setupCuttedCircleExtrusion(js::any origin) {
    {
            this->_normal.set(js::number(0), js::number(0), js::number(1));
            this->_normal.applyQuaternion(VceUtils::temp::rotation);
            this->_plane.setFromNormalAndCoplanarPoint(this->_normal, origin);
    }
}

auto VcePointRaycaster::getTraverseCircleCurveEvent(js::any ray, js::number radius) {
    {
            return [&](js::any first, js::array<unknown> mids, js::any last) -> auto {
            this->fetchOrientation(first, mids[js::number(0)]);
            const js::any result1 = this->raycastCutCircleExtrusion(first, ray, radius);
            const js::any nextToLast = mids[(mids.length() - js::number(1))];
            this->fetchOrientation(nextToLast, last);
            const js::any result2 = this->raycastCutCircleExtrusion(last, ray, radius);
            this->_results.push(result1, result2);
            };
    }
}

auto VcePointRaycaster::computeCutCircleExtrCast(js::any origin, js::number radius, js::any ray) {
    {
            ray["intersectPlane"](this->_plane, this->_point);
            const js::any distance = this->_point.distanceTo(origin);
            if (distance <= radius) {
                        {
                                        const js::any point = origin["clone"]();
                                        return []() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("point", point);
                                              return js::any(obj_temp_0);
                                            }();
                        }
            }
            return js::undefined;
    }
}

auto VcePointRaycaster::raycastCutCircleExtrusion(js::any origin, js::any ray, js::number radius) {
    {
            this->setupCuttedCircleExtrusion(origin);
            const js::any collides = ray["intersectsPlane"](this->_plane);
            if (collides) {
                        {
                                        return this->computeCutCircleExtrCast(origin, radius, ray);
                        }
            }
            return js::undefined;
    }
}

auto VcePointRaycaster::getCleanResults() {
    {
            js::array<js::any> filtered = js::array<js::any>{};
            for (const auto& result : this->_results) {
                        {
                                        if (result) {
                                                            {
                                                                                    filtered.push(result);
                                                            }
                                        }
                        }
            }
            return filtered;
    }
}

auto VcePointRaycaster::traverseAllCurves(js::any ray, js::number radius) {
    {
            const js::any wiresEvent = this->getTraverseWiresEvent(ray, radius);
            VceCasterUtils::traverseWires(this->_axis, wiresEvent);
            const js::any circleEvent = this->getTraverseCircleCurveEvent(ray, radius);
            const js::any divider = VceCasterUtils::circleCurve3Divisions;
            VceCasterUtils::traverseCircleCurve(this->_axis, circleEvent, divider);
            const js::any wireSetsEvent = this->getTraverseWiresEvent(ray, radius);
            VceCasterUtils::traverseWireSets(this->_axis, wireSetsEvent);
    }
}
