#ifndef SHELL_LINE_RAYCASTER_H
#define SHELL_LINE_RAYCASTER_H

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
#include "../../../../../Schema.h"
#include "./shell-utils.h"

using namespace js;

// Forward declarations
class ShellLineRaycaster;

class ShellLineRaycaster {
public:
    ShellLineRaycaster(Meshes meshes);
    virtual auto lineRaycast(js::number id, js::any ray, js::any frustum);
private:
    std::shared_ptr<Meshes> _meshes;
    auto _minAngle;
    auto _shellProfile;
    auto _bigShellProfile;
    auto _tempV1;
    auto _tempV2;
    auto _tempPoint;
    js::array<unknown> _normals;
    auto _pointsByProfile;
    auto _shell;
    js::array<js::any> _result;
    virtual auto lineRaycastItems(js::any ray, js::any frustum);
    virtual auto resetData(js::number id);
    virtual auto lineRaycastProfile(js::any ray, js::any frustum, js::number id);
    virtual auto isInvalidAngle(js::number firstIndex, js::number secondIndex, js::number id);
    virtual auto getProfile(js::number firstIndex, js::number secondIndex, js::number id);
    virtual auto cast(js::number i1, js::number i2, js::any ray, js::any frustum, js::number id);
    virtual auto saveResult(js::number id);
    virtual auto getSecondIndex(js::number id, js::number count);
    virtual auto raycastSegment(js::any ray);
    virtual auto getTempProfile(Shell shell);
};

#endif // SHELL_LINE_RAYCASTER_H