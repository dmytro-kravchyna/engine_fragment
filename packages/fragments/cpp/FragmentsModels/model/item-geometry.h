#ifndef ITEM_GEOMETRY_H
#define ITEM_GEOMETRY_H

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
#include "./model-types.h"
#include "./fragments-model.h"

using namespace js;

// Forward declarations
class ItemGeometry;

class ItemGeometry {
public:
    std::shared_ptr<FragmentsModel> model;
    js::number localId;
    ItemGeometry(FragmentsModel model, js::number localId);
    virtual auto get();
    virtual auto getIndices();
    virtual auto getTransform();
    virtual auto getNormals();
    virtual auto getPositions();
    virtual auto getVertices();
    virtual auto getTriangles();
    virtual auto getPosition();
    virtual auto getBox();
    virtual auto setVisibility(bool visible);
    virtual auto getVisibility();
private:
    js::any _indices;
    js::typed::Nullable<js::array<unknown>> _transform;
    js::typed::Nullable<js::array<js::Int16Array>> _normals;
    js::any _positions;
    js::typed::Nullable<js::array<js::array<unknown>>> _vertices;
    js::typed::Nullable<js::array<js::array<unknown>>> _triangles;
    js::typed::Nullable<js::array<unknown>> _position;
    js::typed::Nullable<js::array<unknown>> _box;
};

#endif // ITEM_GEOMETRY_H