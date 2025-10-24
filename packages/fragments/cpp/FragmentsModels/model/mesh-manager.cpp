#include "index_generated.h"
#include "mesh-manager.h"

using namespace js;

MeshManager::MeshManager(std::function<void()> onUpdate) {
    {
            this->_onUpdate = onUpdate;
            this->requests.onFinish = [&]() -> auto { return this->_updateFinished = true; };
    }
}

auto MeshManager::forceUpdateFinish(auto rate) {
    {
            const std::shared_ptr<Promise> result = std::make_shared<Promise>([&](auto resolve) -> auto {
            this->_updateFinished = false;
            const js::any interval = setInterval([&]() -> auto {
            this->update();
            if (!this->_updateFinished) {
                        return;
            }
            clearInterval(interval);
            resolve();
            }, rate);
            });
            return result;
    }
}

auto MeshManager::update() {
    {
            const js::any start = performance["now"]();
            while (js::null) {
                        {
                        }
            }
    }
}

auto MeshManager::setTileData(BIMMesh mesh, js::any request) {
    {
            auto _temp2240 = request;
            const auto tileId = _temp2240["tileId"];
            const auto itemId = _temp2240["itemId"];
            const auto matrix = _temp2240["matrix"];
            const auto aabb = _temp2240["aabb"];
            this->setMeshData(mesh, tileId, itemId, matrix);
            this->setupBoundings(mesh, aabb);
            this->updateStatus(mesh, request);
    }
}

auto MeshManager::processTileRequest(js::any request) {
    {
            auto _temp592 = request;
            const auto tileRequestClass = _temp592["tileRequestClass"];
            const auto tileId = _temp592["tileId"];
            const auto modelId = _temp592["modelId"];
            const js::any model = this->list.get(modelId);
            if (!model) {
                        return;
            }
            if (tileRequestClass === TileRequestClass::CREATE) {
                        {
                                        if (request["objectClass"] === js::undefined) {
                                                            return;
                                        }
                                        const js::any tile = this->create(request);
                                        this->setTileData(tile, request);
                                        model["tiles"]["set"](tile["userData"]["tileId"], tile);
                        }
            } else {
                        if (tileRequestClass === TileRequestClass::DELETE) {
                                        {
                                                            model["tiles"]["delete"](tileId);
                                        }
                        } else {
                                        if (tileRequestClass === TileRequestClass::UPDATE) {
                                                            {
                                                                                    const js::any tileObject = model["tiles"]["get"](tileId);
                                                                                    if (tileObject) {
                                                                                                                this->updateStatus(tileObject, request);
                                                                                    }
                                                            }
                                        } else {
                                                            if (tileRequestClass === TileRequestClass::FINISH) {
                                                                                    {
                                                                                                                model["_finishProcessing"]();
                                                                                    }
                                                            }
                                        }
                        }
            }
    }
}

auto MeshManager::createMesh(js::any request) {
    {
            auto _temp4153 = request;
            const auto indices = _temp4153["indices"];
            const auto positions = _temp4153["positions"];
            const auto normals = _temp4153["normals"];
            const auto itemIds = _temp4153["itemIds"];
            const auto faceIds = _temp4153["faceIds"];
            const std::shared_ptr<three::BufferGeometry> geometry = std::make_shared<three::BufferGeometry>();
            this->setIndex(geometry, indices);
            this->setPositions(positions, geometry);
            this->setNormals(normals, geometry);
            this->setItemIds(itemIds, geometry);
            this->setFaceIds(faceIds, geometry);
            const js::any material = this->materials.getFromRequest(request);
            return std::make_shared<three::Mesh>(geometry, js::array<js::any>{material});
    }
}

auto MeshManager::setupBoundings(BIMMesh mesh, js::any aabb) {
    {
            auto _temp2393 = mesh;
            const auto geometry = _temp2393["geometry"];
            const js::any box = std::make_shared<three::Box3>().copy(aabb);
            const std::shared_ptr<three::Sphere> sphere = std::make_shared<three::Sphere>();
            box["getBoundingSphere"](sphere);
            geometry["boundingBox"] = box;
            geometry["boundingSphere"] = sphere;
    }
}

