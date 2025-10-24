#ifndef FACES_H
#define FACES_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "./plane.h"
#include "./edge.h"
#include "./face.h"

using namespace js;

// Forward declarations
class Faces;

class Faces {
public:
    Faces() = default;
    auto list;
    auto nextFaceID;
    virtual auto add(js::array<Edge> triangle, Plane plane);
private:
    virtual auto match(js::array<Edge> triangle, Plane plane);
};

#endif // FACES_H