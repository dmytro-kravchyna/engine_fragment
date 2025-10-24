#include "index_generated.h"
#include "virtual-circle-extrusion-manager.h"

using namespace js;

auto VirtualCircleExtrusionManager::setupTemplates() {
    {
            const js::any count = this->meshes.circleExtrusionsLength();
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        this->newCircleExtrusionTemplate(id);
                        }
            }
    }
}

auto VirtualCircleExtrusionManager::fetchLod(js::number meshId, bool evenVoid) {
    {
            const js::any lod = this->getMesh(meshId, CurrentLod::WIRES);
            this->generateLodIfNeeded(meshId, evenVoid, lod);
            return lod;
    }
}

auto VirtualCircleExtrusionManager::fetchMeshes(js::number meshId, bool evenVoid) {
    {
            const js::any meshes = this->getMesh(meshId, CurrentLod::GEOMETRY);
            this->generateMeshesIfNeeded(meshId, evenVoid, meshes);
            return meshes;
    }
}

auto VirtualCircleExtrusionManager::raycast(js::number id, js::any ray) {
    {
            return this->_vceRaycaster.raycast(id, ray);
    }
}

auto VirtualCircleExtrusionManager::faceRaycast() {
    {
            return js::array<js::any>{};
    }
}

auto VirtualCircleExtrusionManager::pointRaycast(js::number id, js::any ray) {
    {
            return this->_vcePointRaycaster.pointRaycast(id, ray);
    }
}

auto VirtualCircleExtrusionManager::lineRaycast(js::number id, js::any ray) {
    {
            return this->_vceLineRaycaster.lineRaycast(id, ray);
    }
}

auto VirtualCircleExtrusionManager::getObjectClass() {
    {
            return this->_objectClass;
    }
}

auto VirtualCircleExtrusionManager::getRepresentation() {
    {
            return this->_representationClass;
    }
}

auto VirtualCircleExtrusionManager::getLodClass() {
    {
            return this->lodClass;
    }
}

auto VirtualCircleExtrusionManager::newMeshes(js::number meshId, js::array<TileData> meshes) {
    {
            this->meshes.circleExtrusions(meshId, VceUtils::temp::circleExtrusion);
            const js::any circleExtrusion = VceUtils::temp::circleExtrusion;
            this->_vceConstructor.construct(circleExtrusion, meshes);
            this->saveMesh(meshId, meshes, CurrentLod::GEOMETRY);
    }
}

auto VirtualCircleExtrusionManager::generateMeshesIfNeeded(js::number meshId, bool createIfVoid, js::array<TileData> meshes) {
    {
            if (meshes.length() === js::number(0)) {
                        {
                                        return;
                        }
            }
            const js::any meshesExist = Boolean(meshes.length());
            const js::any isVoid = !meshes[js::number(0)].positionBuffer;
            const js::any shouldCreate = ((createIfVoid && isVoid) && meshesExist);
            if (shouldCreate) {
                        {
                                        this->newMeshes(meshId, meshes);
                        }
            }
    }
}

auto VirtualCircleExtrusionManager::newCircleExtrusionTemplate(js::number id) {
    {
            js::array<js::any> meshTemplate = js::array<js::any>{};
            this->meshes.circleExtrusions(id, VceUtils::temp::circleExtrusion);
            const js::any circleExtrusion = VceUtils::temp::circleExtrusion;
            const js::any count = circleExtrusion->axesLength();
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        this->_vceConstructor.newTemplate(circleExtrusion, i, meshTemplate);
                        }
            }
            const js::any lodTemplate = this->_lodConstructor.newTemplate();
            this->useMesh(id, meshTemplate, CurrentLod::GEOMETRY);
            this->useMesh(id, lodTemplate, CurrentLod::WIRES);
    }
}

auto VirtualCircleExtrusionManager::generateLodIfNeeded(js::number meshId, bool evenVoid, TileData mesh) {
    {
            const js::any isVoid = !mesh["positionBuffer"];
            if ((!isVoid || !evenVoid)) {
                        return;
            }
            this->meshes.circleExtrusions(meshId, VceUtils::temp::circleExtrusion);
            this->_lodConstructor.construct(VceUtils::temp::circleExtrusion, mesh);
            this->saveMesh(meshId, mesh, CurrentLod::WIRES);
    }
}
