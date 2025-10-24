#include "index_generated.h"
#include "transform-helper.h"

using namespace js;

auto TransformHelper::get(Sample sample, Meshes meshes, js::any transform) {
    {
            this->fetchSampleTransform(sample, meshes);
            this->fetchItemTransform(sample, meshes);
            transform["multiplyMatrices"](this->_item, this->_sample);
    }
}

auto TransformHelper::getBox(Representation representation, js::any bbox) {
    {
            representation["bbox"](this->_box);
            ParserHelper::parseBox(this->_box, bbox);
    }
}

auto TransformHelper::getBoxData(js::any bbox) {
    {
            this->_min.copy(bbox["min"]);
            this->_max.copy(bbox["max"]);
            this->_center.addVectors(this->_min, this->_max);
            this->_center.divideScalar(js::number(2));
            bbox["getSize"](this->_distance);
    }
}

auto TransformHelper::boxSize(js::any bbox) {
    {
            this->getBoxData(bbox);
            this->applyTransformer();
            this->_edge.start = this->_min.clone();
            this->_edge.end = this->_max.clone();
            return this->_edge;
    }
}

auto TransformHelper::applyTransformer() {
    {
            auto _temp3306 = this->_distance;
            const auto x = _temp3306["x"];
            const auto y = _temp3306["y"];
            const auto z = _temp3306["z"];
            const js::any max = js::Math::max(x, y, z);
            if (x === max) {
                        {
                                        this->_transformers.x();
                        }
            } else {
                        if (y === max) {
                                        {
                                                            this->_transformers.y();
                                        }
                        } else {
                                        {
                                                            this->_transformers.z();
                                        }
                        }
            }
    }
}

auto TransformHelper::fetchItemTransform(Sample sample, Meshes meshes) {
    {
            const js::any itemId = sample["item"]();
            meshes["globalTransforms"](itemId, this->_transform);
            ParserHelper::parseTransform(this->_transform, this->_item);
    }
}

auto TransformHelper::fetchSampleTransform(Sample sample, Meshes meshes) {
    {
            const js::any localTransformId = sample["localTransform"]();
            meshes["localTransforms"](localTransformId, this->_transform);
            ParserHelper::parseTransform(this->_transform, this->_sample);
    }
}

auto TransformHelper::setBoxZ() {
    {
            this->_min.set(this->_center.x, this->_center.y, this->_min.z);
            this->_max.set(this->_center.x, this->_center.y, this->_max.z);
    }
}

auto TransformHelper::setBoxY() {
    {
            this->_min.set(this->_center.x, this->_min.y, this->_center.z);
            this->_max.set(this->_center.x, this->_max.y, this->_center.z);
    }
}

auto TransformHelper::setBoxX() {
    {
            this->_min.set(this->_min.x, this->_center.y, this->_center.z);
            this->_max.set(this->_max.x, this->_center.y, this->_center.z);
    }
}
