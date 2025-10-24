#include "index_generated.h"
#include "section-helper.h"

using namespace js;

auto SectionHelper::getSection(VirtualFragmentsModel model, js::any plane, js::array<js::number> indices) {
    {
            this->_sectionGenerator.plane = plane;
            const js::any start = performance["now"]();
            const std::shared_ptr<Map> visitedGeometries = std::make_shared<Map>();
            js::array<unknown> meshes = js::array<js::any>{};
            for (const auto& itemID : indices) {
                        {
                                        const js::any sampleIds = model["boxes"]["sampleOf"](itemID);
                                        if (!sampleIds) {
                                                            continue;
                                        }
                                        for (const auto& sampleId : sampleIds) {
                                                            {
                                                                                    const js::any boundingBox = model["boxes"]["get"](sampleId);
                                                                                    if (!plane["intersectsBox"](boundingBox)) {
                                                                                                                {
                                                                                                                                                continue;
                                                                                                                }
                                                                                    }
                                                                                    const js::any localIDIndex = model["tiles"]["meshes"]["meshesItems"](itemID);
                                                                                    const js::any category = model["data"]["categories"](localIDIndex);
                                                                                    if (category === "IFCSPACE"_S) {
                                                                                                                {
                                                                                                                                                continue;
                                                                                                                }
                                                                                    }
                                                                                    const js::any sample = model["tiles"]["meshes"]["samples"](sampleId);
                                                                                    if (!sample) {
                                                                                                                continue;
                                                                                    }
                                                                                    const js::any definitionID = sample["representation"]();
                                                                                    if (!visitedGeometries->has(definitionID)) {
                                                                                                                {
                                                                                                                                                js::array<unknown> geometries = js::array<js::any>{};
                                                                                                                                                const js::any sampleGeom = model["tiles"]["fetchSample"](sampleId, CurrentLod::GEOMETRY);
                                                                                                                                                MiscHelper::forEach(sampleGeom->geometries, [&](auto geometryData) -> auto {
                                                                                                                                                if ((!geometryData->indexBuffer || !geometryData->positionBuffer)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            return;
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                const std::shared_ptr<three::BufferGeometry> geometry = std::make_shared<three::BufferGeometry>();
                                                                                                                                                geometry["setIndex"](js::array.from(geometryData->indexBuffer));
                                                                                                                                                geometry["setAttribute"]("position"_S, std::make_shared<three::BufferAttribute>(geometryData->positionBuffer, js::number(3)));
                                                                                                                                                geometries.push(geometry);
                                                                                                                                                });
                                                                                                                                                visitedGeometries->set(definitionID, geometries);
                                                                                                                }
                                                                                    }
                                                                                    const js::any geometries = visitedGeometries->get(definitionID);
                                                                                    if (!geometries) {
                                                                                                                continue;
                                                                                    }
                                                                                    for (const auto& geometry : geometries) {
                                                                                                                {
                                                                                                                                                const std::shared_ptr<three::Mesh> mesh = std::make_shared<three::Mesh>(geometry);
                                                                                                                                                const js::any transform = model["tiles"]["getSampleTransform"](sampleId);
                                                                                                                                                mesh["applyMatrix4"](transform);
                                                                                                                                                mesh["updateWorldMatrix"](true, true);
                                                                                                                                                meshes.push(mesh);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            const std::shared_ptr<Float32Array> buffer = std::make_shared<Float32Array>(js::number(600000));
            const std::shared_ptr<three::BufferAttribute> posAttr = std::make_shared<three::BufferAttribute>(buffer, js::number(3), false);
            auto _temp3901 = this->_sectionGenerator.createEdges([]() {
                  js::object obj_temp_0;
                  obj_temp_0.set("meshes", meshes);
                  obj_temp_0.set("posAttr", posAttr);
                  return js::any(obj_temp_0);
                }());
            const auto index = _temp3901["index"];
            const auto indexes = _temp3901["indexes"];
            const js::any fillsIndices = this->_sectionGenerator.createFills(buffer, indexes);
            for (const auto& js::undefined : visitedGeometries) {
                        {
                                        for (const auto& geometry : geometries) {
                                                            {
                                                                                    geometry["dispose"]();
                                                            }
                                        }
                        }
            }
            const ModelSection result = []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("buffer", buffer);
                  obj_temp_1.set("index", index);
                  obj_temp_1.set("fillsIndices", fillsIndices);
                  return js::any(obj_temp_1);
                }();
            return result;
    }
}
