#include "index_generated.h"
#include "requests-manager.h"

using namespace js;

auto RequestsManager::handleRequest(MeshManager meshes, js::any request) {
    {
            if (request["class"] === MultiThreadingRequestClass::RECOMPUTE_MESHES) {
                        {
                                        this->add(request["list"]);
                                        request["list"] = js::undefined;
                        }
            } else {
                        if (request["class"] === MultiThreadingRequestClass::CREATE_MATERIAL) {
                                        {
                                                            auto _temp3530 = request;
                                                            const auto materialDefinitions = _temp3530["materialDefinitions"];
                                                            const auto modelId = _temp3530["modelId"];
                                                            MaterialManager::resetColors(materialDefinitions);
                                                            meshes["materials"]["addDefinitions"](modelId, materialDefinitions);
                                                            request["materialDefinitions"] = js::undefined;
                                        }
                        } else {
                                        if (request["class"] === MultiThreadingRequestClass::THROW_ERROR) {
                                                            {
                                                                                    js::console.error(request);
                                                            }
                                        }
                        }
            }
    }
}

auto RequestsManager::add(js::array<js::any> requests) {
    {
            for (const auto& request : requests) {
                        {
                                        if (!this->insert(request)) {
                                                            this->list.push(request);
                                        }
                                        if (request["tileRequestClass"] === TileRequestClass::FINISH) {
                                                            {
                                                                                    this->onFinish();
                                                            }
                                        }
                        }
            }
    }
}

auto RequestsManager::clean(js::string modelID) {
    {
            const js::any list = this->list.filter([&](auto request) -> auto { return (request["modelId"] !== modelID || request["tileRequestClass"] !== TileRequestClass::FINISH); });
            this->list = list;
    }
}

auto RequestsManager::insert(js::any request) {
    {
            auto _temp4821 = request;
            const auto modelId = _temp4821["modelId"];
            const auto tileId = _temp4821["tileId"];
            const auto tileRequestClass = _temp4821["tileRequestClass"];
            const auto tileData = _temp4821["tileData"];
            if (tileId === js::undefined) {
                        return false;
            }
            if (tileRequestClass === TileRequestClass::DELETE) {
                        {
                                        const js::any list = this->list.filter([&](auto request) -> auto { return !(((request["tileRequestClass"] === TileRequestClass::CREATE || request["tileRequestClass"] === TileRequestClass::DELETE) && request["modelId"] === modelId) && request["tileId"] === tileId); });
                                        this->list = list;
                        }
            }
            if (tileRequestClass === TileRequestClass::CREATE) {
                        {
                                        const js::any list = this->list.filter([&](auto request) -> auto { return !((request["tileRequestClass"] === TileRequestClass::CREATE && request["modelId"] === modelId) && request["tileId"] === tileId); });
                                        this->list = list;
                        }
            }
            if (tileRequestClass === TileRequestClass::UPDATE) {
                        {
                                        const js::any overriddenRequest = this->list.find([&](auto request) -> auto { return (request["modelId"] === modelId && request["tileId"] === tileId); });
                                        if (overriddenRequest) {
                                                            {
                                                                                    if ((overriddenRequest->tileRequestClass === TileRequestClass::CREATE || overriddenRequest->tileRequestClass === TileRequestClass::UPDATE)) {
                                                                                                                overriddenRequest->tileData = tileData;
                                                                                    }
                                                                                    return true;
                                                            }
                                        }
                        }
            }
            return false;
    }
}
