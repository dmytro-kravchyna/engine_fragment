#ifndef PROFILES_H
#define PROFILES_H

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
#include "./profile.h"

using namespace js;

// Forward declarations
class Profiles;

class Profiles {
public:
    auto list;
    std::shared_ptr<Plane> plane;
    auto nextProfileID;
    Profiles(Plane plane);
    virtual auto add(Edge edge);
    virtual auto getProfiles();
private:
    virtual auto match(Edge edge);
};

#endif // PROFILES_H