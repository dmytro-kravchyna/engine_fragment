#include "index_generated.h"
#include "lod-mesh.h"

using namespace js;

LODMesh::LODMesh(LODGeometry geometry, js::array<LodMaterial> material) : three::Mesh(geometry, material) {
    {
            this->geometry = geometry;
            this->material = material;
            LodHelper::setupLodMeshResize(this);
    }
}
