#ifndef VCE_CASTER_UTILS_H
#define VCE_CASTER_UTILS_H

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

using namespace js;

// Forward declarations
class VceCasterUtils;

class VceCasterUtils {
public:
    VceCasterUtils() = default;
    auto circleCurve3Divisions(CircleCurve input);
    auto traverseCircleCurve(Axis axis, std::function<void(unknown, js::array<unknown>, unknown)> callback, std::function<js::number(CircleCurve)> getDivisions);
    auto traverseWireSets(Axis axis, std::function<void(unknown, unknown)> callback);
    auto raycastCircleExtr(js::any first, js::any last, js::any ray, js::number radius);
    auto traverseWires(Axis axis, std::function<void(unknown, unknown)> callback);
private:
    auto _floats;
    auto _wire;
    auto _wireSet;
    auto _circleCurve;
    auto _wireP1;
    auto _wireP2;
    auto _circleP1;
    auto _circleP2;
    auto _circleOrigin;
    auto _circleOrientation;
    auto _currentWireSetPoint;
    auto _nextWireSetPoint;
    auto _ceAxisZ;
    auto _ceAxisY;
    auto _ceAxisX;
    auto _ceRaycastPoint;
    auto _ceSize;
    auto _ceAbsoluteX;
    auto _ceAbsoluteZ;
    js::array<unknown> _circlePoints;
    auto _ceTransform;
    auto _ceInverseTransform;
    auto _ceRay;
    js::array<js::any> _ceRaycastPoints;
    auto getNewCircleCurveData();
    auto setWire();
    auto getCircleCurveMids(js::number divisions);
    auto newCirclePoint(js::number i, js::number divisions);
    auto getAllCircleCurveData(Axis axis, js::number i);
    auto setWirePoint(js::any point, js::any vector);
    auto getCircleCurveData(js::any vector, js::any key);
    auto getVectorData(FloatVector data, js::any vector);
    auto traverseWireSetWires(std::function<void(unknown, unknown)> callback);
    auto getWiresetPoint(js::any point, js::number index);
    auto setupCircleExtrusionTransform(js::any first, js::number radius);
    auto computeCircleExtrusionRaycastFactors();
    auto computeCircleExtrusionRaycast(js::number distance, js::number radius);
    auto setupCircleExtrusionRay(js::any ray);
    auto computeCircleExtrusionRaycastPoints(js::number factor, js::number size, js::number radius);
    auto setupCircleExtrusionAxes(js::any last, js::any first);
    auto computeNormal(js::any source, js::any target);
    auto setupCircleExtrusionRaycastPoint(js::number factor);
    auto checkIfCircleExtrusionClashes(js::number factor, js::number size, js::number radius);
};

#endif // VCE_CASTER_UTILS_H