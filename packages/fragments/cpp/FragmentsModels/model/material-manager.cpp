#include "index_generated.h"
#include "material-manager.h"

using namespace js;

auto MaterialManager::resetColors(js::array<MaterialDefinition> definitions) {
    {
            for (const auto& definition : definitions) {
                        {
                                        if (!(definition && definition["color"])) {
                                                            continue;
                                        }
                                        auto _temp3255 = definition;
                                        const auto color = _temp3255["color"];
                                        if (color["isColor"]) {
                                                            continue;
                                        }
                                        auto _temp9705 = color;
                                        const auto r = _temp9705["r"];
                                        const auto g = _temp9705["g"];
                                        const auto b = _temp9705["b"];
                                        definition["color"] = std::make_shared<three::Color>(r, g, b);
                        }
            }
    }
}

auto MaterialManager::dispose(js::string modelId) {
    {
            this->_definitions.delete(modelId);
            const js::any ids = this->_modelMaterialMapping.get(modelId);
            if (!ids) {
                        return;
            }
            for (const auto& id : ids) {
                        {
                                        const js::any material = this->list.get(id);
                                        if (!material) {
                                                            continue;
                                        }
                                        material["dispose"]();
                                        this->list.delete(id);
                        }
            }
            this->_modelMaterialMapping.delete(modelId);
    }
}

auto MaterialManager::get(MaterialDefinition data, js::any request) {
    {
            auto _temp7058 = request;
            const auto modelId = _temp7058["modelId"];
            const auto objectClass = _temp7058["objectClass"];
            const auto currentLod = _temp7058["currentLod"];
            const auto templateId = _temp7058["templateId"];
            if (!((modelId && objectClass !== js::undefined) && currentLod !== js::undefined)) {
                        {
                                        throw js::any(js::Error("Fragments: material definition information is missing to create the material."_S));
                        }
            }
            this->_idGenerator.fromMaterialData([]() {
                  js::object obj_temp_0;
                  obj_temp_0.set("modelId", modelId);
                  obj_temp_0.set("objectClass", objectClass);
                  obj_temp_0.set("currentLod", currentLod);
                  obj_temp_0.set("templateId", templateId);
                  return js::any(obj_temp_0);
                }());
            auto _temp2039 = this->_idGenerator;
            const auto id = _temp2039["value"];
            const js::any material = this->getUniqueMaterial(id, data, request);
            return material;
    }
}

auto MaterialManager::addDefinitions(js::string modelID, js::array<MaterialDefinition> materials) {
    {
            const js::any definitions = this->_definitions.get(modelID);
            if (definitions) {
                        {
                                        definitions.push(/* spread materials */);
                        }
            } else {
                        {
                                        this->_definitions.set(modelID, materials);
                        }
            }
    }
}

auto MaterialManager::createHighlights(BIMMesh mesh, js::any request) {
    {
            auto _temp2237 = request;
            auto _temp2237_tileData = _temp2237["tileData"];
            const auto highlightData = _temp2237_tileData["highlightData"];
            const auto highlightIds = _temp2237_tileData["highlightIds"];
            const auto modelId = _temp2237["modelId"];
            const auto index = _temp2237["material"];
            auto _temp9319 = mesh;
            const auto geometry = _temp9319["geometry"];
            const js::any materials = mesh["material"].slice(js::number(0), js::number(2));
            const std::shared_ptr<Map> localMap = std::make_shared<Map>();
            const js::any materialDefinitions = this->_definitions.get(modelId);
            if (!materialDefinitions) {
                        return materials;
            }
            for (js::number i = js::number(0); (i < highlightData->position.length()); i++) {
                        {
                                        const js::any highlightIndex = highlightIds->i;
                                        this->processHighlight(localMap, highlightIndex, materialDefinitions, index, request, materials);
                                        const js::any first = highlightData->position->i;
                                        const js::any value = highlightData->size->i;
                                        const js::any isWhite = value === this->white;
                                        const js::any size = (js::null ? js::null : js::null);
                                        geometry["addGroup"](first, size, localMap->get(highlightIds->i));
                        }
            }
            return materials;
    }
}

auto MaterialManager::getFromRequest(js::any request) {
    {
            auto _temp7184 = request;
            const auto index = _temp7184["material"];
            const auto modelId = _temp7184["modelId"];
            const js::any modelMaterials = this->_definitions.get(modelId);
            const js::any definition = modelMaterials->index;
            if (!definition) {
                        {
                                        throw js::any(js::Error(("Fragments: Missing mesh material for index "_S + js::toString(index))));
                        }
            }
            const js::any material = this->get(definition, request);
            return material;
    }
}

