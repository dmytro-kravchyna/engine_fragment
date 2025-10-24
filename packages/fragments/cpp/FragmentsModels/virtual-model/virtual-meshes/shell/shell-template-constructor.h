#ifndef SHELL_TEMPLATE_CONSTRUCTOR_H
#define SHELL_TEMPLATE_CONSTRUCTOR_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../types.h"
#include "../../../model/model-types.h"
#include "../../../utils/geometry/earcut.h"
#include "../../../../../Schema.h"
#include "./shell-utils.h"

using namespace js;

// Forward declarations
class ShellTemplateConstructor;

class ShellTemplateConstructor {
public:
    ShellTemplateConstructor() = default;
    auto holePoints;
    auto profilePoints;
    auto triangleAmount;
    auto indexCount;
    std::shared_ptr<AnyTileBasicData> meshes;
    virtual auto newMeshTemplate(Shell shell);
private:
    auto _shellHole;
    auto _bigShellHole;
    auto _shellProfile;
    auto _bigShellProfile;
    virtual auto manageDataLeft();
    virtual auto getIsEmpty(Shell shell);
    virtual auto processShellHoles(Shell shell, js::number id);
    virtual auto newMesh();
    virtual auto reset(bool evenMeshes);
    virtual auto getIsDataLeft();
    virtual auto processShell(Shell shell);
    virtual auto manageFoundHoles(Shell shell, bool shellHolesExist);
    virtual auto getResult();
    virtual auto manageMemory();
    virtual auto updateBuffers(Shell shell, bool shellHolesExist);
    virtual auto setMesh();
    virtual auto getTempProfile(Shell shell);
    virtual auto getTempHole(Shell shell);
};

#endif // SHELL_TEMPLATE_CONSTRUCTOR_H