#ifndef PLANE_H
#define PLANE_H

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
#include "./utils.h"

using namespace js;

// Forward declarations
class Plane;

class Plane {
public:
    js::any normal;
    js::number constant;
    js::string id;
    js::array<js::number> faces;
    Plane(js::any plane, js::number precission, js::number normalPrecision);
};

#endif // PLANE_H