BIMMesh MeshManager::create(js::any request) {
    {
            if (request["objectClass"] === ObjectClass::SHELL) {
                        return this->createMesh(request);
            }
            if (request["objectClass"] === ObjectClass::LINE) {
                        {
                                        const std::shared_ptr<three::BufferGeometry> geometry = std::make_shared<three::BufferGeometry>();
                                        return this->lod.createMesh(geometry, request);
                        }
            }
            throw js::any(js::Error(("Fragments: object class "_S + js::toString(request["objectClass"]) + " is not supported."_S)));
    }
}

auto MeshManager::updateStatus(BIMMesh mesh, js::any request) {
    {
            auto _temp7633 = request;
            auto _temp7633_tileData = _temp7633["tileData"];
            const auto highlightData = _temp7633_tileData["highlightData"];
            const auto currentLod = _temp7633["currentLod"];
            auto _temp4705 = mesh;
            const auto geometry = _temp4705["geometry"];
            geometry["clearGroups"]();
            this->lod.processMesh(mesh, request);
            if (!(highlightData && currentLod !== CurrentLod::WIRES)) {
                        return;
            }
            const js::any materials = this->materials.createHighlights(mesh, request);
            mesh["material"] = materials;
    }
}

auto MeshManager::cleanAttributeMemory(js::any geometry, js::string name) {
    {
            const js::any attr = geometry["attributes"][name];
            attr["onUpload"](this->deleteAttribute(geometry));
    }
}

auto MeshManager::setPositions(js::any positions, js::any geometry) {
    {
            if (!positions) {
                        {
                                        throw js::any(js::Error("Fragments: no positions provided to create the mesh."_S));
                        }
            }
            geometry["setAttribute"]("position"_S, std::make_shared<three::BufferAttribute>(positions, js::number(3)));
            this->cleanAttributeMemory(geometry, "position"_S);
    }
}

auto MeshManager::setFaceIds(js::any faceIds, js::any geometry) {
    {
            if (faceIds) {
                        {
                                        geometry["setAttribute"]("color"_S, std::make_shared<three::BufferAttribute>(faceIds, js::number(3)));
                                        this->cleanAttributeMemory(geometry, "color"_S);
                        }
            }
    }
}

auto MeshManager::setIndex(js::any geometry, js::any indices) {
    {
            if (!indices) {
                        {
                                        throw js::any(js::Error("Fragments: no indices provided to create the mesh."_S));
                        }
            }
            geometry["setIndex"](std::make_shared<three::BufferAttribute>(indices, js::number(1)));
            geometry["index"]["onUpload"](this->deleteAttribute(geometry));
    }
}

auto MeshManager::setNormals(js::any normals, js::any geometry) {
    {
            if (normals) {
                        {
                                        geometry["setAttribute"]("normal"_S, std::make_shared<three::BufferAttribute>(normals, js::number(3), true));
                        }
            }
            this->cleanAttributeMemory(geometry, "normal"_S);
    }
}

auto MeshManager::setItemIds(js::any itemIds, js::any geometry) {
    {
            if (itemIds) {
                        {
                                        geometry["setAttribute"]("id"_S, std::make_shared<three::BufferAttribute>(itemIds, js::number(1), false));
                                        this->cleanAttributeMemory(geometry, "id"_S);
                        }
            }
    }
}

auto MeshManager::deleteAttribute(js::any _geometry) {
    {
            js::null;
            return callback;
    }
}

auto MeshManager::setMeshData(BIMMesh mesh, js::any tileId, js::any itemId, js::any matrix) {
    {
            mesh["userData"] = []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("tileId", tileId);
                  obj_temp_0.set("itemId", itemId);
                  return js::any(obj_temp_0);
                }();
            mesh["matrixAutoUpdate"] = false;
            mesh["applyMatrix4"](matrix);
            mesh["matrix"]["copy"](matrix);
    }
}
