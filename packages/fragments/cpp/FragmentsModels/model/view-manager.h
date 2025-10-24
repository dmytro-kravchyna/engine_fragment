#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "runtime/async.h"
#include <three.h>
#include "./model-types.h"
#include "./fragments-model.h"
#include "./mesh-manager.h"
#include "../utils.h"

using namespace js;

// Forward declarations
class ViewManager;

class ViewManager {
public:
    ViewManager() = default;
    std::shared_ptr<std::function<js::array<unknown>()>> getClippingPlanesEvent;
    virtual auto refreshView(FragmentsModel model, MeshManager meshes);
    virtual auto useCamera(js::any camera);
private:
    auto _tempMatrix;
    auto _tempVec;
    auto _tempFrustum;
    std::shared_ptr<std::function<void(unknown)>> _updateCameraPositionEvent;
    std::shared_ptr<std::function<void(unknown)>> _updateCameraFrustumEvent;
    std::shared_ptr<std::function<js::any()>> _updateFOVEvent;
    std::shared_ptr<std::function<js::any()>> _updateOrthoSizeEvent;
    virtual auto getOrthoSize();
    virtual auto setup(MeshManager meshes, FragmentsModel model);
    virtual auto newViewRequest(js::any frustum, js::any fov, FragmentsModel model);
    virtual auto newView(js::any frustum, js::any fov, FragmentsModel model);
    virtual auto setOrtho();
    virtual auto setFov(js::any camera);
    virtual auto getPlanes();
    virtual auto setCameraPosition(js::any camera);
    virtual auto setCameraFrustum(js::any camera, js::any projScreenMatrix);
};

#endif // VIEW_MANAGER_H