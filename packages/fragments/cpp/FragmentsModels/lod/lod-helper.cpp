#include "index_generated.h"
#include "lod-helper.h"

using namespace js;

auto LodHelper::setupLodMeshResize(LODMesh mesh) {
    {
            mesh["onBeforeRender"] = [&](auto renderer) -> auto {
            renderer["getSize"](mesh["material"][js::number(0)].lodSize);
            };
    }
}

void LodHelper::setupLodAttributes(js::any geometry) {
    {
            geometry["setIndex"](LodHelper::indices);
            geometry["setAttribute"]("position"_S, LodHelper::vertices);
    }
}

auto LodHelper::setLodBuffer(LODGeometry lodGeometry, js::Float32Array data, std::optional<std::function<void()>> onFinish) {
    {
            js::any itemFirst = lodGeometry->getItemFirst();
            js::any itemLast = lodGeometry->getItemLast();
            js::any dataBuffer = this->setItemFirst(lodGeometry, itemFirst, data, itemLast);
            const js::any result = this->resetAttributes(itemFirst, dataBuffer, data, itemLast);
            []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("itemFirst", itemFirst);
                  obj_temp_0.set("dataBuffer", dataBuffer);
                  obj_temp_0.set("itemLast", itemLast);
                  return js::any(obj_temp_0);
                }() = result;
            this->setupFinish(onFinish, dataBuffer);
            lodGeometry->setAttribute("itemFirst"_S, itemFirst);
            lodGeometry->setAttribute("itemLast"_S, itemLast);
    }
}

void LodHelper::setLodVisibility(LODGeometry lodGeometry, js::any visible) {
    {
            const js::any itemFilter = this->setupItemFilter(lodGeometry);
            this->applyVisibilityState(lodGeometry, visible, itemFilter);
            itemFilter->needsUpdate = true;
    }
}

auto LodHelper::getInterAttribute(js::any geometry, js::string name) {
    {
            return geometry["getAttribute"](name);
    }
}

auto LodHelper::computeLodSphere(LODGeometry geometry) {
    {
            if (!geometry["boundingSphere"]) {
                        {
                                        return;
                        }
            }
            const js::any itemFirst = geometry["getItemFirst"]();
            if (itemFirst) {
                        {
                                        const js::any midPoint = LodHelper::getLodMidPoint(geometry, itemFirst);
                                        const js::any radius = LodHelper::getLodRadius(midPoint, itemFirst);
                                        geometry["boundingSphere"]["radius"] = radius;
                        }
            }
    }
}

auto LodHelper::newLodMaterialParams(LineMaterialParameters parameters) {
    {
            const js::any customUniforms = []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("lodColor", []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("value", std::make_shared<three::Color>(parameters["color"]));
                  return js::any(obj_temp_2);
                }());
                  obj_temp_1.set("lodSize", []() {
                  js::object obj_temp_3;
                  obj_temp_3.set("value", std::make_shared<three::Vector2>(js::number(1), js::number(1)));
                  return js::any(obj_temp_3);
                }());
                  obj_temp_1.set("lodOpacity", []() {
                  js::object obj_temp_4;
                  obj_temp_4.set("value", (parameters["opacity"].has_value() ? parameters["opacity"] : js::number(1)));
                  return js::any(obj_temp_4);
                }());
                  return js::any(obj_temp_1);
                }();
            const js::any uniforms = three::UniformsUtils.merge(js::array<js::any>{three::UniformsLib.common, customUniforms});
            const js::any transparent = (parameters["transparent"].has_value() ? parameters["transparent"] : false);
            return []() {
                  js::object obj_temp_5;
                  obj_temp_5.set("uniforms", uniforms);
                  obj_temp_5.set("transparent", transparent);
                  obj_temp_5.set("vertexShader", LodShaders::vertex);
                  obj_temp_5.set("fragmentShader", LodShaders::fragment);
                  return js::any(obj_temp_5);
                }();
    }
}

void LodHelper::setLodFilter(LODGeometry geometry, js::any data) {
    {
            const js::any itemFilter = geometry["getItemFilter"]();
            const js::any bufferData = itemFilter->array;
            for (js::number i = js::number(0); (i < data->position.length()); ++i) {
                        {
                                        const js::number first = (data->position[i] / js::number(2));
                                        const js::number size = (data->size[i] / js::number(2));
                                        if (size === js::number(4294967295)) {
                                                            {
                                                                                    bufferData->fill(js::number(1), first);
                                                            }
                                        } else {
                                                            {
                                                                                    bufferData->fill(js::number(1), first, (first + size));
                                                            }
                                        }
                        }
            }
            itemFilter->needsUpdate = true;
    }
}

auto LodHelper::getInstancedAttribute(js::any geometry, js::string name) {
    {
            return geometry["getAttribute"](name);
    }
}

