#ifndef PROFILE_H
#define PROFILE_H

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
#include "./edge.h"
#include "./point.h"
#include "./plane.h"

using namespace js;

// Forward declarations
class Profile;

class Profile {
public:
    auto closed;
    js::typed::Nullable<js::string> openStartPoint;
    js::typed::Nullable<js::string> openEndPoint;
    std::shared_ptr<Plane> plane;
    js::array<Point> orderedPoints;
    Profile(Plane plane);
    virtual auto getEdges(bool reverse = false);
    virtual auto getIndices();
    virtual auto add(Edge edge);
    virtual auto match(Edge edge);
    virtual auto merge(Profile newProfile);
    virtual auto getArea();
};

#endif // PROFILE_H