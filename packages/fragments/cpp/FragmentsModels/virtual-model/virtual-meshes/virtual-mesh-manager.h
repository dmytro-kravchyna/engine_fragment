#ifndef VIRTUAL_MESH_MANAGER_H
#define VIRTUAL_MESH_MANAGER_H

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
#include "../../model/model-types.h"
#include "../../utils.h"
#include "../../../../Schema.h"
#include "./types.h"
#include "../virtual-controllers.h"

using namespace js;

// Forward declarations
class VirtualMeshManager;

class VirtualMeshManager {
public:
    VirtualMeshManager(js::string modelId, Meshes meshes);
    virtual void setupTemplates() = 0;
    virtual AnyTileData fetchMeshes(js::number meshId, bool evenVoid) = 0;
    virtual js::array<js::any> lineRaycast(js::number id, js::any ray, js::any frustum) = 0;
    virtual js::array<js::any> pointRaycast(js::number id, js::any ray, js::any frustum) = 0;
    virtual js::array<js::any> raycast(js::number id, js::any ray, js::any frustum) = 0;
    virtual js::array<js::any> faceRaycast(js::number id, js::any ray, js::any frustum) = 0;
    virtual RepresentationClass getRepresentation() = 0;
    virtual ObjectClass getObjectClass() = 0;
    virtual LodClass getLodClass() = 0;
    virtual auto dispose();
protected:
    std::shared_ptr<Meshes> meshes;
    virtual auto useMesh(js::number id, AnyTileBasicData mesh, CurrentLod lod);
    virtual auto getMesh(js::number id, CurrentLod lod);
    virtual auto saveMesh(js::number id, AnyTileData mesh, CurrentLod lod);
private:
    auto _templateController;
    auto _meshIds;
    auto _idGenerator;
    js::number _modelCode;
    virtual js::number meshCode(js::number index, CurrentLod lod);
    virtual auto getModelCode(js::string modelId);
};

#endif // VIRTUAL_MESH_MANAGER_H