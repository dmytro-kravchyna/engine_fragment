#include "index_generated.h"
#include "vce-caster-utils.h"

using namespace js;

auto VceCasterUtils::circleCurve3Divisions(CircleCurve input) {
    {
            const js::number factor = js::number(4);
            const js::number min = js::number(4);
            const js::number max = js::number(32);
            const js::any aperture = input["aperture"]();
            const js::any radius = input["radius"]();
            const js::number rawResult = ((aperture * radius) * factor);
            const js::any divisions = js::Math::round(rawResult);
            return js::Math::min(js::Math::max(divisions, min), max);
    }
}

auto VceCasterUtils::traverseCircleCurve(Axis axis, std::function<void(unknown, js::array<unknown>, unknown)> callback, std::function<js::number(CircleCurve)> getDivisions) {
    {
            const js::any count = axis["circleCurvesLength"]();
            const js::number startAndEnd = js::number(2);
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        this->getAllCircleCurveData(axis, i);
                                        const js::any divisions = getDivisions(this->_circleCurve);
                                        this->_circlePoints.length() = (divisions - startAndEnd);
                                        this->getCircleCurveMids(divisions);
                                        this->getNewCircleCurveData();
                                        callback(this->_circleP1, this->_circlePoints, this->_circleP2);
                        }
            }
    }
}

auto VceCasterUtils::traverseWireSets(Axis axis, std::function<void(unknown, unknown)> callback) {
    {
            const js::any wireSetCount = axis["wireSetsLength"]();
            for (js::number i = js::number(0); (i < wireSetCount); i++) {
                        {
                                        axis["wireSets"](i, this->_wireSet);
                                        this->traverseWireSetWires(callback);
                        }
            }
    }
}

auto VceCasterUtils::raycastCircleExtr(js::any first, js::any last, js::any ray, js::number radius) {
    {
            const js::any distance = last["distanceTo"](first);
            this->setupCircleExtrusionAxes(last, first);
            this->setupCircleExtrusionTransform(first, radius);
            this->setupCircleExtrusionRay(ray);
            return this->computeCircleExtrusionRaycast(distance, radius);
    }
}

auto VceCasterUtils::traverseWires(Axis axis, std::function<void(unknown, unknown)> callback) {
    {
            const js::any wiresCount = axis["wiresLength"]();
            for (js::number i = js::number(0); (i < wiresCount); i++) {
                        {
                                        axis["wires"](i, this->_wire);
                                        this->setWire();
                                        callback(this->_wireP1, this->_wireP2);
                        }
            }
    }
}

auto VceCasterUtils::getNewCircleCurveData() {
    {
            this->_circleP2.copy(this->_circleP1);
            const js::any aperture = this->_circleCurve.aperture();
            const js::any radius = this->_circleCurve.radius();
            this->_circleP2.applyAxisAngle(this->_circleOrientation, aperture);
            this->_circleP2.multiplyScalar(radius);
            this->_circleP2.add(this->_circleOrigin);
            this->_circleP1.multiplyScalar(radius);
            this->_circleP1.add(this->_circleOrigin);
    }
}

auto VceCasterUtils::setWire() {
    {
            this->setWirePoint("p1"_S, this->_wireP1);
            this->setWirePoint("p2"_S, this->_wireP2);
    }
}

auto VceCasterUtils::getCircleCurveMids(js::number divisions) {
    {
            const js::any count = this->_circlePoints.length();
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        this->_circlePoints[i] = this->newCirclePoint(i, divisions);
                        }
            }
    }
}

auto VceCasterUtils::newCirclePoint(js::number i, js::number divisions) {
    {
            const js::number divisionCount = (divisions - js::number(1));
            const js::number currentSegment = (i + js::number(1));
            const std::shared_ptr<three::Vector3> point = std::make_shared<three::Vector3>();
            point["copy"](this->_circleP1);
            const js::any radius = this->_circleCurve.radius();
            const js::any aperture = this->_circleCurve.aperture();
            const js::number progress = (aperture * currentSegment);
            const js::number angle = (progress / divisionCount);
            point["applyAxisAngle"](this->_circleOrientation, angle);
            point["multiplyScalar"](radius);
            point["add"](this->_circleOrigin);
            return point;
    }
}

auto VceCasterUtils::getAllCircleCurveData(Axis axis, js::number i) {
    {
            axis["circleCurves"](i, this->_circleCurve);
            this->getCircleCurveData(this->_circleOrigin, "position"_S);
            this->getCircleCurveData(this->_circleOrientation, "xDirection"_S);
            this->getCircleCurveData(this->_circleP1, "yDirection"_S);
    }
}

auto VceCasterUtils::setWirePoint(js::any point, js::any vector) {
    {
            this->_wire[point](this->_floats);
            const js::any x = this->_floats.x();
            const js::any y = this->_floats.y();
            const js::any z = this->_floats.z();
            vector["set"](x, y, z);
    }
}

auto VceCasterUtils::getCircleCurveData(js::any vector, js::any key) {
    {
            const js::any data = this->_circleCurve[key]();
            this->getVectorData(data, vector);
    }
}

auto VceCasterUtils::getVectorData(FloatVector data, js::any vector) {
    {
            const js::any x = data->x();
            const js::any y = data->y();
            const js::any z = data->z();
            vector["set"](x, y, z);
    }
}

