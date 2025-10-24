#include "index_generated.h"
#include "virtual-mesh-manager.h"

using namespace js;

VirtualMeshManager::VirtualMeshManager(js::string modelId, Meshes meshes) {
    {
            this->meshes = meshes;
            this->_modelCode = this->getModelCode(modelId);
    }
}

auto VirtualMeshManager::dispose() {
    {
            VirtualMemoryController::delete(this->_meshIds);
    }
}

auto VirtualMeshManager::useMesh(js::number id, AnyTileBasicData mesh, CurrentLod lod) {
    {
            const js::any code = this->meshCode(id, lod);
            VirtualMemoryController::lockIn(mesh);
            this->_templateController.add(code, mesh);
    }
}

auto VirtualMeshManager::getMesh(js::number id, CurrentLod lod) {
    {
            const js::any code = this->meshCode(id, lod);
            const js::any geometry = VirtualMemoryController::get(code);
            return (geometry.has_value() ? geometry : this->_templateController.get(code));
    }
}

auto VirtualMeshManager::saveMesh(js::number id, AnyTileData mesh, CurrentLod lod) {
    {
            MiscHelper::forEach(mesh, VirtualMemoryController::updateMeshMemory);
            const js::any code = this->meshCode(id, lod);
            VirtualMemoryController::add(code, mesh);
            this->_meshIds.add(code);
    }
}

js::number VirtualMeshManager::meshCode(js::number index, CurrentLod lod) {
    {
            const js::any code = this->_modelCode;
            const js::any repr = this->getRepresentation();
            js::array<js::any> data = js::array<js::any>{code, repr, lod, index};
            return this->_idGenerator.generate(data);
    }
}

auto VirtualMeshManager::getModelCode(js::string modelId) {
    {
            return this->_idGenerator.generate(js::array<js::any>{modelId});
    }
}
