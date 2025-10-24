#ifndef VCE_UTILS_H
#define VCE_UTILS_H

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
#include "../../../model/model-types.h"

using namespace js;

// Forward declarations
class VceUtils;

class VceUtils {
public:
    VceUtils() = default;
    auto up;
    js::array<unknown> circleCurves;
    js::array<unknown> circleCurvePoints;
    auto temp;
    auto newPaths(CircleCurve circleCurve, js::number size);
    auto getAxisPartSize(Axis axis, js::number id, js::number vertexSize);
    auto vertexLength(js::number radius, js::number factor = js::number(200));
    auto setPathVertices(js::number vertexSize);
    auto validSize(js::number pointsSize, js::number extraPoints, js::number vertexSize);
private:
    auto _wireSize;
    auto _minSize;
    auto _maxSize;
    auto _axisPartSize;
    auto fetchCircleCurveEnds(PathData data, CircleCurve circleCurve);
    auto getAxisPartData(AxisPartClass part, js::number vertexSize, Axis axis, js::number order);
    auto newEmptyAxisPartData();
    auto getAxisPartWireSetData;
    auto fetchCircleCurveMids(js::number size, PathData data, CircleCurve circleCurve);
    auto getAxisPartWireData;
    auto fetchCircleCurveCuts(PathData data);
    auto fetchCircleCurveData(CircleCurve circleCurve, PathData data);
    auto newPathData();
    auto fetchAxisPartSize(js::number vertexSize, AxisPartData data);
    auto getAxisPartCircleCurveData;
};

#endif // VCE_UTILS_H