#include "index_generated.h"
#include "virtual-shell-manager.h"

using namespace js;

auto VirtualShellManager::fetchMeshes(js::number meshId, bool evenVoid) {
    {
            const js::any mesh = this->getMesh(meshId, CurrentLod::GEOMETRY);
            this->constructMesh(mesh, evenVoid, meshId);
            return mesh;
    }
}

auto VirtualShellManager::newMeshTemplate(Shell shell) {
    {
            return this->_templates.newMeshTemplate(shell);
    }
}

auto VirtualShellManager::lineRaycast(js::number id, js::any ray, js::any frustum) {
    {
            return this->_lineRaycaster.lineRaycast(id, ray, frustum);
    }
}

auto VirtualShellManager::faceRaycast(js::number id, js::any ray) {
    {
            return this->_faceRaycaster.faceRaycast(id, ray);
    }
}

auto VirtualShellManager::raycast(js::number id, js::any ray) {
    {
            return this->_faceRaycaster.faceRaycast(id, ray);
    }
}

auto VirtualShellManager::pointRaycast(js::number id, js::any _ray, js::any frustum) {
    {
            return this->_pointRaycaster.pointRaycast(id, frustum);
    }
}

auto VirtualShellManager::setupTemplates() {
    {
            for (js::number i = js::number(0);
            js::any l = this->meshes.shellsLength(); (i < l); i++) {
                        {
                                        const js::any poly = ShellUtils::getShell(this->meshes, i);
                                        this->useMesh(i, this->newMeshTemplate(poly), CurrentLod::GEOMETRY);
                        }
            }
    }
}

auto VirtualShellManager::getRepresentation() {
    {
            return this->_representationClass;
    }
}

auto VirtualShellManager::getObjectClass() {
    {
            return this->_objectClass;
    }
}

auto VirtualShellManager::getLodClass() {
    {
            return this->_lodClass;
    }
}

auto VirtualShellManager::isVoidMesh(AnyTileData mesh) {
    {
            if (!js::array.isArray(mesh)) {
                        {
                                        return mesh["positionBuffer"] === js::undefined;
                        }
            }
            return mesh[js::number(0)].positionBuffer === js::undefined;
    }
}

auto VirtualShellManager::constructMesh(AnyTileData mesh, bool evenVoid, js::number meshId) {
    {
            const js::any isVoid = this->isVoidMesh(mesh);
            if ((!isVoid || !evenVoid)) {
                        return;
            }
            const js::any shell = ShellUtils::getShell(this->meshes, meshId);
            this->_constructor.construct(shell, mesh);
            this->saveMesh(meshId, mesh, CurrentLod::GEOMETRY);
    }
}
