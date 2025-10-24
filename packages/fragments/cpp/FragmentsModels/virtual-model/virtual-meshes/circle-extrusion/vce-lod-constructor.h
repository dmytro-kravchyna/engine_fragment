#ifndef VCE_LOD_CONSTRUCTOR_H
#define VCE_LOD_CONSTRUCTOR_H

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
#include "../../../model/model-types.h"
#include "../types.h"
#include "./vce-caster-utils.h"
#include "./vce-utils.h"

using namespace js;

// Forward declarations
class VceLodConstructor;

class VceLodConstructor {
public:
    VceLodConstructor() = default;
    virtual auto construct(CircleExtrusion circleExtrusion, TileData mesh);
    virtual auto newTemplate();
private:
    auto _currentElement;
    auto _wireSize;
    virtual auto constructCircleExtrusionLod(js::number id, TileData mesh);
    auto newCircleCurveLod;
    auto newWireSetLod;
    auto newWireTemplate;
    virtual auto newCircleCurveLodPath(Axis axis, js::number index);
    virtual auto selectNextWire();
    virtual void getAxisPartVertexSize(js::number id, TileBasicData template);
    virtual auto getIndices();
    virtual auto setAxisTemplate(js::number id, TileBasicData template);
    virtual auto constructLod(TileData mesh);
    virtual auto getLodConstructor(AxisPartClass type);
    auto newWireSetTemplate;
    virtual auto setAxisThickness(TileBasicData template, js::number id);
    virtual auto newTemplateData();
    auto newWireLod;
    virtual auto getTemplateConstructor(AxisPartClass type);
    virtual auto newWire(DataBuffer points, js::any first, js::any last);
    auto newCircleCurveTemplate;
};

#endif // VCE_LOD_CONSTRUCTOR_H