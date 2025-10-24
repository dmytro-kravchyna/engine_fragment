#ifndef VIRTUAL_TEMPLATE_CONTROLLER_H
#define VIRTUAL_TEMPLATE_CONTROLLER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../virtual-meshes.h"

using namespace js;

// Forward declarations
class VirtualTemplateController;

class VirtualTemplateController {
public:
    VirtualTemplateController() = default;
    virtual auto add(js::number code, AnyTileBasicData template);
    virtual auto get(js::number code);
private:
    std::shared_ptr<VirtualTemplates> _templates;
    virtual auto getTemplateSet(js::array<TileBasicData> templates);
};

#endif // VIRTUAL_TEMPLATE_CONTROLLER_H