#include "index_generated.h"
#include "point.h"

using namespace js;

Point::Point(js::Float32Array vertices, js::number index, js::number id, js::number precission) {
    {
            this->x = round(vertices[(index * js::number(3))], precission);
            this->y = round(vertices[((index * js::number(3)) + js::number(1))], precission);
            this->z = round(vertices[((index * js::number(3)) + js::number(2))], precission);
            this->hash = (js::toString(this->x) + "/"_S + js::toString(this->y) + "/"_S + js::toString(this->z));
            this->id = id;
    }
}
