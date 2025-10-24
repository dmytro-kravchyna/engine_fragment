#include "index_generated.h"
#include "virtual-box-maker.h"

using namespace js;

VirtualBoxMaker::VirtualBoxMaker(VirtualBoxController boxes, VirtualBoxCompressor compressor, js::any data) {
    {
            this->_data = data;
            this->_compressor = compressor;
            this->_boxes = boxes;
            this->_sorter = std::make_shared<VirtualBoxSorter>(boxes);
    }
}

js::number VirtualBoxMaker::make(DataBuffer data, VirtualBox bounds, auto a, auto b, auto size, auto result) {
    {
            const js::number distance = (a - b);
            if (distance === js::number(1)) {
                        {
                                        return this->makePoint(data, b, bounds, result);
                        }
            }
            if (distance === js::number(2)) {
                        {
                                        return this->makeGroup3(result, data, b, bounds);
                        }
            }
            return this->makeGroup(size, data, b, a, result, bounds);
    }
}

auto VirtualBoxMaker::makeGroup3(js::number position, DataBuffer data, js::number b, VirtualBox bounds) {
    {
            const js::any box1 = this->makeBox((position + js::number(1)), data, b);
            const js::any box2 = this->makeBox((position + js::number(2)), data, (b + js::number(1)));
            bounds["combine"](box1, box2);
            this->newGroup(position, js::number(3), bounds);
            return js::number(3);
    }
}

auto VirtualBoxMaker::makeGroup(js::number size, DataBuffer data, js::number b, js::number a, js::number position, VirtualBox bounds) {
    {
            const js::any lim1 = this->_data.limits.primary[size];
            const js::any lim2 = this->_data.limits.secondary[size];
            const js::any frontier = this->_sorter.sort(data, b, a);
            const js::any size1 = this->make(data, lim1, frontier, b, (size + js::number(1)), (position + js::number(1)));
            const js::number result2 = ((position + size1) + js::number(1));
            const js::any size2 = this->make(data, lim2, a, frontier, (size + js::number(1)), result2);
            bounds["combine"](lim1, lim2);
            const js::number newSize = ((size1 + size2) + js::number(1));
            this->newGroup(position, newSize, bounds);
            return newSize;
    }
}

auto VirtualBoxMaker::makeBox(js::number position, DataBuffer data, js::number b) {
    {
            const js::any box = this->_data.points[position].box;
            const js::any boxPosition = data->b;
            const js::any boxData = this->_boxes.get(boxPosition);
            this->_compressor.deflate(boxData, box);
            this->set(position, boxPosition);
            return box;
    }
}

auto VirtualBoxMaker::makePoint(DataBuffer data, js::number b, VirtualBox bounds, js::number position) {
    {
            const js::any box = this->_boxes.get(data->b);
            this->_compressor.deflate(box, bounds);
            this->newPoint(position, data->b, bounds);
            return js::number(1);
    }
}

auto VirtualBoxMaker::newGroup(js::number position, js::number size, VirtualBox bounds) {
    {
            const js::any point = this->get(position);
            point["transform"](size, bounds, false);
    }
}

auto VirtualBoxMaker::get(js::number position) {
    {
            return this->_data.points[position];
    }
}

auto VirtualBoxMaker::newPoint(js::number position, js::number value, VirtualBox bounds) {
    {
            const js::any point = this->get(position);
            point["transform"](value, bounds, true);
    }
}

auto VirtualBoxMaker::set(js::number position, js::number data) {
    {
            const js::any point = this->get(position);
            point["data"] = data;
    }
}
