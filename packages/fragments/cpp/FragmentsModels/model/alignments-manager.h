#ifndef ALIGNMENTS_MANAGER_H
#define ALIGNMENTS_MANAGER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "runtime/async.h"
#include <three.h>
#include <three/examples/jsm/lines/Line2.js.h>
#include <three/examples/jsm/lines/LineMaterial.js.h>
#include <three/examples/jsm/lines/LineGeometry.js.h>
#include "./fragments-model.h"
#include "./model-types.h"
#include "../../../Schema.h"

using namespace js;

// Forward declarations
class AlignmentsManager;

class AlignmentsManager {
public:
    AlignmentsManager(FragmentsModel model);
    virtual auto getAlignments();
    virtual auto getHorizontalAlignments();
    virtual auto getVerticalAlignments();
    virtual auto getAlignmentStyles();
    virtual auto dispose();
private:
    std::shared_ptr<FragmentsModel> model;
    auto _endpointsMaterials;
    auto _absoluteAlignments;
    auto _horizontalAlignments;
    auto _verticalAlignments;
    auto _alignmentMaterials;
    virtual auto constructAlignments();
    virtual auto constructLine(js::array<AlignmentCurve> data, js::any parent);
    virtual auto constructPoints(js::array<js::number> pointsArray, js::any material, js::any alignment);
};

#endif // ALIGNMENTS_MANAGER_H