auto LodHelper::computeLodBox(LODGeometry geometry) {
    {
            if (!geometry["boundingBox"]) {
                        {
                                        return;
                        }
            }
            const js::any position = geometry["getItemFirst"]();
            if (position) {
                        {
                                        const js::any buffer = position["data"]["array"];
                                        geometry["boundingBox"]["setFromArray"](buffer);
                                        return;
                        }
            }
            geometry["boundingBox"]["makeEmpty"]();
    }
}

auto LodHelper::setDataBuffer(js::typed::Nullable<unknown> dataBuffer, js::any itemFirst, js::Float32Array data) {
    {
            dataBuffer = itemFirst->data;
            dataBuffer->array = data;
            dataBuffer->needsUpdate = true;
            return dataBuffer;
    }
}

auto LodHelper::disposeAllData(js::any geometry) {
    {
            js::delete_property(geometry["attributes"], "itemFilter");
            js::delete_property(geometry["attributes"], "position");
            geometry["index"] = js::null;
            geometry["dispose"]();
            LodHelper::setupLodAttributes(geometry);
    }
}

auto LodHelper::setItemFirst(LODGeometry lodGeometry, js::any itemFirst, js::Float32Array data, js::any itemLast) {
    {
            js::typed::Nullable<unknown> dataBuffer = js::null;
            if (itemFirst) {
                        {
                                        const js::any sizeMatch = data.length() === itemFirst->data->array.length();
                                        if (sizeMatch) {
                                                            {
                                                                                    dataBuffer = this->setDataBuffer(dataBuffer, itemFirst, data);
                                                            }
                                        } else {
                                                            {
                                                                                    itemFirst = js::undefined;
                                                                                    itemLast = js::undefined;
                                                                                    this->disposeAllData(lodGeometry);
                                                            }
                                        }
                        }
            }
            return dataBuffer;
    }
}

auto LodHelper::setupFinish(js::typed::Nullable<std::function<void()>> onFinish, js::typed::Nullable<unknown> dataBuffer) {
    {
            if (onFinish) {
                        {
                                        dataBuffer->onUploadCallback = onFinish;
                        }
            }
    }
}

auto LodHelper::resetAttributes(js::any itemFirst, js::typed::Nullable<unknown> dataBuffer, js::Float32Array data, js::any itemLast) {
    {
            if (!itemFirst) {
                        {
                                        dataBuffer = std::make_shared<three::InstancedInterleavedBuffer>(data, js::number(6), js::number(1));
                                        itemFirst = std::make_shared<three::InterleavedBufferAttribute>(dataBuffer, js::number(3), js::number(0));
                                        itemLast = std::make_shared<three::InterleavedBufferAttribute>(dataBuffer, js::number(3), js::number(3));
                        }
            }
            return []() {
                  js::object obj_temp_6;
                  obj_temp_6.set("itemFirst", itemFirst);
                  obj_temp_6.set("dataBuffer", dataBuffer);
                  obj_temp_6.set("itemLast", itemLast);
                  return js::any(obj_temp_6);
                }();
    }
}

auto LodHelper::setupItemFilter(LODGeometry lodGeometry) {
    {
            const js::any itemFirst = lodGeometry->getItemFirst();
            const js::any size = itemFirst->count;
            js::any itemFilter = lodGeometry->getItemFilter();
            if (itemFilter) {
                        {
                                        itemFilter->array->fill(js::number(0));
                        }
            } else {
                        {
                                        itemFilter = std::make_shared<three::InstancedBufferAttribute>(std::make_shared<Uint8Array>(size), js::number(1));
                                        lodGeometry->setAttribute("itemFilter"_S, itemFilter);
                        }
            }
            return itemFilter;
    }
}

auto LodHelper::applyVisibilityState(LODGeometry lodGeometry, js::any visible, js::any itemFilter) {
    {
            if (visible === true) {
                        {
                                        itemFilter->array->fill(js::number(1));
                                        return;
                        }
            }
            if (visible) {
                        {
                                        this->setLodFilter(lodGeometry, visible);
                        }
            }
    }
}

auto LodHelper::getLodMidPoint(LODGeometry geometry, js::any itemFirst) {
    {
            const js::any midpoint = geometry["boundingSphere"]["center"];
            this->tempBox.setFromArray(itemFirst->data->array);
            this->tempBox.getCenter(midpoint);
            return midpoint;
    }
}

auto LodHelper::getLodRadius(js::any midPoint, js::any itemFirst) {
    {
            js::number threshold = js::number(0);
            const js::any size = itemFirst->data->array.length();
            for (js::number i = js::number(0); (i < size); i += js::number(3)) {
                        {
                                        const js::any dataBuffer = itemFirst->data->array;
                                        LodHelper::tempVec::fromArray(dataBuffer, i);
                                        const js::any distance = midPoint->distanceToSquared(LodHelper::tempVec);
                                        threshold = js::Math::max(threshold, distance);
                        }
            }
            return js::Math::sqrt(threshold);
    }
}
