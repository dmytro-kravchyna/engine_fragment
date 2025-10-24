#ifndef SECTION_GENERATOR_H
#define SECTION_GENERATOR_H

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
#include <earcut.h>

using namespace js;

// Forward declarations
class SectionGenerator;

class SectionGenerator {
public:
    SectionGenerator() = default;
    virtual auto createEdges(js::any data);
    virtual auto createFills(js::Float32Array buffer, js::array<js::number> trianglesIndices);
private:
    auto _inverseMatrix;
    auto _localPlane;
    auto _tempLine;
    auto _tempVector;
    js::any _plane;
    auto _plane2DCoordinateSystem;
    auto _precission;
    virtual auto computeFill(js::array<js::number> vertices, js::Float32Array buffer);
    virtual auto updatePlane2DCoordinateSystem();
    virtual auto shapecast(js::any mesh, js::any posAttr, js::number index);
};

#endif // SECTION_GENERATOR_H