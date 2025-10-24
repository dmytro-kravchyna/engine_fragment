#include "index_generated.h"
#include "virtual-box.h"

using namespace js;

VirtualBox::VirtualBox(std::optional<js::number> position, std::optional<DataBuffer> data) {
    {
            this->_dataBuffer = (data || this->getDefaultData());
            this->_dataPosition = (position || VirtualBox::_data::defaultPosition);
    }
}

auto VirtualBox::set(js::array<js::number> values) {
    {
            js::number counter = js::number(0);
            for (const auto& point : VirtualBox::_data::points) {
                        {
                                        for (const auto& coord : VirtualBox::_data::coords) {
                                                            {
                                                                                    const js::any position = this->getPosition(coord, point);
                                                                                    const js::any result = values[counter++];
                                                                                    this->setValue(position, result);
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualBox::get(js::any coord, js::any point) {
    {
            const js::any position = this->getPosition(coord, point);
            return this->_dataBuffer[position];
    }
}

void VirtualBox::clone(VirtualBox box) {
    {
            for (const auto& point : VirtualBox::_data::points) {
                        {
                                        for (const auto& coord : VirtualBox::_data::coords) {
                                                            {
                                                                                    const js::any position = this->getPosition(coord, point);
                                                                                    const js::any result = box["get"](coord, point);
                                                                                    this->setValue(position, result);
                                                            }
                                        }
                        }
            }
    }
}

void VirtualBox::combine(VirtualBox box1, VirtualBox box2) {
    {
            for (const auto& point : VirtualBox::_data::points) {
                        {
                                        for (const auto& coord : VirtualBox::_data::coords) {
                                                            {
                                                                                    this->save(coord, point, box1, box2);
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualBox::setValue(js::number position, js::number value) {
    {
            this->_dataBuffer[position] = value;
    }
}

auto VirtualBox::getDefaultData() {
    {
            return std::make_shared<Float64Array>(VirtualBox::_data::size);
    }
}

auto VirtualBox::getPosition(js::any coord, js::any point) {
    {
            const js::any coordPosition = VirtualBox::_data[point][coord];
            return (coordPosition + this->_dataPosition);
    }
}

auto VirtualBox::save(js::any coord, js::any point, VirtualBox first, VirtualBox second) {
    {
            const js::any position = this->getPosition(coord, point);
            const js::any data1 = first["get"](coord, point);
            const js::any data2 = second["get"](coord, point);
            const js::any result = js::Math[point](data1, data2);
            this->setValue(position, result);
    }
}
