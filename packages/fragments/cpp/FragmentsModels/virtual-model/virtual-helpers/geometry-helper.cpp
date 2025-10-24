#include "index_generated.h"
#include "geometry-helper.h"

using namespace js;

auto GeometryHelper::getGeometriesLength(VirtualFragmentsModel model) {
    {
            return model["data"]["meshes"]()["globalTransformsLength"]();
    }
}

js::array<MeshData> GeometryHelper::getGeometry(VirtualFragmentsModel model, js::number itemIndex) {
    {
            const js::any sampleIds = model["boxes"]["sampleOf"](itemIndex);
            js::array<MeshData> result = js::array<js::any>{};
            if (!sampleIds) {
                        return result;
            }
            for (const auto& sampleId : sampleIds) {
                        {
                                        const js::any sample = model["tiles"]["fetchSample"](sampleId, CurrentLod::GEOMETRY);
                                        const js::any geometries = (js::null ? js::null : js::null);
                                        for (const auto& geometry : geometries) {
                                                            {
                                                                                    result.push([]() {
                                                                                          js::object obj_temp_0;
                                                                                          obj_temp_0.set("transform", sample["transform"]["clone"]());
                                                                                          obj_temp_0.set("indices", geometry["indexBuffer"]);
                                                                                          obj_temp_0.set("positions", geometry["positionBuffer"]);
                                                                                          obj_temp_0.set("normals", geometry["normalBuffer"]);
                                                                                          return js::any(obj_temp_0);
                                                                                        }());
                                                            }
                                        }
                        }
            }
            return result;
    }
}

auto GeometryHelper::getVolume(VirtualFragmentsModel model, js::number id) {
    {
            js::number volume = js::number(0);
            const Vector3 p1 = []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("x", js::number(0));
                  obj_temp_1.set("y", js::number(0));
                  obj_temp_1.set("z", js::number(0));
                  return js::any(obj_temp_1);
                }();
            const Vector3 p2 = []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("x", js::number(0));
                  obj_temp_2.set("y", js::number(0));
                  obj_temp_2.set("z", js::number(0));
                  return js::any(obj_temp_2);
                }();
            const Vector3 p3 = []() {
                  js::object obj_temp_3;
                  obj_temp_3.set("x", js::number(0));
                  obj_temp_3.set("y", js::number(0));
                  obj_temp_3.set("z", js::number(0));
                  return js::any(obj_temp_3);
                }();
            const js::any geometries = this->getGeometry(model, id);
            for (const auto& js::undefined : geometries) {
                        {
                                        if (!(indices && positions)) {
                                                            continue;
                                        }
                                        for (js::number i = js::number(0); (i < (indices.length() - js::number(2))); i += js::number(3)) {
                                                            {
                                                                                    const js::number i1 = (indices[i] * js::number(3));
                                                                                    const js::number i2 = (indices[(i + js::number(1))] * js::number(3));
                                                                                    const js::number i3 = (indices[(i + js::number(2))] * js::number(3));
                                                                                    p1["x"] = positions[i1];
                                                                                    p1["y"] = positions[(i1 + js::number(1))];
                                                                                    p1["z"] = positions[(i1 + js::number(2))];
                                                                                    p2["x"] = positions[i2];
                                                                                    p2["y"] = positions[(i2 + js::number(1))];
                                                                                    p2["z"] = positions[(i2 + js::number(2))];
                                                                                    p3["x"] = positions[i3];
                                                                                    p3["y"] = positions[(i3 + js::number(1))];
                                                                                    p3["z"] = positions[(i3 + js::number(2))];
                                                                                    volume += this->getSignedVolumeOfTriangle(p1, p2, p3);
                                                            }
                                        }
                        }
            }
            return js::Math::abs(volume);
    }
}

auto GeometryHelper::getSignedVolumeOfTriangle(Vector3 p1, Vector3 p2, Vector3 p3) {
    {
            const js::number v321 = ((p3["x"] * p2["y"]) * p1["z"]);
            const js::number v231 = ((p2["x"] * p3["y"]) * p1["z"]);
            const js::number v312 = ((p3["x"] * p1["y"]) * p2["z"]);
            const js::number v132 = ((p1["x"] * p3["y"]) * p2["z"]);
            const js::number v213 = ((p2["x"] * p1["y"]) * p3["z"]);
            const js::number v123 = ((p1["x"] * p2["y"]) * p3["z"]);
            return ((js::number(1) / js::number(6)) * (((((-v321 + v231) + v312) - v132) - v213) + v123));
    }
}
