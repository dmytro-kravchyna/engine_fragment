#ifndef VIRTUAL_BOX_CONTROLLER_H
#define VIRTUAL_BOX_CONTROLLER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include <three.h>
#include "./virtual-box-structure.h"
#include "../../../Schema.h"
#include "../utils.h"
#include "../model/model-types.h"

using namespace js;

// Forward declarations
class VirtualBoxController;

class VirtualBoxController {
public:
    std::shared_ptr<VirtualBoxStructure> lookup;
    VirtualBoxController(Model fragments);
    virtual js::typed::Nullable<js::array<js::number>> sampleOf(js::number id);
    virtual js::any get(js::number id);
    virtual void process(js::number id);
    virtual auto getCount();
    virtual auto dimensionOf(js::number id);
private:
    auto _boxSize;
    auto _pointSize;
    js::any _temp;
    std::shared_ptr<DataBuffer> _dimensionsOfSamples;
    js::array<js::array<js::number>> _samples;
    std::shared_ptr<DataBuffer> _boxes;
    std::shared_ptr<Meshes> _meshes;
    js::any _box;
    virtual auto newLookup();
    virtual auto getBox();
    virtual auto fetchSampleAndRepresentation(js::number id);
    virtual auto getMinPosition(js::number id);
    virtual auto storeBox(js::number id);
    virtual auto getMaxPosition(js::number id);
    virtual auto addToFullBox();
};

#endif // VIRTUAL_BOX_CONTROLLER_H