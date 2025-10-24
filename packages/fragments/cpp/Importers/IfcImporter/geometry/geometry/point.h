#ifndef POINT_H
#define POINT_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "./utils.h"

using namespace js;

// Forward declarations
class Point;

class Point {
public:
    js::number x;
    js::number y;
    js::number z;
    js::string hash;
    js::number id;
    Point(js::Float32Array vertices, js::number index, js::number id, js::number precission);
};

#endif // POINT_H