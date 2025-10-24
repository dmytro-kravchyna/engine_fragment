#include "index_generated.h"
#include "virtual-box-structure.h"

using namespace js;

VirtualBoxStructure::VirtualBoxStructure(VirtualBoxController boxes) {
    {
            this->_boxes = boxes;
            this->_compressor = std::make_shared<VirtualBoxCompressor>(boxes);
            this->_data = this->getData();
            this->_collider = std::make_shared<VirtualBoxCollider>(this->_compressor, this->_data);
            this->_maker = std::make_shared<VirtualBoxMaker>(this->_boxes, this->_compressor, this->_data);
            this->initData();
    }
}

js::array<js::number> VirtualBoxStructure::collideFrustum(js::array<unknown> bounds, js::any frustum, auto fullyIncluded) {
    {
            return this->_collider.frustumCollide(bounds, frustum, fullyIncluded);
    }
}

js::array<js::number> VirtualBoxStructure::collideRay(js::array<unknown> bounds, js::any beam) {
    {
            return this->_collider.rayCollide(bounds, beam);
    }
}

auto VirtualBoxStructure::setupLimits() {
    {
            for (js::number i = js::number(0); (i < VirtualBoxStructure::_limitThreshold); i++) {
                        {
                                        this->_data.limits.primary.push(std::make_shared<VirtualBox>());
                                        this->_data.limits.secondary.push(std::make_shared<VirtualBox>());
                        }
            }
    }
}

auto VirtualBoxStructure::getPointBuffer() {
    {
            const js::any count = this->_boxes.getCount();
            const std::shared_ptr<Uint32Array> pointBuffer = std::make_shared<Uint32Array>(count);
            for (js::number i = js::number(0); (i < pointBuffer.length()); i++) {
                        {
                                        pointBuffer->i = i;
                        }
            }
            return pointBuffer;
    }
}

auto VirtualBoxStructure::getPointsAmount(js::Uint32Array pointBuffer) {
    {
            const js::number result = (pointBuffer.length() * js::number(2));
            return (result - js::number(1));
    }
}

auto VirtualBoxStructure::initData() {
    {
            const js::any pointBuffer = this->getPointBuffer();
            const js::any pointsAmount = this->getPointsAmount(pointBuffer);
            const js::number size = (pointsAmount * VirtualBoxStructure::_boxSize);
            const std::shared_ptr<Float64Array> data = std::make_shared<Float64Array>(size);
            for (js::number i = js::number(0); (i < pointsAmount); i++) {
                        {
                                        const js::number position = (i * VirtualBoxStructure::_boxSize);
                                        const std::shared_ptr<VirtualSpatialPoint> newPoint = std::make_shared<VirtualSpatialPoint>(position, data);
                                        this->_data.points.push(newPoint);
                        }
            }
            this->setupLimits();
            const std::shared_ptr<VirtualBox> root = std::make_shared<VirtualBox>();
            this->_maker.make(pointBuffer, root, pointBuffer.length());
    }
}

auto VirtualBoxStructure::getData() {
    {
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("points", js::array<js::any>{});
                  obj_temp_0.set("limits", []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("primary", js::array<js::any>{});
                  obj_temp_1.set("secondary", js::array<js::any>{});
                  return js::any(obj_temp_1);
                }());
                  return js::any(obj_temp_0);
                }();
    }
}
