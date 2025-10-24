#include "index_generated.h"
#include "virtual-box-sorter.h"

using namespace js;

VirtualBoxSorter::VirtualBoxSorter(VirtualBoxController boxes) {
    {
            this->_boxes = boxes;
    }
}

auto VirtualBoxSorter::sort(DataBuffer dataBuffer, js::number a, js::number b) {
    {
            this->average(this->_average, dataBuffer, a, b);
            this->getDataToTotal(a, b, dataBuffer);
            js::any result = this->anySort(a, b, dataBuffer);
            result = this->adjust(b, a, result);
            return js::Math::round(result);
    }
}

auto VirtualBoxSorter::anySort(js::number a, js::number b, DataBuffer dataBuffer) {
    {
            if ((this->_total.x > this->_total.y)) {
                        {
                                        if ((this->_total.x > this->_total.z)) {
                                                            {
                                                                                    return this->sortDim("x"_S, this->_average.x, a, b, dataBuffer);
                                                            }
                                        }
                                        return this->sortDim("z"_S, this->_average.z, a, b, dataBuffer);
                        }
            }
            if ((this->_total.y > this->_total.z)) {
                        {
                                        return this->sortDim("y"_S, this->_average.y, a, b, dataBuffer);
                        }
            }
            return this->sortDim("z"_S, this->_average.z, a, b, dataBuffer);
    }
}

auto VirtualBoxSorter::getDataToTotal(js::number a, js::number b, DataBuffer dataBuffer) {
    {
            this->_total.set(js::number(0), js::number(0), js::number(0));
            for (js::any i = a; (i < b); i++) {
                        {
                                        const js::any box = this->_boxes.get(dataBuffer->i);
                                        box["getCenter"](this->_change).sub(this->_average);
                                        const js::any deltaSquared = this->_change.multiply(this->_change);
                                        this->_total.add(deltaSquared);
                        }
            }
    }
}

auto VirtualBoxSorter::sortDim(js::any dimension, js::number threshold, js::number first, js::number second, DataBuffer elements) {
    {
            js::any position = first;
            for (js::any i = first; (i < second); i++) {
                        {
                                        const js::any value = this->getValue(elements, i, dimension);
                                        if ((value > threshold)) {
                                                            {
                                                                                    this->exchange(i, position, elements);
                                                                                    position++;
                                                            }
                                        }
                        }
            }
            return position;
    }
}

auto VirtualBoxSorter::exchange(js::number first, js::number second, DataBuffer elements) {
    {
            const js::any value = elements[first];
            elements[first] = elements[second];
            elements[second] = value;
    }
}

auto VirtualBoxSorter::getValue(DataBuffer elements, js::number i, js::any dimension) {
    {
            const js::any box = this->getBox(elements, i);
            const js::any vector = this->_tempVectors[dimension];
            const js::any value = box["getCenter"](vector)[dimension];
            return value;
    }
}

auto VirtualBoxSorter::average(js::any result, DataBuffer elements, js::number first, js::number second) {
    {
            const js::any box = this->getBox(elements, first);
            box["getCenter"](result);
            this->aggregate(first, second, elements, box, result);
            return result->divideScalar((second - first));
    }
}

auto VirtualBoxSorter::aggregate(js::number first, js::number second, DataBuffer elements, js::any box, js::any result) {
    {
            for (js::number i = (first + js::number(1)); (i < second); i++) {
                        {
                                        const js::any current = elements[i];
                                        box = this->_boxes.get(current);
                                        const js::any center = box["getCenter"](this->_tempCenterVector);
                                        result->add(center);
                        }
            }
    }
}

auto VirtualBoxSorter::adjust(js::number b, js::number a, js::number result) {
    {
            const js::number correction = ((a + b) / js::number(2));
            const js::number diff = (b - a);
            const js::number factor = (diff / js::number(3));
            if (result <= (a + factor)) {
                        {
                                        result = correction;
                        }
            } else {
                        if (result >= ((b - js::number(1)) - factor)) {
                                        {
                                                            result = correction;
                                        }
                        }
            }
            return result;
    }
}

auto VirtualBoxSorter::getBox(DataBuffer elements, js::number index) {
    {
            const js::any selected = elements[index];
            return this->_boxes.get(selected);
    }
}
