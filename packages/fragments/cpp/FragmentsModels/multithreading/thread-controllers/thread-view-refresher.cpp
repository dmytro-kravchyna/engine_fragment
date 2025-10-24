#include "index_generated.h"
#include "thread-view-refresher.h"

using namespace js;

auto ThreadViewRefresher::getId() {
    {
            return MultiThreadingRequestClass::REFRESH_VIEW;
    }
}

auto ThreadViewRefresher::execute(js::any input) {
    {
            const js::any model = this->thread.list.get(input["modelId"]);
            if (model) {
                        {
                                        this->safeCopyFrustum(input);
                                        this->safeCopyPosition(input);
                                        this->safeCopyPlanes(input);
                                        model["refreshView"](input["view"]);
                        }
            }
    }
}

auto ThreadViewRefresher::safeCopyFrustum(js::any input) {
    {
            const js::any frustum = input["view"]["cameraFrustum"];
            input["view"]["cameraFrustum"] = MultithreadingHelper::frustum(frustum);
    }
}

auto ThreadViewRefresher::safeCopyPosition(js::any input) {
    {
            const js::any position = input["view"]["cameraPosition"];
            input["view"]["cameraPosition"] = MultithreadingHelper::array(position);
    }
}

auto ThreadViewRefresher::safeCopyPlanes(js::any input) {
    {
            const js::any planes = input["view"]["clippingPlanes"];
            input["view"]["clippingPlanes"] = MultithreadingHelper::planeSet(planes);
    }
}
