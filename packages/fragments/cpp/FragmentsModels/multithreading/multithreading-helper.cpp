#include "index_generated.h"
#include "multithreading-helper.h"

using namespace js;

auto MultithreadingHelper::newThread(js::string url) {
    {
            return std::make_shared<Worker>(url, []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("type", "module"_S);
                  return js::any(obj_temp_0);
                }());
    }
}

auto MultithreadingHelper::newUpdater(js::any effect, js::number rate) {
    {
            return setInterval(effect, rate);
    }
}

auto MultithreadingHelper::getMeshComputeRequest(js::string modelId, js::array<js::any> list) {
    {
            const js::any className = MultiThreadingRequestClass::RECOMPUTE_MESHES;
            return []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("class", className);
                  obj_temp_1.set("modelId", modelId);
                  obj_temp_1.set("list", list);
                  return js::any(obj_temp_1);
                }();
    }
}

auto MultithreadingHelper::planeSet(js::array<unknown> planes) {
    {
            js::array<unknown> planeSet = js::array<js::any>{};
            for (const auto& plane : planes) {
                        {
                                        const js::any newNormal = this->array(plane["normal"]);
                                        const js::any newConstant = plane["constant"];
                                        const std::shared_ptr<three::Plane> newPlane = std::make_shared<three::Plane>(newNormal, newConstant);
                                        planeSet.push(newPlane);
                        }
            }
            return planeSet;
    }
}

auto MultithreadingHelper::data(js::any data) {
    {
            const js::any isTransform = data->elements !== js::undefined;
            if (isTransform) {
                        {
                                        return MultithreadingHelper::transform(data);
                        }
            }
            const js::any isBeam = (data->origin !== js::undefined && data->direction !== js::undefined);
            if (isBeam) {
                        {
                                        return MultithreadingHelper::beam(data);
                        }
            }
            const js::any isFrustum = data->planes !== js::undefined;
            if (isFrustum) {
                        {
                                        return MultithreadingHelper::frustum(data);
                        }
            }
            const js::any hasNormal = data->normal !== js::undefined;
            const js::any hasConstant = data->constant !== js::undefined;
            const js::any isPlane = (hasNormal && hasConstant);
            if (isPlane) {
                        {
                                        return MultithreadingHelper::plane(data);
                        }
            }
            const js::any hasNormalSet = data->js::number(0).normal !== js::undefined;
            const js::any hasConstantSet = data->js::number(0).constant !== js::undefined;
            const js::any isPlaneSet = (hasNormalSet && hasConstantSet);
            if (isPlaneSet) {
                        {
                                        return MultithreadingHelper::planeSet(data);
                        }
            }
            const js::any hasX = data->x !== js::undefined;
            const js::any hasY = data->y !== js::undefined;
            const js::any hasZ = data->z !== js::undefined;
            const js::any isArray = ((hasX && hasY) && hasZ);
            if (isArray) {
                        {
                                        return MultithreadingHelper::array(data);
                        }
            }
            return data;
    }
}

auto MultithreadingHelper::getExecuteRequest(js::string modelId, js::string method, js::any args) {
    {
            const js::any parameters = js::array.from(args);
            const js::any className = MultiThreadingRequestClass::EXECUTE;
            return []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("class", className);
                  obj_temp_2.set("modelId", modelId);
                  obj_temp_2.set("function", method);
                  obj_temp_2.set("parameters", parameters);
                  return js::any(obj_temp_2);
                }();
    }
}

auto MultithreadingHelper::plane(js::any plane) {
    {
            const js::any newNormal = this->array(plane["normal"]);
            const js::any newConstant = plane["constant"];
            const std::shared_ptr<three::Plane> newPlane = std::make_shared<three::Plane>(newNormal, newConstant);
            return newPlane;
    }
}

js::array<js::any> MultithreadingHelper::getRequestContent(js::any input) {
    {
            js::array<js::any> content = js::array<js::any>{};
            for (const auto& request : input["list"]) {
                        {
                                        MultithreadingHelper::setupCreateRequest(request, content);
                                        MultithreadingHelper::setupUpdateRequest(request, content);
                        }
            }
            return content;
    }
}

auto MultithreadingHelper::array(js::any vector) {
    {
            const std::shared_ptr<three::Vector3> array = std::make_shared<three::Vector3>();
            array["set"](vector["x"], vector["y"], vector["z"]);
            return array;
    }
}

