#include "index_generated.h"
#include "edge.h"

using namespace js;

Edge::Edge(Point p1, Point p2) {
    {
            this->p1 = p1;
            this->p2 = p2;
            js::array<js::any> points = js::array<js::any>{this->p1, this->p2};
            points["sort"]([&](auto a, auto b) -> auto { return (((a["x"] - b["x"]) || (a["y"] - b["y"])) || (a["z"] - b["z"])); });
            this->hash = (js::toString(points[js::number(0)].hash) + "_"_S + js::toString(points[js::number(1)].hash));
    }
}
