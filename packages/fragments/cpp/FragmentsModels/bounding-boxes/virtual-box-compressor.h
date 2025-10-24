#ifndef VIRTUAL_BOX_COMPRESSOR_H
#define VIRTUAL_BOX_COMPRESSOR_H

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
#include "./virtual-box.h"
#include "./virtual-box-controller.h"

using namespace js;

// Forward declarations
class VirtualBoxCompressor;

class VirtualBoxCompressor {
public:
    VirtualBoxCompressor(VirtualBoxController boxes);
    virtual js::any inflate(VirtualBox bounds);
    virtual auto deflate(js::any bounds, VirtualBox result);
private:
    std::shared_ptr<VirtualBoxController> _boxes;
    auto _min;
    auto _max;
    virtual auto getVector(VirtualBox bounds, js::any offset, js::any value);
    virtual auto read(js::any bounds);
};

#endif // VIRTUAL_BOX_COMPRESSOR_H