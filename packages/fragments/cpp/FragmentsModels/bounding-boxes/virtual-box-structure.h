#ifndef VIRTUAL_BOX_STRUCTURE_H
#define VIRTUAL_BOX_STRUCTURE_H

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
#include "./virtual-spatial-point.h"
#include "./virtual-box.h"
#include "./virtual-box-controller.h"
#include "./virtual-box-compressor.h"
#include "./virtual-box-collider.h"
#include "./virtual-box-maker.h"

using namespace js;

// Forward declarations
class VirtualBoxStructure;

class VirtualBoxStructure {
public:
    VirtualBoxStructure(VirtualBoxController boxes);
    virtual js::array<js::number> collideFrustum(js::array<unknown> bounds, js::any frustum, auto fullyIncluded = false);
    virtual js::array<js::number> collideRay(js::array<unknown> bounds, js::any beam);
private:
    auto _boxSize;
    auto _limitThreshold;
    std::shared_ptr<VirtualBoxCompressor> _compressor;
    std::shared_ptr<VirtualBoxCollider> _collider;
    std::shared_ptr<VirtualBoxMaker> _maker;
    js::any _data;
    std::shared_ptr<VirtualBoxController> _boxes;
    virtual auto setupLimits();
    virtual auto getPointBuffer();
    virtual auto getPointsAmount(js::Uint32Array pointBuffer);
    virtual auto initData();
    virtual auto getData();
};

#endif // VIRTUAL_BOX_STRUCTURE_H