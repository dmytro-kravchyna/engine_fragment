#include "index_generated.h"
#include "points.h"

using namespace js;

Points::Points(js::number precission) {
    {
            this->precission = precission;
    }
}

auto Points::create(js::Float32Array vertices, js::number index) {
    {
            const std::shared_ptr<Point> point = std::make_shared<Point>(vertices, index, this->list.size, this->precission);
            if (!this->list.has(point["hash"])) {
                        {
                                        this->list.set(point["hash"], point);
                        }
            }
            return this->list.get(point["hash"]);
    }
}

auto Points::get() {
    {
            return js::array.from(this->list.values()).map([&](auto p) -> auto { return js::array<js::any>{p->x, p->y, p->z}; });
    }
}

auto Points::isValidTriangle(js::Float32Array position, js::number index1, js::number index2, js::number index3) {
    {
            this->tempV1.set(position[(index1 * js::number(3))], position[((index1 * js::number(3)) + js::number(1))], position[((index1 * js::number(3)) + js::number(2))]);
            this->tempV2.set(position[(index2 * js::number(3))], position[((index2 * js::number(3)) + js::number(1))], position[((index2 * js::number(3)) + js::number(2))]);
            this->tempV3.set(position[(index3 * js::number(3))], position[((index3 * js::number(3)) + js::number(1))], position[((index3 * js::number(3)) + js::number(2))]);
            const js::number pointPrecision = ((js::number(1) / this->precission) * js::number(10));
            const bool d1Valid = (this->tempV1.distanceTo(this->tempV2) > pointPrecision);
            const bool d2Valid = (this->tempV1.distanceTo(this->tempV3) > pointPrecision);
            const bool d3Valid = (this->tempV2.distanceTo(this->tempV3) > pointPrecision);
            return ((d1Valid && d2Valid) && d3Valid);
    }
}
