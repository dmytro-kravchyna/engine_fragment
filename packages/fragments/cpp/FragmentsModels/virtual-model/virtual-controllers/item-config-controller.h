#ifndef ITEM_CONFIG_CONTROLLER_H
#define ITEM_CONFIG_CONTROLLER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../../model/model-types.h"
#include "../../utils.h"

using namespace js;

// Forward declarations
class ItemConfigController;

class ItemConfigController {
public:
    js::number size;
    ItemConfigController(js::number size);
    virtual js::number getHighlight(js::number id);
    virtual auto setHighlight(js::number id, js::number highlightId);
    virtual auto clearHighlight();
    virtual bool visible(js::number id);
    virtual auto setVisible(js::number id, bool visible);
    virtual auto clearVisible();
private:
    std::shared_ptr<DataBuffer> _data;
    std::shared_ptr<DataBuffer> _highlightData;
};

#endif // ITEM_CONFIG_CONTROLLER_H