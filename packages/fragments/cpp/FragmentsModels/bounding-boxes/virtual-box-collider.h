#ifndef VIRTUAL_BOX_COLLIDER_H
#define VIRTUAL_BOX_COLLIDER_H

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
#include "../utils.h"
#include "./virtual-spatial-point.h"
#include "./virtual-box-compressor.h"

using namespace js;

// Forward declarations
class VirtualBoxCollider;

class VirtualBoxCollider {
public:
    VirtualBoxCollider(VirtualBoxCompressor compressor, js::any data);
    virtual js::array<js::number> frustumCollide(js::array<unknown> bounds, js::any frustum, auto fullyIncluded = false);
    virtual js::array<js::number> rayCollide(js::array<unknown> bounds, js::any ray);
private:
    auto _data;
    std::shared_ptr<VirtualBoxCompressor> _compressor;
    virtual auto addPoint(bool fullyIncluded, js::array<js::number> result, js::number currentPosition, bool includes);
    virtual js::number getPointData(js::number position);
    virtual js::any getBounds(js::number position);
    virtual bool isPoint(js::number position);
    virtual auto newDefaultCallback(bool value);
    virtual js::number groupSize(js::number position);
    virtual auto getPoint(js::number position);
    virtual auto getRayOnSeen(js::array<unknown> bounds);
    virtual auto getRayOnCollide(js::any beam);
    virtual js::array<js::number> collide(BoxEvent onCollide, BoxEvent onIncludes, BoxEvent onSeen, auto fullyIncluded = false);
    virtual auto getFrustumOnIncludes(js::array<unknown> planes);
    virtual auto getFrustumOnCollide(js::array<unknown> planes);
    virtual auto getFrustumPlanes(js::any frustum, js::array<unknown> bounds);
    virtual auto savePoint(js::number position, js::array<js::number> result);
};

#endif // VIRTUAL_BOX_COLLIDER_H