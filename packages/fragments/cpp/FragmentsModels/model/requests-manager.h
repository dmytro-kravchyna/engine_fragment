#ifndef REQUESTS_MANAGER_H
#define REQUESTS_MANAGER_H

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
#include "./model-types.h"
#include "./material-manager.h"
#include "./mesh-manager.h"

using namespace js;

// Forward declarations
class RequestsManager;

class RequestsManager {
public:
    RequestsManager() = default;
    js::array<js::any> list;
    auto onFinish;
    virtual auto handleRequest(MeshManager meshes, js::any request);
    virtual auto add(js::array<js::any> requests);
    virtual auto clean(js::string modelID);
    virtual auto insert(js::any request);
};

#endif // REQUESTS_MANAGER_H