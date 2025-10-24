#ifndef SHELL_POINT_RAYCASTER_H
#define SHELL_POINT_RAYCASTER_H

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
#include "./shell-utils.h"
#include "../../../../../Schema.h"

using namespace js;

// Forward declarations
class ShellPointRaycaster;

class ShellPointRaycaster {
public:
    ShellPointRaycaster(Meshes _meshes);
    virtual auto pointRaycast(js::number id, js::any frustum);
private:
    std::shared_ptr<Meshes> _meshes;
    auto _tempVec;
    virtual auto cast(Shell shell, js::any frustum, js::array<js::any> points);
};

#endif // SHELL_POINT_RAYCASTER_H