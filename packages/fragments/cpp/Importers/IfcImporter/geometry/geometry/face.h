#ifndef FACE_H
#define FACE_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "./edge.h"
#include "./plane.h"

using namespace js;

// Forward declarations
class Face;

class Face {
public:
    auto edges;
    auto openEdges;
    js::number id;
    std::shared_ptr<Plane> plane;
    Face(js::number id, Plane plane);
    virtual auto add(Iterable triangle);
    virtual auto match(Iterable triangle, Plane plane);
    virtual auto getOpenEdges();
    virtual auto merge(Face face);
};

#endif // FACE_H