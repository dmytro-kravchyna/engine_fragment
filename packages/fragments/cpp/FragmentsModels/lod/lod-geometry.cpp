#include "index_generated.h"
#include "lod-geometry.h"

using namespace js;

bool LODGeometry::isFiltered() {
    {
            const js::any filter = this->getItemFilter();
            return Boolean(filter);
    }
}

LODGeometry::LODGeometry() : three::InstancedBufferGeometry() {
    {
            LodHelper::setupLodAttributes(this);
    }
}

auto LODGeometry::computeBoundingBox() {
    {
            if (!this->boundingBox) {
                        {
                                        this->boundingBox = std::make_shared<three::Box3>();
                        }
            }
            LodHelper::computeLodBox(this);
    }
}

auto LODGeometry::applyMatrix4(js::any matrix) {
    {
            this->applyTransformToBuffers(matrix);
            this->updateBounds();
            return this;
    }
}

auto LODGeometry::computeBoundingSphere() {
    {
            if (!this->boundingSphere) {
                        {
                                        this->boundingSphere = std::make_shared<three::Sphere>();
                        }
            }
            LodHelper::computeLodSphere(this);
    }
}

auto LODGeometry::getItemFilter() {
    {
            return LodHelper::getInstancedAttribute(this, "itemFilter"_S);
    }
}

auto LODGeometry::getItemLast() {
    {
            return LodHelper::getInterAttribute(this, "itemLast"_S);
    }
}

auto LODGeometry::getItemFirst() {
    {
            return LodHelper::getInterAttribute(this, "itemFirst"_S);
    }
}

auto LODGeometry::applyTransformToBuffers(js::any matrix) {
    {
            const js::any first = this->getItemFirst();
            first["applyMatrix4"](matrix);
            const js::any last = this->getItemLast();
            last["applyMatrix4"](matrix);
    }
}

auto LODGeometry::updateBounds() {
    {
            if (this->boundingBox) {
                        {
                                        this->computeBoundingBox();
                        }
            }
            if (this->boundingSphere) {
                        {
                                        this->computeBoundingSphere();
                        }
            }
    }
}
