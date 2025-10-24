#ifndef VIRTUAL_BOX_MAKER_H
#define VIRTUAL_BOX_MAKER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../model/model-types.h"
#include "./virtual-box.h"
#include "./virtual-box-compressor.h"
#include "./virtual-box-controller.h"
#include "./virtual-box-sorter.h"
#include "./virtual-spatial-point.h"

using namespace js;

// Forward declarations
class VirtualBoxMaker;

class VirtualBoxMaker {
public:
    VirtualBoxMaker(VirtualBoxController boxes, VirtualBoxCompressor compressor, js::any data);
    virtual js::number make(DataBuffer data, VirtualBox bounds, auto a = js::number(0), auto b = js::number(0), auto size = js::number(0), auto result = js::number(0));
private:
    auto _data;
    std::shared_ptr<VirtualBoxCompressor> _compressor;
    std::shared_ptr<VirtualBoxController> _boxes;
    std::shared_ptr<VirtualBoxSorter> _sorter;
    virtual auto makeGroup3(js::number position, DataBuffer data, js::number b, VirtualBox bounds);
    virtual auto makeGroup(js::number size, DataBuffer data, js::number b, js::number a, js::number position, VirtualBox bounds);
    virtual auto makeBox(js::number position, DataBuffer data, js::number b);
    virtual auto makePoint(DataBuffer data, js::number b, VirtualBox bounds, js::number position);
    virtual auto newGroup(js::number position, js::number size, VirtualBox bounds);
    virtual auto get(js::number position);
    virtual auto newPoint(js::number position, js::number value, VirtualBox bounds);
    virtual auto set(js::number position, js::number data);
};

#endif // VIRTUAL_BOX_MAKER_H