auto MultithreadingHelper::cleanRequests(js::array<js::any> list) {
    {
            js::array<js::any> tasks = js::array<js::any>{};
            const js::any helper = MultithreadingHelper;
            for (const auto& request : list) {
                        {
                                        const js::any isFinish = helper["isFinishRequest"](request);
                                        if (!isFinish) {
                                                            {
                                                                                    tasks.push(request);
                                                            }
                                        }
                        }
            }
            return tasks;
    }
}

auto MultithreadingHelper::frustum(js::any frustum) {
    {
            const js::any newPlane = this->planeSet(frustum["planes"]);
            auto _temp3943 = newPlane;
            const auto a = _temp3943[0];
            const auto b = _temp3943[1];
            const auto c = _temp3943[2];
            const auto d = _temp3943[3];
            const auto e = _temp3943[4];
            const auto f = _temp3943[5];
            return std::make_shared<three::Frustum>(a, b, c, d, e, f);
    }
}

auto MultithreadingHelper::beam(js::any ray) {
    {
            const js::any newOrigin = this->array(ray["origin"]);
            const js::any newDirection = this->array(ray["direction"]);
            return std::make_shared<three::Ray>(newOrigin, newDirection);
    }
}

auto MultithreadingHelper::transform(js::any matrix) {
    {
            const std::shared_ptr<three::Matrix4> newMatrix = std::make_shared<three::Matrix4>();
            newMatrix->copy(matrix);
            return newMatrix;
    }
}

auto MultithreadingHelper::deleteUpdater(js::any updater) {
    {
            clearInterval(updater);
    }
}

auto MultithreadingHelper::areCoresAvailable(js::number currentThreads) {
    {
            const js::any capacity = MultithreadingHelper::getCpuCapacity();
            const js::any availableThreads = js::Math::max(capacity, js::number(2));
            return (currentThreads < availableThreads);
    }
}

auto MultithreadingHelper::isFinishRequest(js::any request) {
    {
            return request["tileRequestClass"] === TileRequestClass::FINISH;
    }
}

auto MultithreadingHelper::setupUpdateRequest(js::any request, js::array<js::any> content) {
    {
            if (request["tileRequestClass"] === TileRequestClass::UPDATE) {
                        {
                                        this->addAllTileData(request, content);
                        }
            }
    }
}

auto MultithreadingHelper::getCpuCapacity() {
    {
            const js::number freeCores = js::number(3);
            if (globalThis->navigator->hardwareConcurrency) {
                        {
                                        return (navigator["hardwareConcurrency"] - freeCores);
                        }
            }
            return js::number(0);
    }
}

auto MultithreadingHelper::addAllTileData(js::any request, js::array<js::any> content) {
    {
            this->addRequestTileData(request, content, "visibilityData"_S);
            js::array<js::string> extras = js::array<js::string>{"highlightIds"_S};
            this->addRequestTileData(request, content, "highlightData"_S, extras);
    }
}

auto MultithreadingHelper::addRequestContent(js::string id, js::any request, js::array<js::any> content) {
    {
            if (!request[id]) {
                        return;
            }
            const js::any buffer = request[id]["buffer"];
            content.push(buffer);
    }
}

auto MultithreadingHelper::addRequestTileData(js::any request, js::array<js::any> content, js::string name, js::array<js::string> extras) {
    {
            const js::any data = request["tileData"][name];
            if (data) {
                        {
                                        content.push(data->position.buffer);
                                        content.push(data->size.buffer);
                                        for (const auto& extra : extras) {
                                                            {
                                                                                    content.push(request["tileData"][extra]["buffer"]);
                                                            }
                                        }
                        }
            }
    }
}

auto MultithreadingHelper::setupCreateRequest(js::any request, js::array<js::any> content) {
    {
            if (request["tileRequestClass"] !== TileRequestClass::CREATE) {
                        {
                                        return;
                        }
            }
            const js::any ids = this->getCreateRequestIds();
            for (const auto& id : ids) {
                        {
                                        this->addRequestContent(id, request, content);
                        }
            }
            this->addAllTileData(request, content);
    }
}

auto MultithreadingHelper::getCreateRequestIds() {
    {
            return js::array<js::string>{"positions"_S, "indices"_S, "normals"_S, "itemIds"_S};
    }
}
