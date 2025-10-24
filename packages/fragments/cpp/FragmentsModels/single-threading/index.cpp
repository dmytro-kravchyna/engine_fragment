#include "index_generated.h"
#include "index.h"

using namespace js;

SingleThreadedFragmentsModel::SingleThreadedFragmentsModel(js::string modelId, js::Uint8Array modelData, auto raw) {
    {
            this->_modelId = modelId;
            js::any data = modelData;
            if (!raw) {
                        {
                                        data = pako["inflate"](modelData);
                        }
            }
            this->_virtualModel = std::make_shared<VirtualFragmentsModel>(modelId, data, js::undefined);
    }
}

auto SingleThreadedFragmentsModel::dispose() {
    {
            this->_virtualModel.dispose();
            this->_virtualModel = js::null;
    }
}

auto SingleThreadedFragmentsModel::getSpatialStructure() {
    {
            return this->_virtualModel.getSpatialStructure();
    }
}

auto SingleThreadedFragmentsModel::getLocalIdsByGuids(js::array<js::string> guids) {
    {
            return this->_virtualModel.getLocalIdsByGuids(guids);
    }
}

auto SingleThreadedFragmentsModel::getCategories() {
    {
            return this->_virtualModel.getCategories();
    }
}

auto SingleThreadedFragmentsModel::getItemsWithGeometry() {
    {
            return this->_virtualModel.getItemsWithGeometry();
    }
}

auto SingleThreadedFragmentsModel::getMetadata() {
    {
            return this->_virtualModel.getMetadata();
    }
}

auto SingleThreadedFragmentsModel::getGuidsByLocalIds(js::array<js::number> localIds) {
    {
            return this->_virtualModel.getGuidsByLocalIds(localIds);
    }
}

auto SingleThreadedFragmentsModel::getBuffer(auto raw) {
    {
            return this->_virtualModel.getBuffer(raw);
    }
}

auto SingleThreadedFragmentsModel::getItemsOfCategories(js::array<RegExp> categories) {
    {
            return this->_virtualModel.getItemsOfCategories(categories);
    }
}

auto SingleThreadedFragmentsModel::getMaxLocalId() {
    {
            return this->_virtualModel.getMaxLocalId();
    }
}

auto SingleThreadedFragmentsModel::getItemsChildren(js::array<Identifier> ids) {
    {
            this->_virtualModel.getItemsChildren(ids);
    }
}

auto SingleThreadedFragmentsModel::getItemsData(js::array<js::number> ids, std::optional<Partial> config) {
    {
            return this->_virtualModel.getItemsData(ids, config);
    }
}

auto SingleThreadedFragmentsModel::getPositions(js::array<js::number> localIds) {
    {
            return this->_virtualModel.getPositions(localIds);
    }
}

auto SingleThreadedFragmentsModel::getCoordinates() {
    {
            return this->_virtualModel.getCoordinates();
    }
}
