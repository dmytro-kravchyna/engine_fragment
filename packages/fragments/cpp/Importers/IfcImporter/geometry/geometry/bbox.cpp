#include "index_generated.h"
#include "bbox.h"

using namespace js;

auto getAABB(js::any vertices) {
    js::any minX = Number::POSITIVE_INFINITY;
    js::any minY = Number::POSITIVE_INFINITY;
    js::any minZ = Number::POSITIVE_INFINITY;
    js::any maxX = Number::NEGATIVE_INFINITY;
    js::any maxY = Number::NEGATIVE_INFINITY;
    js::any maxZ = Number::NEGATIVE_INFINITY;
    for (js::number i = js::number(0); (i < vertices.length()); i += js::number(3)) {
            {
                        const js::any x = vertices[i];
                        const js::any y = vertices[(i + js::number(1))];
                        const js::any z = vertices[(i + js::number(2))];
                        if ((x < minX)) {
                                        minX = x;
                        }
                        if ((y < minY)) {
                                        minY = y;
                        }
                        if ((z < minZ)) {
                                        minZ = z;
                        }
                        if ((x > maxX)) {
                                        maxX = x;
                        }
                        if ((y > maxY)) {
                                        maxY = y;
                        }
                        if ((z > maxZ)) {
                                        maxZ = z;
                        }
            }
    }
    return []() {
          js::object obj_temp_0;
          obj_temp_0.set("min", []() {
          js::object obj_temp_1;
          obj_temp_1.set("x", minX);
          obj_temp_1.set("y", minY);
          obj_temp_1.set("z", minZ);
          return js::any(obj_temp_1);
        }());
          obj_temp_0.set("max", []() {
          js::object obj_temp_2;
          obj_temp_2.set("x", maxX);
          obj_temp_2.set("y", maxY);
          obj_temp_2.set("z", maxZ);
          return js::any(obj_temp_2);
        }());
          return js::any(obj_temp_0);
        }();
}
