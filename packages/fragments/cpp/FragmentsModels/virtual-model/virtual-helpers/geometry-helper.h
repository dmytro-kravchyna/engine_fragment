#ifndef GEOMETRY_HELPER_H
#define GEOMETRY_HELPER_H

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
#include "../virtual-fragments-model.h"

using namespace js;

// Forward declarations
class GeometryHelper;

// Interface Vector3
class IVector3 {
public:
    virtual ~IVector3() = default;
    // TODO: Interface members
};
class GeometryHelper {
public:
    GeometryHelper() = default;
    virtual auto getGeometriesLength(VirtualFragmentsModel model);
    virtual js::array<MeshData> getGeometry(VirtualFragmentsModel model, js::number itemIndex);
    virtual auto getVolume(VirtualFragmentsModel model, js::number id);
private:
    virtual auto getSignedVolumeOfTriangle(Vector3 p1, Vector3 p2, Vector3 p3);
};

#endif // GEOMETRY_HELPER_H