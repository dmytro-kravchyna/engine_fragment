#include "index_generated.h"
#include "virtual-box-compressor.h"

using namespace js;

VirtualBoxCompressor::VirtualBoxCompressor(VirtualBoxController boxes) {
    {
            this->_boxes = boxes;
    }
}

js::any VirtualBoxCompressor::inflate(VirtualBox bounds) {
    {
            const js::any offset = this->_boxes.fullBox.min;
            const js::any min = this->getVector(bounds, offset, "min"_S);
            const js::any max = this->getVector(bounds, offset, "max"_S);
            return std::make_shared<three::Box3>(min, max);
    }
}

auto VirtualBoxCompressor::deflate(js::any bounds, VirtualBox result) {
    {
            this->read(bounds);
            js::array<js::number> data = js::array<js::any>{};
            data.push(this->_min.x, this->_min.y, this->_min.z);
            data.push(this->_max.x, this->_max.y, this->_max.z);
            result->set(data);
    }
}

auto VirtualBoxCompressor::getVector(VirtualBox bounds, js::any offset, js::any value) {
    {
            const js::number x = (bounds["get"]("x"_S, value) + offset["x"]);
            const js::number y = (bounds["get"]("y"_S, value) + offset["y"]);
            const js::number z = (bounds["get"]("z"_S, value) + offset["z"]);
            return std::make_shared<three::Vector3>(x, y, z);
    }
}

auto VirtualBoxCompressor::read(js::any bounds) {
    {
            auto _temp397 = this->_boxes.fullBox;
            const auto min = _temp397["min"];
            this->_min.subVectors(bounds["min"], min);
            this->_max.subVectors(bounds["max"], min);
    }
}