auto VceCasterUtils::traverseWireSetWires(std::function<void(unknown, unknown)> callback) {
    {
            const js::any pointsCount = this->_wireSet.psLength();
            const js::number wiresCount = (pointsCount - js::number(1));
            for (js::number i = js::number(0); (i < wiresCount); i++) {
                        {
                                        this->getWiresetPoint(this->_currentWireSetPoint, i);
                                        this->getWiresetPoint(this->_nextWireSetPoint, (i + js::number(1)));
                                        callback(this->_currentWireSetPoint, this->_nextWireSetPoint);
                        }
            }
    }
}

auto VceCasterUtils::getWiresetPoint(js::any point, js::number index) {
    {
            const js::any pointData = this->_wireSet.ps(index);
            this->getVectorData(pointData, point);
    }
}

auto VceCasterUtils::setupCircleExtrusionTransform(js::any first, js::number radius) {
    {
            this->_ceTransform.identity();
            this->_ceTransform.makeBasis(this->_ceAxisX, this->_ceAxisY, this->_ceAxisZ);
            this->_ceTransform.setPosition(first);
            this->_ceSize.set(radius, radius, radius);
            this->_ceTransform.scale(this->_ceSize);
    }
}

auto VceCasterUtils::computeCircleExtrusionRaycastFactors() {
    {
            const js::number c1 = js::number(2);
            const js::number c2 = js::number(4);
            const js::any d = this->_ceRay.direction;
            const js::any o = this->_ceRay.origin;
            const js::number x = ((d["x"] * d["x"]) + (d["y"] * d["y"]));
            const js::number y = (((c1 * o["x"]) * d["x"]) + ((c1 * o["y"]) * d["y"]));
            const js::number z = (((o["x"] * o["x"]) + (o["y"] * o["y"])) - js::number(1));
            const js::number v1 = ((c2 * x) * z);
            const js::number v2 = (y * y);
            const bool nothingFound = (v1 > v2);
            if (nothingFound) {
                        {
                                        return js::null;
                        }
            }
            const js::number v3 = (c1 * x);
            const js::any v4 = js::Math::sqrt((v2 - v1));
            const js::number factorA = ((-y + v4) / v3);
            const js::number factorB = ((-y - v4) / v3);
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("factorA", factorA);
                  obj_temp_0.set("factorB", factorB);
                  return js::any(obj_temp_0);
                }();
    }
}

auto VceCasterUtils::computeCircleExtrusionRaycast(js::number distance, js::number radius) {
    {
            const js::any result = this->computeCircleExtrusionRaycastFactors();
            if (result === js::null) {
                        {
                                        return js::array<js::any>{};
                        }
            }
            auto _temp5501 = result;
            const auto factorA = _temp5501["factorA"];
            const auto factorB = _temp5501["factorB"];
            this->_ceInverseTransform.transpose();
            this->_ceRaycastPoints = js::array<js::any>{};
            this->computeCircleExtrusionRaycastPoints(factorA, distance, radius);
            this->computeCircleExtrusionRaycastPoints(factorB, distance, radius);
            return this->_ceRaycastPoints;
    }
}

auto VceCasterUtils::setupCircleExtrusionRay(js::any ray) {
    {
            this->_ceInverseTransform.copy(this->_ceTransform);
            this->_ceInverseTransform.invert();
            this->_ceRay.copy(ray);
            this->_ceRay.applyMatrix4(this->_ceInverseTransform);
    }
}

auto VceCasterUtils::computeCircleExtrusionRaycastPoints(js::number factor, js::number size, js::number radius) {
    {
            const js::any clashes = this->checkIfCircleExtrusionClashes(factor, size, radius);
            if (!clashes) {
                        return;
            }
            this->_ceRaycastPoint.applyMatrix4(this->_ceTransform);
            const js::any point = this->_ceRaycastPoint.clone();
            this->_ceRaycastPoints.push([]() {
                  js::object obj_temp_1;
                  obj_temp_1.set("point", point);
                  return js::any(obj_temp_1);
                }());
    }
}

auto VceCasterUtils::setupCircleExtrusionAxes(js::any last, js::any first) {
    {
            this->_ceAxisZ.copy(last);
            this->_ceAxisZ.sub(first);
            this->_ceAxisZ.normalize();
            this->computeNormal(this->_ceAxisZ, this->_ceAxisX);
            this->_ceAxisY.crossVectors(this->_ceAxisZ, this->_ceAxisX);
    }
}

auto VceCasterUtils::computeNormal(js::any source, js::any target) {
    {
            const js::number threshold = js::number(0.9);
            const js::any dot = source->dot(this->_ceAbsoluteX);
            const js::any absDot = js::Math::abs(dot);
            const bool isLookingAtX = (absDot > threshold);
            const js::any v = (js::null ? js::null : js::null);
            target->crossVectors(source, v);
            target->normalize();
    }
}

auto VceCasterUtils::setupCircleExtrusionRaycastPoint(js::number factor) {
    {
            this->_ceRaycastPoint.copy(this->_ceRay.direction);
            this->_ceRaycastPoint.normalize();
            this->_ceRaycastPoint.multiplyScalar(factor);
            this->_ceRaycastPoint.add(this->_ceRay.origin);
    }
}

auto VceCasterUtils::checkIfCircleExtrusionClashes(js::number factor, js::number size, js::number radius) {
    {
            this->setupCircleExtrusionRaycastPoint(factor);
            const js::number rel = (size / radius);
            const js::any z = this->_ceRaycastPoint.z;
            const js::any clashes = (z >= js::number(0) && z <= rel);
            return clashes;
    }
}
