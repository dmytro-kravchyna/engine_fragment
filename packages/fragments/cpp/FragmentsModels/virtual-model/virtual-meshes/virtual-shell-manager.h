#ifndef VIRTUAL_SHELL_MANAGER_H
#define VIRTUAL_SHELL_MANAGER_H

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
#include "./virtual-mesh-manager.h"
#include "./types.h"
#include "../../model/model-types.h"
#include "../../../../Schema.h"
#include "./shell/shell-template-constructor.h"
#include "./shell.h"
#include "./shell/shell-utils.h"
#include "./shell/shell-point-raycaster.h"

using namespace js;

// Forward declarations
class VirtualShellManager;

class VirtualShellManager : public VirtualMeshManager {
public:
    VirtualShellManager() = default;
    auto fetchMeshes(js::number meshId, bool evenVoid) override;
    auto newMeshTemplate(Shell shell) override;
    auto lineRaycast(js::number id, js::any ray, js::any frustum) override;
    auto faceRaycast(js::number id, js::any ray) override;
    auto raycast(js::number id, js::any ray) override;
    auto pointRaycast(js::number id, js::any _ray, js::any frustum) override;
    auto setupTemplates() override;
    auto getRepresentation() override;
    auto getObjectClass() override;
    auto getLodClass() override;
private:
    auto _lodClass;
    auto _objectClass;
    auto _representationClass;
    auto _templates;
    auto _constructor;
    auto _faceRaycaster;
    auto _lineRaycaster;
    auto _pointRaycaster;
    auto isVoidMesh(AnyTileData mesh) override;
    auto constructMesh(AnyTileData mesh, bool evenVoid, js::number meshId) override;
};

#endif // VIRTUAL_SHELL_MANAGER_H