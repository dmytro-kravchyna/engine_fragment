#include "index_generated.h"
#include "geometry-processor.h"

using namespace js;

auto getRawShellData(js::Uint32Array index, js::Float32Array position, js::any bbox) {
    const std::shared_ptr<Map> pointsMap = std::make_shared<Map>();
    const std::shared_ptr<Map> profiles = std::make_shared<Map>();
    const js::any getPointIndex = [](js::number x, js::number y, js::number z) -> auto {
    const js::any key = (js::toString(x) + ","_S + js::toString(y) + ","_S + js::toString(z));
    if (pointsMap->has(key)) {
            {
                        return pointsMap->get(key)->js::number(0);
            }
    }
    const js::any index = pointsMap->size;
    pointsMap->set(key, js::array<js::any>{index, x, y, z});
    return index;
    };
    for (js::number i = js::number(0); (i < (index.length() - js::number(2))); i += js::number(3)) {
            {
                        const js::any v1Index = index[i];
                        const js::any v2Index = index[(i + js::number(1))];
                        const js::any v3Index = index[(i + js::number(2))];
                        const js::any p1x = position[(v1Index * js::number(3))];
                        const js::any p1y = position[((v1Index * js::number(3)) + js::number(1))];
                        const js::any p1z = position[((v1Index * js::number(3)) + js::number(2))];
                        const js::any p2x = position[(v2Index * js::number(3))];
                        const js::any p2y = position[((v2Index * js::number(3)) + js::number(1))];
                        const js::any p2z = position[((v2Index * js::number(3)) + js::number(2))];
                        const js::any p3x = position[(v3Index * js::number(3))];
                        const js::any p3y = position[((v3Index * js::number(3)) + js::number(1))];
                        const js::any p3z = position[((v3Index * js::number(3)) + js::number(2))];
                        const js::any i1 = getPointIndex(p1x, p1y, p1z);
                        const js::any i2 = getPointIndex(p2x, p2y, p2z);
                        const js::any i3 = getPointIndex(p3x, p3y, p3z);
                        profiles["set"](profiles["size"], js::array<js::any>{i1, i2, i3});
            }
    }
    js::array<js::array<js::number>> points = js::array<js::any>{};
    for (const auto& js::undefined : pointsMap) {
            {
                        points.push(js::array<js::any>{x, y, z});
            }
    }
    const ShellData result = []() {
          js::object obj_temp_0;
          obj_temp_0.set("bbox", bbox);
          obj_temp_0.set("type", ../../../../../Schema::RepresentationClass.SHELL);
          obj_temp_0.set("profiles", profiles);
          obj_temp_0.set("holes", std::make_shared<Map>());
          obj_temp_0.set("points", points);
          return js::any(obj_temp_0);
        }();
    return result;
}

ShellData getShellData(js::any geometry) {
    auto _temp5761 = geometry;
    const auto position = _temp5761["position"];
    const auto normals = _temp5761["normals"];
    const auto index = _temp5761["index"];
    const auto raw = _temp5761["raw"];
    const js::number threshold = js::number(3000);
    const js::number precision = js::number(1000000);
    const js::number normalPrecision = js::number(10000000);
    const js::number planePrecision = js::number(1000);
    const js::number vertexCount = (position.length() / js::number(3));
    const bool tooBigToShell = (vertexCount > threshold);
    const js::any bbox = getAABB(position);
    if ((raw || tooBigToShell)) {
            {
                        return getRawShellData(index, position, bbox);
            }
    }
    const std::shared_ptr<three::Plane> tempPlane = std::make_shared<three::Plane>();
    const std::shared_ptr<three::Vector3> tempNormal = std::make_shared<three::Vector3>();
    const std::shared_ptr<three::Vector3> tempPoint = std::make_shared<three::Vector3>();
    const std::shared_ptr<Map> coplanarTriangles = std::make_shared<Map>();
    for (js::number i = js::number(0); (i < (index.length() - js::number(2))); i += js::number(3)) {
            {
                        const js::any v1Index = index[i];
                        tempNormal->set(normals[(v1Index * js::number(3))], normals[((v1Index * js::number(3)) + js::number(1))], normals[((v1Index * js::number(3)) + js::number(2))]);
                        tempPoint->set(position[(v1Index * js::number(3))], position[((v1Index * js::number(3)) + js::number(1))], position[((v1Index * js::number(3)) + js::number(2))]);
                        tempPlane->setFromNormalAndCoplanarPoint(tempNormal, tempPoint);
                        const std::shared_ptr<Plane> plane = std::make_shared<Plane>(tempPlane, planePrecision, normalPrecision);
                        if (!coplanarTriangles->has(plane["id"])) {
                                        {
                                                            coplanarTriangles->set(plane["id"], plane);
                                        }
                        }
                        coplanarTriangles->get(plane["id"])->faces.push(i);
            }
    }
    const std::shared_ptr<Points> points = std::make_shared<Points>(precision);
    const std::shared_ptr<Faces> faces = std::make_shared<Faces>();
    for (const auto& js::undefined : coplanarTriangles) {
            {
                        for (const auto& triangleIndex : plane["faces"]) {
                                        {
                                                            const js::any v1Index = index[triangleIndex];
                                                            const js::any v2Index = index[(triangleIndex + js::number(1))];
                                                            const js::any v3Index = index[(triangleIndex + js::number(2))];
                                                            if (!points["isValidTriangle"](position, v1Index, v2Index, v3Index)) {
                                                                                    {
                                                                                                                continue;
                                                                                    }
                                                            }
                                                            const js::any p1 = points["create"](position, v1Index);
                                                            const js::any p2 = points["create"](position, v2Index);
                                                            const js::any p3 = points["create"](position, v3Index);
                                                            const std::shared_ptr<Edge> e1 = std::make_shared<Edge>(p1, p2);
                                                            const std::shared_ptr<Edge> e2 = std::make_shared<Edge>(p2, p3);
                                                            const std::shared_ptr<Edge> e3 = std::make_shared<Edge>(p3, p1);
                                                            js::array<js::any> triangle = js::array<js::any>{e1, e2, e3};
                                                            faces["add"](triangle, plane);
                                        }
                        }
            }
    }
    const std::shared_ptr<Map> profiles = std::make_shared<Map>();
    const std::shared_ptr<Map> holes = std::make_shared<Map>();
    js::number faceCounter = js::number(0);
    for (const auto& js::undefined : faces["list"]) {
            {
                        const std::shared_ptr<Profiles> profile = std::make_shared<Profiles>(face["plane"]);
                        const js::any openEdges = face["getOpenEdges"]();
                        if (openEdges.length() === js::number(0)) {
                                        {
                                                            js::console.log("No open edges found. Using raw geometry."_S);
                                                            return getRawShellData(index, position, bbox);
                                        }
                        }
                        for (const auto& edge : openEdges) {
                                        {
                                                            profile["add"](edge);
                                        }
                        }
                        const js::any resultProfiles = profile["getProfiles"]();
                        profiles["set"](faceCounter, (resultProfiles->profile || js::array<js::any>{}));
                        holes["set"](faceCounter, (resultProfiles->holes || js::array<js::any>{}));
                        faceCounter++;
            }
    }
    const ShellData result = []() {
          js::object obj_temp_1;
          obj_temp_1.set("bbox", bbox);
          obj_temp_1.set("type", ../../../../../Schema::RepresentationClass.SHELL);
          obj_temp_1.set("profiles", profiles);
          obj_temp_1.set("holes", holes);
          obj_temp_1.set("points", points["get"]());
          return js::any(obj_temp_1);
        }();
    return result;
}
