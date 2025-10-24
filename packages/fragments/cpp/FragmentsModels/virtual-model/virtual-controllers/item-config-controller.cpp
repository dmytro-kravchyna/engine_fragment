#include "index_generated.h"
#include "item-config-controller.h"

using namespace js;

ItemConfigController::ItemConfigController(js::number size) {
    {
            this->size = size;
            this->_data = std::make_shared<Uint8Array>(size);
            this->_highlightData = std::make_shared<Uint16Array>(size);
            this->_data.fill(js::number(1));
    }
}

js::number ItemConfigController::getHighlight(js::number id) {
    {
            return this->_highlightData[id];
    }
}

auto ItemConfigController::setHighlight(js::number id, js::number highlightId) {
    {
            BitUtils::checkMemory(highlightId);
            this->_highlightData[id] = highlightId;
    }
}

auto ItemConfigController::clearHighlight() {
    {
            this->_highlightData.fill(js::number(0));
    }
}

bool ItemConfigController::visible(js::number id) {
    {
            return BitUtils::check(this->_data, id, ItemConfigClass::VISIBLE);
    }
}

auto ItemConfigController::setVisible(js::number id, bool visible) {
    {
            BitUtils::apply(this->_data, id, ItemConfigClass::VISIBLE, visible);
    }
}

auto ItemConfigController::clearVisible() {
    {
            this->_data.fill(js::number(1));
    }
}