auto MaterialManager::newLODMaterial(MaterialData data, js::any request) {
    {
            auto _temp570 = data;
            const auto definition = _temp570["data"];
            const std::shared_ptr<three::Color> color = std::make_shared<three::Color>(definition["color"]);
            if (request["currentLod"] === CurrentLod::WIRES) {
                        {
                                        color["multiplyScalar"](js::number(0.85));
                        }
            }
            const LineMaterialParameters parameters = []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("color", color);
                  return js::any(obj_temp_1);
                }();
            const std::shared_ptr<LodMaterial> material = std::make_shared<LodMaterial>(parameters);
            material["userData"] = []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("customId", definition["customId"]);
                  return js::any(obj_temp_2);
                }();
            return material;
    }
}

auto MaterialManager::getParameters(MaterialDefinition data) {
    {
            auto _temp282 = data;
            const auto opacity = _temp282["opacity"];
            const auto transparent = _temp282["transparent"];
            const bool isTranslucent = (opacity < js::number(1));
            const js::any parameters = []() {
                  js::object obj_temp_3;
                  obj_temp_3.set("opacity", opacity);
                  obj_temp_3.set("transparent", (transparent || isTranslucent));
                  obj_temp_3.set("clipIntersection", false);
                  return js::any(obj_temp_3);
                }();
            return parameters;
    }
}

auto MaterialManager::new(MaterialDefinition data, js::any request) {
    {
            auto _temp9776 = request;
            const auto objectClass = _temp9776["objectClass"];
            const auto templateId = _temp9776["templateId"];
            BIMMaterial material;
            if (objectClass === ObjectClass::SHELL) {
                        {
                                        material = std::make_shared<three::MeshLambertMaterial>([]() {
                                              js::object obj_temp_4;
                                              obj_temp_4.set("color", data->color);
                                              obj_temp_4.set("transparent", (data->opacity < js::number(1)));
                                              obj_temp_4.set("opacity", data->opacity);
                                              obj_temp_4.set("userData", []() {
                                              js::object obj_temp_5;
                                              obj_temp_5.set("customId", data->customId);
                                              return js::any(obj_temp_5);
                                            }());
                                              obj_temp_4.set("depthTest", (data->depthTest.has_value() ? data->depthTest : true));
                                              return js::any(obj_temp_4);
                                            }());
                        }
            } else {
                        if (objectClass === ObjectClass::LINE) {
                                        {
                                                            material = this->newLODMaterial([]() {
                                                                  js::object obj_temp_6;
                                                                  obj_temp_6.set("data", data);
                                                                  obj_temp_6.set("instancing", templateId !== js::undefined);
                                                                  return js::any(obj_temp_6);
                                                                }(), request);
                                        }
                        } else {
                                        {
                                                            throw js::any(js::Error("Fragments: Unsupported object class"_S));
                                        }
                        }
            }
            return material;
    }
}

auto MaterialManager::addMaterialToModel(js::string modelId, js::number id) {
    {
            js::any modelMaterials = this->_modelMaterialMapping.get(modelId);
            if (!modelMaterials) {
                        {
                                        modelMaterials = std::make_shared<Set>();
                                        this->_modelMaterialMapping.set(modelId, modelMaterials);
                        }
            }
            modelMaterials->add(id);
    }
}

auto MaterialManager::processHighlight(Map localMap, js::any highlightIndex, js::array<MaterialDefinition> materialDefinitions, js::any index, js::any request, js::array<unknown> materials) {
    {
            if (!localMap->has(highlightIndex)) {
                        {
                                        const js::any originalDefinition = materialDefinitions->index;
                                        const js::any newDefinition = materialDefinitions->highlightIndex;
                                        const MaterialDefinition combinedDefinition = []() {
                                              js::object obj_temp_7;
                                              return js::any(obj_temp_7);
                                            }();
                                        const js::any material = this->get(combinedDefinition, request);
                                        materials.push(material);
                                        localMap->set(highlightIndex, (materials.length() - js::number(1)));
                        }
            }
    }
}

auto MaterialManager::getUniqueMaterial(js::number id, MaterialDefinition data, js::any request) {
    {
            const js::any modelId = request["modelId"];
            js::any material = this->list.get(id);
            if (material) {
                        return material;
            }
            material = this->new(data, request);
            this->list.set(id, material);
            this->addMaterialToModel(modelId, id);
            return material;
    }
}
