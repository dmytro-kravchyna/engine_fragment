#ifndef TRANSFORM_HELPER_H
#define TRANSFORM_HELPER_H

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
#include "../../../../Schema.h"
#include "./parser-helper.h"

using namespace js;

// Forward declarations
class TransformHelper;

class TransformHelper {
public:
    TransformHelper() = default;
    auto get(Sample sample, Meshes meshes, js::any transform);
    auto getBox(Representation representation, js::any bbox);
    auto boxSize(js::any bbox);
private:
    auto _transform;
    auto _min;
    auto _max;
    auto _center;
    auto _distance;
    auto _edge;
    auto _item;
    auto _sample;
    auto _box;
    auto _transformers;
    auto getBoxData(js::any bbox);
    auto applyTransformer();
    auto fetchItemTransform(Sample sample, Meshes meshes);
    auto fetchSampleTransform(Sample sample, Meshes meshes);
    auto setBoxZ();
    auto setBoxY();
    auto setBoxX();
};

#endif // TRANSFORM_HELPER_H