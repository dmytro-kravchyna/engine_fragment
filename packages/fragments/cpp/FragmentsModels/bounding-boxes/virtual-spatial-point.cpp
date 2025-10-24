#include "index_generated.h"
#include "virtual-spatial-point.h"

using namespace js;

VirtualSpatialPoint::VirtualSpatialPoint(js::number position, DataBuffer data) {
    {
            this->box = std::make_shared<VirtualBox>(position, data);
    }
}

auto VirtualSpatialPoint::transform(js::number size, VirtualBox box, bool group) {
    {
            if (!group) {
                        {
                                        size *= VirtualSpatialPoint::_data::factor;
                        }
            }
            this->data = size;
            this->box.clone(box);
    }
}
