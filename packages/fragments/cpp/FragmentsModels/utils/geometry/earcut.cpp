#include "index_generated.h"
#include "earcut.h"

using namespace js;

auto earcut(js::any data, js::any holeIndices, js::any dim, js::any a, js::any b, js::any createGeometry) {
    const js::any hasHoles = (holeIndices && holeIndices.length());
    const js::any outerLen = (js::null ? js::null : js::null);
    js::any outerNode = linkedList(data, js::number(0), outerLen, dim, true, a, b);
    if ((!outerNode || outerNode->next === outerNode->prev)) {
            return;
    }
    auto minX;
    auto minY;
    auto invSize;
    if (hasHoles) {
            outerNode = eliminateHoles(data, holeIndices, outerNode, dim, a, b);
    }
    if ((data.length() > (js::number(80) * dim))) {
            {
                        js::any maxX = data->a;
                        js::any maxY = data->b;
                        minX = maxX;
                        minY = maxY;
                        for (js::any i = dim; (i < outerLen); i += dim) {
                                        {
                                                            const js::any x = data->(i + a);
                                                            const js::any y = data->(i + b);
                                                            if ((x < minX)) {
                                                                                    minX = x;
                                                            }
                                                            if ((y < minY)) {
                                                                                    minY = y;
                                                            }
                                                            if ((x > maxX)) {
                                                                                    maxX = x;
                                                            }
                                                            if ((y > maxY)) {
                                                                                    maxY = y;
                                                            }
                                        }
                        }
                        invSize = js::Math::max((maxX - minX), (maxY - minY));
                        invSize = (js::null ? js::null : js::null);
            }
    }
    earcutLinked(outerNode, createGeometry, dim, minX, minY, invSize);
}

auto linkedList(js::any data, js::any start, js::any end, js::any dim, js::any clockwise, js::any a, js::any b) {
    auto finish;
    auto current;
    auto counter;
    if (clockwise === (signedArea(data, start, end, dim, a, b) > js::number(0))) {
            {
                        for (counter = start; (counter < end); counter += dim) {
                                        finish = insertNode(counter, data->(counter + a), data->(counter + b), finish);
                        }
            }
    } else {
            {
                        for (counter = (end - dim); counter >= start; counter -= dim) {
                                        finish = insertNode(counter, data->(counter + a), data->(counter + b), finish);
                        }
            }
    }
    if ((finish && equals(finish, finish["next"]))) {
            {
                        current = finish["next"];
                        removeNode(finish);
                        finish = current;
            }
    }
    return finish;
}

auto filterPoints(js::any start, std::optional<js::any> end) {
    if (!start) {
            return start;
    }
    if (!end) {
            end = start;
    }
    js::any p = start;
    auto again;
    auto past;
    js::null;
    return end;
}

auto earcutLinked(js::any ear, js::any createGeometry, js::any dim, js::any minX, js::any minY, js::any invSize, std::optional<js::any> pass) {
    if ((!pass && invSize)) {
            indexCurve(ear, minX, minY, invSize);
    }
    js::any stop = ear;
    while (js::null) {
            {
            }
    }
}

auto isEar(js::any ear) {
    const js::any a = ear["prev"];
    const js::any b = ear;
    const js::any c = ear["next"];
    if (area(a, b, c) >= js::number(0)) {
            return false;
    }
    js::any p = ear["next"]["next"];
    while (js::null) {
            {
            }
    }
    return true;
}

auto isEarHashed(js::any ear, js::any minX, js::any minY, js::any invSize) {
    const js::any a = ear["prev"];
    const js::any b = ear;
    const js::any c = ear["next"];
    if (area(a, b, c) >= js::number(0)) {
            return false;
    }
    const js::any x0 = js::Math::min(a["x"], b["x"], c["x"]);
    const js::any y0 = js::Math::min(a["y"], b["y"], c["y"]);
    const js::any x1 = js::Math::max(a["x"], b["x"], c["x"]);
    const js::any y1 = js::Math::max(a["y"], b["y"], c["y"]);
    const js::any minZ = zOrder(x0, y0, minX, minY, invSize);
    const js::any maxZ = zOrder(x1, y1, minX, minY, invSize);
    js::any p = ear["prevZ"];
    js::any n = ear["nextZ"];
    while (js::null) {
            {
            }
    }
    while (js::null) {
            {
            }
    }
    while (js::null) {
            {
            }
    }
    return true;
}

auto cureLocalIntersections(js::any start, js::any createGeometry, js::any dim) {
    js::any p = start;
    js::null;
    return filterPoints(p);
}

