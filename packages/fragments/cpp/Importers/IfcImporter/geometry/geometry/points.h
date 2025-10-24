#ifndef POINTS_H
#define POINTS_H

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
#include "./point.h"

using namespace js;

// Forward declarations
class Points;

class Points {
public:
    auto list;
    auto tempV1;
    auto tempV2;
    auto tempV3;
    js::number precission;
    Points(js::number precission);
    virtual auto create(js::Float32Array vertices, js::number index);
    virtual auto get();
    virtual auto isValidTriangle(js::Float32Array position, js::number index1, js::number index2, js::number index3);
};

#endif // POINTS_H