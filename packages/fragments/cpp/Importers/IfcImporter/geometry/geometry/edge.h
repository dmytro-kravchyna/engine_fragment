#ifndef EDGE_H
#define EDGE_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "./point.h"

using namespace js;

// Forward declarations
class Edge;

class Edge {
public:
    std::shared_ptr<Point> p1;
    std::shared_ptr<Point> p2;
    js::string hash;
    Edge(Point p1, Point p2);
};

#endif // EDGE_H