auto splitEarcut(js::any start, js::any createGeometry, js::any dim, js::any minX, js::any minY, js::any invSize) {
    js::any a = start;
    js::null;
}

auto eliminateHoles(js::any data, js::any holeIndices, js::any outerNode, js::any dim, js::any a, js::any b) {
    js::array<js::any> queue = js::array<js::any>{};
    for (js::number i = js::number(0);
    js::any len = holeIndices.length(); (i < len); i++) {
            {
                        const js::number start = (holeIndices->i * dim);
                        const js::any end = (js::null ? js::null : js::null);
                        const js::any list = linkedList(data, start, end, dim, false, a, b);
                        if (list === list["next"]) {
                                        list["steiner"] = true;
                        }
                        queue.push(getLeftmost(list));
            }
    }
    queue["sort"](xDifference);
    for (js::number i = js::number(0); (i < queue.length()); i++) {
            {
                        outerNode = eliminateHole(queue[i], outerNode);
                        outerNode = filterPoints(outerNode, outerNode->next);
            }
    }
    return outerNode;
}

auto xDifference(js::any a, js::any b) {
    return (a["x"] - b["x"]);
}

auto eliminateHole(js::any hole, js::any outerNode) {
    const js::any bridge = findHoleBridge(hole, outerNode);
    if (!bridge) {
            {
                        return outerNode;
            }
    }
    const js::any bridgeReverse = splitPolygon(bridge, hole);
    const js::any filtered = filterPoints(bridge, bridge["next"]);
    filterPoints(bridgeReverse, bridgeReverse->next);
    if ((outerNode === outerNode->next || bridge === outerNode)) {
            {
                        return filtered;
            }
    }
    return outerNode;
}

auto findHoleBridge(js::any hole, js::any outerNode) {
    js::any p = outerNode;
    const js::any hx = hole["x"];
    const js::any hy = hole["y"];
    js::any qx = -js::number::POSITIVE_INFINITY;
    auto m;
    js::null;
    if (!m) {
            return js::null;
    }
    if (hx === qx) {
            return m;
    }
    const js::any stop = m;
    const js::any mx = m["x"];
    const js::any my = m["y"];
    js::any tanMin = js::number::POSITIVE_INFINITY;
    p = m;
    js::null;
    return m;
}

auto sectorContainsSector(js::any m, js::any p) {
    return ((area(m["prev"], m, p->prev) < js::number(0)) && (area(p->next, m, m["next"]) < js::number(0)));
}

auto indexCurve(js::any start, js::any minX, js::any minY, js::any invSize) {
    js::any p = start;
    js::null;
    p->prevZ.nextZ = js::null;
    p->prevZ = js::null;
    sortLinked(p);
}

auto sortLinked(js::any list) {
    js::number inSize = js::number(1);
    auto numMerges;
    js::null;
    return list;
}

auto zOrder(js::any x, js::any y, js::any minX, js::any minY, js::any invSize) {
    x = ((js::number(32767) * (x - minX)) * invSize);
    y = ((js::number(32767) * (y - minY)) * invSize);
    x = ((x | (x << js::number(8))) & js::number(16711935));
    x = ((x | (x << js::number(4))) & js::number(252645135));
    x = ((x | (x << js::number(2))) & js::number(858993459));
    x = ((x | (x << js::number(1))) & js::number(1431655765));
    y = ((y | (y << js::number(8))) & js::number(16711935));
    y = ((y | (y << js::number(4))) & js::number(252645135));
    y = ((y | (y << js::number(2))) & js::number(858993459));
    y = ((y | (y << js::number(1))) & js::number(1431655765));
    return (x | (y << js::number(1)));
}

auto getLeftmost(js::any start) {
    js::any p = start;
    js::any leftmost = start;
    js::null;
    return leftmost;
}

auto pointInTriangle(js::any ax, js::any ay, js::any bx, js::any by, js::any cx, js::any cy, js::any px, js::any py) {
    return (((((cx - px) * (ay - py)) - ((ax - px) * (cy - py))) >= js::number(0) && (((ax - px) * (by - py)) - ((bx - px) * (ay - py))) >= js::number(0)) && (((bx - px) * (cy - py)) - ((cx - px) * (by - py))) >= js::number(0));
}

