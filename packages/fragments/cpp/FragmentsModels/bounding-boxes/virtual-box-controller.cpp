#include "index_generated.h"
#include "virtual-box-controller.h"

using namespace js;

VirtualBoxController::VirtualBoxController(Model fragments) {
    {
            this->_temp = []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("box", std::make_shared<three::Box3>());
                  obj_temp_0.set("vector", std::make_shared<three::Vector3>());
                  obj_temp_0.set("transform", std::make_shared<three::Matrix4>());
                  obj_temp_0.set("sample", std::make_shared<Sample>());
                  obj_temp_0.set("representation", std::make_shared<Representation>());
                  return js::any(obj_temp_0);
                }();
            this->_box = std::make_shared<three::Box3>();
            const js::any meshes = fragments["meshes"]();
            if (!meshes) {
                        {
                                        throw js::any(js::Error("Fragments: Malformed fragments data!"_S));
                        }
            }
            this->_meshes = meshes;
            const js::any sampleCount = meshes["samplesLength"]();
            this->_dimensionsOfSamples = std::make_shared<Float32Array>(sampleCount);
            const js::number boxSize = (sampleCount * this->_boxSize);
            this->_boxes = std::make_shared<Float64Array>(boxSize);
            this->lookup = this->newLookup();
    }
}

js::typed::Nullable<js::array<js::number>> VirtualBoxController::sampleOf(js::number id) {
    {
            return this->_samples[id];
    }
}

js::any VirtualBoxController::get(js::number id) {
    {
            const js::any minPosition = this->getMinPosition(id);
            const js::any maxPosition = this->getMaxPosition(id);
            this->_temp.box.min.fromArray(this->_boxes, minPosition);
            this->_temp.box.max.fromArray(this->_boxes, maxPosition);
            return this->_temp.box;
    }
}

void VirtualBoxController::process(js::number id) {
    {
            this->fetchSampleAndRepresentation(id);
            this->getBox();
            this->addToFullBox();
            const js::any minPosition = this->getMinPosition(id);
            const js::any maxPosition = this->getMaxPosition(id);
            this->_temp.box.min.toArray(this->_boxes, minPosition);
            this->_temp.box.max.toArray(this->_boxes, maxPosition);
    }
}

auto VirtualBoxController::getCount() {
    {
            return (this->_boxes.length() / this->_boxSize);
    }
}

auto VirtualBoxController::dimensionOf(js::number id) {
    {
            const js::any dimension = this->_dimensionsOfSamples[id];
            if (!dimension) {
                        {
                                        throw js::any(js::Error("Fragments: Dimension not found!"_S));
                        }
            }
            return dimension;
    }
}

auto VirtualBoxController::newLookup() {
    {
            const js::any sampleCount = this->_meshes.samplesLength();
            const js::any itemsCount = this->_meshes.globalTransformsLength();
            for (js::number i = js::number(0); (i < sampleCount); i++) {
                        {
                                        this->fetchSampleAndRepresentation(i);
                                        TransformHelper::getBox(this->_temp.representation, this->_temp.box);
                                        const js::any dimension = this->_temp.box.getSize(this->_temp.vector);
                                        this->_dimensionsOfSamples[i] = dimension.length()();
                                        this->process(i);
                        }
            }
            this->_samples = std::make_shared<js::array>(itemsCount);
            for (js::number i = js::number(0); (i < sampleCount); i++) {
                        {
                                        this->storeBox(i);
                        }
            }
            if (!this->getCount()) {
                        {
                                        throw js::any(js::Error("Fragments: Malformed boxes!"_S));
                        }
            }
            return std::make_shared<VirtualBoxStructure>(this);
    }
}

auto VirtualBoxController::getBox() {
    {
            TransformHelper::get(this->_temp.sample, this->_meshes, this->_temp.transform);
            TransformHelper::getBox(this->_temp.representation, this->_temp.box);
            this->_temp.box.applyMatrix4(this->_temp.transform);
    }
}

auto VirtualBoxController::fetchSampleAndRepresentation(js::number id) {
    {
            this->_meshes.samples(id, this->_temp.sample);
            const js::any representationId = this->_temp.sample.representation();
            this->_meshes.representations(representationId, this->_temp.representation);
    }
}

auto VirtualBoxController::getMinPosition(js::number id) {
    {
            return (id * this->_boxSize);
    }
}

auto VirtualBoxController::storeBox(js::number id) {
    {
            this->fetchSampleAndRepresentation(id);
            const js::any sampleId = this->_temp.sample.item();
            if (this->_samples[sampleId] === js::undefined) {
                        {
                                        this->_samples[sampleId] = js::array<js::any>{};
                        }
            }
            this->_samples[sampleId].push(id);
    }
}

auto VirtualBoxController::getMaxPosition(js::number id) {
    {
            return ((id * this->_boxSize) + this->_pointSize);
    }
}

auto VirtualBoxController::addToFullBox() {
    {
            this->fullBox.union(this->_temp.box);
    }
}
