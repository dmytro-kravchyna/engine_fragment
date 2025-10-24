#ifndef EARCUT_H
#define EARCUT_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"

using namespace js;

auto earcut(js::any data, js::any holeIndices, js::any dim, js::any a, js::any b, js::any createGeometry);
auto linkedList(js::any data, js::any start, js::any end, js::any dim, js::any clockwise, js::any a, js::any b);
auto filterPoints(js::any start, std::optional<js::any> end = std::nullopt);
auto earcutLinked(js::any ear, js::any createGeometry, js::any dim, js::any minX, js::any minY, js::any invSize, std::optional<js::any> pass = std::nullopt);
auto isEar(js::any ear);
auto isEarHashed(js::any ear, js::any minX, js::any minY, js::any invSize);
auto cureLocalIntersections(js::any start, js::any createGeometry, js::any dim);
auto splitEarcut(js::any start, js::any createGeometry, js::any dim, js::any minX, js::any minY, js::any invSize);
auto eliminateHoles(js::any data, js::any holeIndices, js::any outerNode, js::any dim, js::any a, js::any b);
auto xDifference(js::any a, js::any b);
auto eliminateHole(js::any hole, js::any outerNode);
auto findHoleBridge(js::any hole, js::any outerNode);
auto sectorContainsSector(js::any m, js::any p);
auto indexCurve(js::any start, js::any minX, js::any minY, js::any invSize);
auto sortLinked(js::any list);
auto zOrder(js::any x, js::any y, js::any minX, js::any minY, js::any invSize);
auto getLeftmost(js::any start);
auto pointInTriangle(js::any ax, js::any ay, js::any bx, js::any by, js::any cx, js::any cy, js::any px, js::any py);
auto isValidDiagonal(js::any a, js::any b);
auto area(js::any p, js::any q, js::any r);
auto equals(js::any p1, js::any p2);
auto intersects(js::any p1, js::any q1, js::any p2, js::any q2);
auto onSegment(js::any p, js::any q, js::any r);
auto sign(js::any num);
auto intersectsPolygon(js::any a, js::any b);
auto locallyInside(js::any a, js::any b);
auto middleInside(js::any a, js::any b);
auto splitPolygon(js::any a, js::any b);
auto insertNode(js::any i, js::any x, js::any y, js::any last);
auto removeNode(js::any p);
auto createNode(js::any i, js::any x, js::any y);
auto signedArea(js::any data, js::any start, js::any end, js::any dim, js::any a, js::any b);

#endif // EARCUT_H