auto isValidDiagonal(js::any a, js::any b) {
    return (((a["next"]["i"] !== b["i"] && a["prev"]["i"] !== b["i"]) && !intersectsPolygon(a, b)) && ((((locallyInside(a, b) && locallyInside(b, a)) && middleInside(a, b)) && (area(a["prev"], a, b["prev"]) || area(a, b["prev"], b))) || ((equals(a, b) && (area(a["prev"], a, a["next"]) > js::number(0))) && (area(b["prev"], b, b["next"]) > js::number(0)))));
}

auto area(js::any p, js::any q, js::any r) {
    return (((q["y"] - p->y) * (r["x"] - q["x"])) - ((q["x"] - p->x) * (r["y"] - q["y"])));
}

auto equals(js::any p1, js::any p2) {
    return (p1["x"] === p2["x"] && p1["y"] === p2["y"]);
}

auto intersects(js::any p1, js::any q1, js::any p2, js::any q2) {
    const js::any o1 = sign(area(p1, q1, p2));
    const js::any o2 = sign(area(p1, q1, q2));
    const js::any o3 = sign(area(p2, q2, p1));
    const js::any o4 = sign(area(p2, q2, q1));
    if ((o1 !== o2 && o3 !== o4)) {
            return true;
    }
    if ((o1 === js::number(0) && onSegment(p1, p2, q1))) {
            return true;
    }
    if ((o2 === js::number(0) && onSegment(p1, q2, q1))) {
            return true;
    }
    if ((o3 === js::number(0) && onSegment(p2, p1, q2))) {
            return true;
    }
    if ((o4 === js::number(0) && onSegment(p2, q1, q2))) {
            return true;
    }
    return false;
}

auto onSegment(js::any p, js::any q, js::any r) {
    return (((q["x"] <= js::Math::max(p->x, r["x"]) && q["x"] >= js::Math::min(p->x, r["x"])) && q["y"] <= js::Math::max(p->y, r["y"])) && q["y"] >= js::Math::min(p->y, r["y"]));
}

auto sign(js::any num) {
    return (js::null ? js::null : js::null);
}

auto intersectsPolygon(js::any a, js::any b) {
    js::any p = a;
    js::null;
    return false;
}

auto locallyInside(js::any a, js::any b) {
    return (js::null ? js::null : js::null);
}

auto middleInside(js::any a, js::any b) {
    js::any p = a;
    bool inside = false;
    const js::number px = ((a["x"] + b["x"]) / js::number(2));
    const js::number py = ((a["y"] + b["y"]) / js::number(2));
    js::null;
    return inside;
}

auto splitPolygon(js::any a, js::any b) {
    const js::any a2 = createNode(a["i"], a["x"], a["y"]);
    const js::any b2 = createNode(b["i"], b["x"], b["y"]);
    const js::any an = a["next"];
    const js::any bp = b["prev"];
    a["next"] = b;
    b["prev"] = a;
    a2["next"] = an;
    an["prev"] = a2;
    b2["next"] = a2;
    a2["prev"] = b2;
    bp["next"] = b2;
    b2["prev"] = bp;
    return b2;
}

auto insertNode(js::any i, js::any x, js::any y, js::any last) {
    const js::any p = createNode(i, x, y);
    if (!last) {
            {
                        p->prev = p;
                        p->next = p;
            }
    } else {
            {
                        p->next = last["next"];
                        p->prev = last;
                        last["next"]["prev"] = p;
                        last["next"] = p;
            }
    }
    return p;
}

auto removeNode(js::any p) {
    p->next.prev = p->prev;
    p->prev.next = p->next;
    if (p->prevZ) {
            p->prevZ.nextZ = p->nextZ;
    }
    if (p->nextZ) {
            p->nextZ.prevZ = p->prevZ;
    }
    p->next = p;
    p->prev = p;
}

auto createNode(js::any i, js::any x, js::any y) {
    return []() {
          js::object obj_temp_0;
          obj_temp_0.set("i", i);
          obj_temp_0.set("x", x);
          obj_temp_0.set("y", y);
          obj_temp_0.set("prev", js::null);
          obj_temp_0.set("next", js::null);
          obj_temp_0.set("z", js::null);
          obj_temp_0.set("prevZ", js::null);
          obj_temp_0.set("nextZ", js::null);
          obj_temp_0.set("steiner", false);
          return js::any(obj_temp_0);
        }();
}

auto signedArea(js::any data, js::any start, js::any end, js::any dim, js::any a, js::any b) {
    js::number sum = js::number(0);
    for (js::any i = start;
    js::number j = (end - dim); (i < end); i += dim) {
            {
                        sum += ((data->(j + a) - data->(i + a)) * (data->(i + b) + data->(j + b)));
                        j = i;
            }
    }
    return sum;
}
