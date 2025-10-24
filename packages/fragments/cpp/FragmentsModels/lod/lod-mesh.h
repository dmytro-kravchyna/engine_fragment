#ifndef LOD_MESH_H
#define LOD_MESH_H

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
#include "./lod-material.h"
#include "./lod-geometry.h"
#include "./lod-helper.h"

using namespace js;

// Forward declarations
class LODMesh;

class LODMesh : public three::Mesh {
public:
    std::shared_ptr<LODGeometry> geometry;
    js::array<LodMaterial> material;
    LODMesh(LODGeometry geometry, js::array<LodMaterial> material);
};

#endif // LOD_MESH_H