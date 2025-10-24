#include "index_generated.h"
#include "lod-manager.h"

using namespace js;

LODManager::LODManager(MaterialManager materials) {
    {
            this->_materials = materials;
    }
}

auto LODManager::createMesh(js::any geometry, js::any request) {
    {
            const js::any material = this->_materials.getFromRequest(request);
            if (!(js::in_op("isLodMaterial"_S, material) && material["isLodMaterial"])) {
                        {
                                        throw js::any(js::Error("Fragments: material is not an instance of LodMaterial."_S));
                        }
            }
            auto _temp8659 = request;
            const auto positions = _temp8659["positions"];
            if (!positions) {
                        {
                                        throw js::any(js::Error("Fragments: no positions provided to create the LOD mesh."_S));
                        }
            }
            const std::shared_ptr<LODGeometry> lodGeometry = std::make_shared<LODGeometry>();
            const js::any deleteEvent = this->deleteAttributeEvent(geometry);
            LodHelper::setLodBuffer(lodGeometry, positions, deleteEvent);
            const std::shared_ptr<LODMesh> mesh = std::make_shared<LODMesh>(lodGeometry, js::array<js::any>{material});
            return mesh;
    }
}

auto LODManager::updateVisibility(LODMesh mesh, js::any status) {
    {
            auto _temp1392 = mesh;
            const auto geometry = _temp1392["geometry"];
            auto _temp4074 = status;
            const auto visibilityData = _temp4074["visibilityData"];
            const auto highlightData = _temp4074["highlightData"];
            LodHelper::setLodVisibility(geometry, visibilityData);
            if (highlightData) {
                        {
                                        LodHelper::setLodFilter(geometry, highlightData);
                                        MultiBufferData::getComplementary(highlightData, [&](auto start, auto count) -> auto {
                                        geometry["addGroup"](start, count, js::number(0));
                                        });
                        }
            } else {
                        {
                                        geometry["addGroup"](js::number(0), js::number::POSITIVE_INFINITY, js::number(0));
                        }
            }
    }
}

auto LODManager::processMesh(BIMMesh mesh, js::any request) {
    {
            auto _temp4996 = mesh;
            const auto geometry = _temp4996["geometry"];
            auto _temp2791 = request;
            auto _temp2791_tileData = _temp2791["tileData"];
            const auto visibilityData = _temp2791_tileData["visibilityData"];
            const auto currentLod = _temp2791["currentLod"];
            if ((currentLod === CurrentLod::WIRES && js::instanceof_op(mesh, "LODMesh"))) {
                        {
                                        this->updateVisibility(mesh, request["tileData"]);
                        }
            } else {
                        if ((visibilityData && (visibilityData->position.length() > js::number(0)))) {
                                        {
                                                            for (js::number i = js::number(0); (i < visibilityData->position.length()); ++i) {
                                                                                    {
                                                                                                                const js::any isWhite = visibilityData->size->i === this->white;
                                                                                                                const js::any position = visibilityData->position->i;
                                                                                                                const js::any value = (js::null ? js::null : js::null);
                                                                                                                geometry["addGroup"](position, value, js::number(0));
                                                                                    }
                                                            }
                                        }
                        }
            }
    }
}

auto LODManager::deleteAttributeEvent(js::any _geometry) {
    {
            js::null;
            return callback;
    }
}
