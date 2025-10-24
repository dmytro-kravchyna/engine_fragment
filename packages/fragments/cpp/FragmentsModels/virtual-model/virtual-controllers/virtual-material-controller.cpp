#include "index_generated.h"
#include "virtual-material-controller.h"

using namespace js;

VirtualMaterialController::VirtualMaterialController(js::string modelId, VirtualMaterialTransfer onTransfer) {
    {
            this->_modelId = modelId;
            this->_onTransfer = onTransfer;
    }
}

js::array<js::number> VirtualMaterialController::update(Model model) {
    {
            const js::any meshes = model["meshes"]();
            js::array<js::any> matList = js::array<js::any>{};
            return this->getAll(meshes, matList);
    }
}

auto VirtualMaterialController::fetch(js::number materialId) {
    {
            return this->_list[materialId];
    }
}

js::array<js::number> VirtualMaterialController::transfer(js::array<MaterialDefinition> materials) {
    {
            const js::any result = this->deduplicateMaterials(materials);
            auto _temp1479 = result;
            const auto materialDefinitions = _temp1479["materialDefinitions"];
            const auto ids = _temp1479["ids"];
            this->transferMaterialData(materialDefinitions);
            return ids;
    }
}

auto VirtualMaterialController::getItemsMaterialDefinition(Model model, js::array<js::number> indices, js::array<js::number> localIds) {
    {
            js::array<js::any> result = js::array<js::any>{};
            const js::any meshes = model["meshes"]();
            if (!meshes) {
                        return js::array<js::any>{};
            }
            const std::shared_ptr<Map> map = std::make_shared<Map>();
            for (const auto& js::undefined : indices["entries"]()) {
                        {
                                        const js::any sample = meshes["samples"](itemIndex);
                                        if (!sample) {
                                                            continue;
                                        }
                                        const js::any materialIndex = sample["material"]();
                                        js::any materialItems = map["get"](materialIndex);
                                        if (!materialItems) {
                                                            {
                                                                                    materialItems = std::make_shared<Set>();
                                                                                    map["set"](materialIndex, materialItems);
                                                            }
                                        }
                                        materialItems->add(localIds->index);
                        }
            }
            for (const auto& js::undefined : map["entries"]()) {
                        {
                                        const js::any material = meshes["materials"](materialIndex);
                                        if (!material) {
                                                            continue;
                                        }
                                        const js::any definition = ParserHelper::parseMaterial(material);
                                        result.push([]() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("localIds", js::array<js::any>().concat(localIds));
                                              obj_temp_0.set("definition", definition);
                                              return js::any(obj_temp_0);
                                            }());
                        }
            }
            return result;
    }
}

auto VirtualMaterialController::checkMaterialExists(MaterialDefinition material, js::array<js::number> ids) {
    {
            const js::any count = this->_list.length();
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        const js::any current = this->_list[i];
                                        const js::any isSame = MaterialUtils::isSame(material, current);
                                        if (isSame) {
                                                            {
                                                                                    ids.push(i);
                                                                                    return true;
                                                            }
                                        }
                        }
            }
            return false;
    }
}

auto VirtualMaterialController::deduplicateMaterials(js::array<MaterialDefinition> materialDefinition) {
    {
            js::array<js::any> ids = js::array<js::any>{};
            js::array<js::any> materialDefinitions = js::array<js::any>{};
            for (const auto& material : materialDefinition) {
                        {
                                        const js::any exists = this->checkMaterialExists(material, ids);
                                        if (!exists) {
                                                            {
                                                                                    this->_list.push(material);
                                                                                    materialDefinitions.push(material);
                                                                                    const js::number currentId = (this->_list.length() - js::number(1));
                                                                                    ids.push(currentId);
                                                            }
                                        }
                        }
            }
            return []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("materialDefinitions", materialDefinitions);
                  obj_temp_1.set("ids", ids);
                  return js::any(obj_temp_1);
                }();
    }
}

auto VirtualMaterialController::getAll(Meshes meshes, js::array<MaterialDefinition> materialDefinitions) {
    {
            const js::any count = meshes["materialsLength"]();
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        const js::any matData = meshes["materials"](i);
                                        const js::any definition = ParserHelper::parseMaterial(matData);
                                        materialDefinitions.push(definition);
                        }
            }
            return this->transfer(materialDefinitions);
    }
}

auto VirtualMaterialController::transferMaterialData(js::array<MaterialDefinition> materialDefinitions) {
    {
            this->_onTransfer([]() {
                  js::object obj_temp_2;
                  obj_temp_2.set("class", MultiThreadingRequestClass::CREATE_MATERIAL);
                  obj_temp_2.set("modelId", this->_modelId);
                  obj_temp_2.set("materialDefinitions", materialDefinitions);
                  return js::any(obj_temp_2);
                }());
    }
}
