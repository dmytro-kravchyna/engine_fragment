#include "index_generated.h"
#include "thread-raycaster.h"

using namespace js;

// Enum RaycastType implementation
const js::number RaycastType::BEAM = js::number(0);
const js::number RaycastType::RECTANGLE = js::number(1);
const js::number RaycastType::WITH_SNAP = js::number(2);

js::string RaycastType::getName(js::number key) {
    if (key.value() == js::number(0).value()) return "BEAM"_S;
    if (key.value() == js::number(1).value()) return "RECTANGLE"_S;
    if (key.value() == js::number(2).value()) return "WITH_SNAP"_S;
    return "undefined"_S;
}


auto ThreadRaycaster::getId() {
    {
            return MultiThreadingRequestClass::RAYCAST;
    }
}

auto ThreadRaycaster::execute(js::any input) {
    {
            const js::any raycastType = this->getRaycastType(input);
            if (raycastType === RaycastType::BEAM) {
                        {
                                        this->raycastBeam(input);
                                        return;
                        }
            }
            if (raycastType === RaycastType::WITH_SNAP) {
                        {
                                        this->raycastWithSnap(input);
                                        return;
                        }
            }
            if (raycastType === RaycastType::RECTANGLE) {
                        {
                                        this->raycastRectangle(input);
                                        return;
                        }
            }
            throw js::any(js::Error("Fragments: Invalid raycast type"_S));
    }
}

auto ThreadRaycaster::getRaycastType(js::any input) {
    {
            if (input["snappingClass"]) {
                        {
                                        return RaycastType::WITH_SNAP;
                        }
            }
            if (input["ray"]) {
                        {
                                        return RaycastType::BEAM;
                        }
            }
            return RaycastType::RECTANGLE;
    }
}

auto ThreadRaycaster::raycastRectangle(js::any input) {
    {
            const js::any model = this->thread.getModel(input["modelId"]);
            const js::any frustum = MultithreadingHelper::frustum(input["frustum"]);
            const js::any fullyIncluded = input["fullyIncluded"];
            const js::any localIds = model["rectangleRaycast"](frustum, fullyIncluded);
            input["localIds"] = localIds;
    }
}

auto ThreadRaycaster::raycastWithSnap(js::any input) {
    {
            const js::any model = this->thread.getModel(input["modelId"]);
            const js::any beam = MultithreadingHelper::beam(input["ray"]);
            const js::any frustum = MultithreadingHelper::frustum(input["frustum"]);
            const js::any snappingClass = input["snappingClass"];
            const js::any results = model["snapRaycast"](beam, frustum, snappingClass);
            input["results"] = results;
    }
}

auto ThreadRaycaster::raycastBeam(js::any input) {
    {
            const js::any model = this->thread.getModel(input["modelId"]);
            const js::any beam = MultithreadingHelper::beam(input["ray"]);
            const js::any frustum = MultithreadingHelper::frustum(input["frustum"]);
            const js::any hit = model["raycast"](beam, frustum);
            if (hit) {
                        {
                                        input["results"] = js::array<js::any>{hit};
                        }
            }
    }
}
