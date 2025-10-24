#include "index_generated.h"
#include "profile.h"

using namespace js;

Profile::Profile(Plane plane) {
    {
            this->plane = plane;
    }
}

auto Profile::getEdges(bool reverse) {
    {
            js::array<Edge> edges = js::array<js::any>{};
            if (reverse) {
                        {
                                        for (js::number i = (this->orderedPoints.length() - js::number(1)); (i > js::number(0)); i--) {
                                                            {
                                                                                    edges.push(std::make_shared<Edge>(this->orderedPoints[i], this->orderedPoints[(i - js::number(1))]));
                                                            }
                                        }
                        }
            } else {
                        {
                                        for (js::number i = js::number(0); (i < (this->orderedPoints.length() - js::number(1))); i++) {
                                                            {
                                                                                    edges.push(std::make_shared<Edge>(this->orderedPoints[i], this->orderedPoints[(i + js::number(1))]));
                                                            }
                                        }
                        }
            }
            return edges;
    }
}

auto Profile::getIndices() {
    {
            return this->orderedPoints.map([&](auto p) -> auto { return p->id; });
    }
}

auto Profile::add(Edge edge) {
    {
            if (this->orderedPoints.length() === js::number(0)) {
                        {
                                        this->openStartPoint = edge["p1"]["hash"];
                                        this->openEndPoint = edge["p2"]["hash"];
                                        this->orderedPoints.push(edge["p1"], edge["p2"]);
                                        return;
                        }
            }
            const js::any matches = this->match(edge);
            if (matches === js::number(0)) {
                        {
                                        throw js::any(js::Error("Fragments: Edge doesn't match with any open point"_S));
                        }
            }
            if ((matches > js::number(2))) {
                        {
                                        throw js::any(js::Error("Fragments: Edge matches with more than 2 open points"_S));
                        }
            }
            if (matches === js::number(2)) {
                        {
                                        this->closed = true;
                                        this->openEndPoint = js::null;
                                        this->openStartPoint = js::null;
                                        return;
                        }
            }
            if (this->openStartPoint === edge["p1"]["hash"]) {
                        {
                                        this->orderedPoints.unshift(edge["p2"]);
                                        this->openStartPoint = edge["p2"]["hash"];
                        }
            } else {
                        if (this->openEndPoint === edge["p1"]["hash"]) {
                                        {
                                                            this->orderedPoints.push(edge["p2"]);
                                                            this->openEndPoint = edge["p2"]["hash"];
                                        }
                        } else {
                                        if (this->openStartPoint === edge["p2"]["hash"]) {
                                                            {
                                                                                    this->orderedPoints.unshift(edge["p1"]);
                                                                                    this->openStartPoint = edge["p1"]["hash"];
                                                            }
                                        } else {
                                                            if (this->openEndPoint === edge["p2"]["hash"]) {
                                                                                    {
                                                                                                                this->orderedPoints.push(edge["p1"]);
                                                                                                                this->openEndPoint = edge["p1"]["hash"];
                                                                                    }
                                                            }
                                        }
                        }
            }
    }
}

auto Profile::match(Edge edge) {
    {
            if (this->closed) {
                        return js::number(0);
            }
            js::number matchNumber = js::number(0);
            if (this->openStartPoint === edge["p1"]["hash"]) {
                        matchNumber++;
            }
            if (this->openStartPoint === edge["p2"]["hash"]) {
                        matchNumber++;
            }
            if (this->openEndPoint === edge["p1"]["hash"]) {
                        matchNumber++;
            }
            if (this->openEndPoint === edge["p2"]["hash"]) {
                        matchNumber++;
            }
            return matchNumber;
    }
}

auto Profile::merge(Profile newProfile) {
    {
            if ((newProfile->closed || this->closed)) {
                        {
                                        throw js::any(js::Error("Fragments: Cannot merge closed profiles"_S));
                        }
            }
            if ((newProfile->openStartPoint === this->openEndPoint && newProfile->openEndPoint === this->openStartPoint)) {
                        {
                                        throw js::any(js::Error("Fragments: Cannot merge profiles that close each other"_S));
                        }
            }
            if ((newProfile->openEndPoint === this->openEndPoint && newProfile->openStartPoint === this->openStartPoint)) {
                        {
                                        throw js::any(js::Error("Fragments: Cannot merge profiles that close each other"_S));
                        }
            }
            bool reverse = false;
            if ((newProfile->openEndPoint === this->openStartPoint || newProfile->openEndPoint === this->openEndPoint)) {
                        {
                                        reverse = true;
                        }
            }
            const js::any newEdges = newProfile->getEdges(reverse);
            for (const auto& edge : newEdges) {
                        {
                                        this->add(edge);
                        }
            }
    }
}

auto Profile::getArea() {
    {
            const js::any vertices = this->orderedPoints.map([&](auto p) -> auto { return js::array<js::any>{p->x, p->y, p->z}; });
            js::number dimension1 = js::number(0);
            js::number dimension2 = js::number(1);
            const js::any absX = js::Math::abs(this->plane.normal.x);
            const js::any absY = js::Math::abs(this->plane.normal.y);
            const js::any absZ = js::Math::abs(this->plane.normal.z);
            if ((absX >= absY && absX >= absZ)) {
                        {
                                        dimension1 = js::number(1);
                                        dimension2 = js::number(2);
                        }
            } else {
                        if ((absY >= absX && absY >= absZ)) {
                                        {
                                                            dimension1 = js::number(0);
                                                            dimension2 = js::number(2);
                                        }
                        } else {
                                        {
                                                            dimension1 = js::number(0);
                                                            dimension2 = js::number(1);
                                        }
                        }
            }
            js::array<unknown> projectedPoints = js::array<js::any>{};
            for (const auto& point : vertices) {
                        {
                                        projectedPoints.push(std::make_shared<three::Vector2>(point[dimension1], point[dimension2]));
                        }
            }
            js::number total = js::number(0);
            for (js::number i = js::number(0);
            js::any l = projectedPoints.length(); (i < l); i++) {
                        {
                                        const js::any addX = projectedPoints->i->x;
                                        const js::any addY = projectedPoints->(js::null ? js::null : js::null)->y;
                                        const js::any subX = projectedPoints->(js::null ? js::null : js::null)->x;
                                        const js::any subY = projectedPoints->i->y;
                                        total += ((addX * addY) * js::number(0.5));
                                        total -= ((subX * subY) * js::number(0.5));
                        }
            }
            return js::Math::abs(total);
    }
}
