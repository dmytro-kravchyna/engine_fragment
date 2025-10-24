#ifndef MULTITHREADING_HELPER_H
#define MULTITHREADING_HELPER_H

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
#include "../model/model-types.h"

using namespace js;

// Forward declarations
class MultithreadingHelper;

class MultithreadingHelper {
public:
    MultithreadingHelper() = default;
    auto newThread(js::string url);
    auto newUpdater(js::any effect, js::number rate);
    auto getMeshComputeRequest(js::string modelId, js::array<js::any> list);
    auto planeSet(js::array<unknown> planes);
    auto data(js::any data);
    auto getExecuteRequest(js::string modelId, js::string method, js::any args);
    auto plane(js::any plane);
    js::array<js::any> getRequestContent(js::any input);
    auto array(js::any vector);
    auto cleanRequests(js::array<js::any> list);
    auto frustum(js::any frustum);
    auto beam(js::any ray);
    auto transform(js::any matrix);
    auto deleteUpdater(js::any updater);
    auto areCoresAvailable(js::number currentThreads);
    auto isFinishRequest(js::any request);
private:
    auto setupUpdateRequest(js::any request, js::array<js::any> content);
    auto getCpuCapacity();
    auto addAllTileData(js::any request, js::array<js::any> content);
    auto addRequestContent(js::string id, js::any request, js::array<js::any> content);
    auto addRequestTileData(js::any request, js::array<js::any> content, js::string name, js::array<js::string> extras = js::array<js::any>{});
    auto setupCreateRequest(js::any request, js::array<js::any> content);
    auto getCreateRequestIds();
};

#endif // MULTITHREADING_HELPER_H