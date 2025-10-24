#include "index_generated.h"
#include "shell-face-raycaster.h"

using namespace js;

ShellFaceRaycaster::ShellFaceRaycaster(Meshes meshes) {
    {
            this->_meshes = meshes;
    }
}

auto ShellFaceRaycaster::faceRaycast(js::number id, js::any ray) {
    {
            const js::any shell = ShellUtils::getShell(this->_meshes, id);
            this->resetData();
            this->getInteriorProfiles(shell);
            const js::any buffer = ShellUtils::getBuffer(shell);
            this->processAllCollisions(shell, buffer, ray);
            return this->includedVertices;
    }
}

auto ShellFaceRaycaster::resetVectors() {
    {
            this->a.set(js::number(0), js::number(0), js::number(0));
            this->b.set(js::number(0), js::number(0), js::number(0));
            this->c.set(js::number(0), js::number(0), js::number(0));
            this->d.set(js::number(0), js::number(0), js::number(0));
    }
}

auto ShellFaceRaycaster::resetData() {
    {
            this->includedVertices.length() = js::number(0);
            this->interiorProfiles.clear();
    }
}

auto ShellFaceRaycaster::getInteriorProfiles(Shell shell) {
    {
            const js::any holesLength = ShellUtils::getHolesLength(shell);
            for (js::number holeId = js::number(0); (holeId < holesLength); holeId++) {
                        {
                                        const js::any hole = ShellUtils::getHole(shell, holeId);
                                        const js::any profileId = hole["profileId"]();
                                        if (!this->interiorProfiles.has(profileId)) {
                                                            {
                                                                                    this->interiorProfiles.set(profileId, js::array<js::any>{});
                                                            }
                                        }
                                        const js::any profiles = this->interiorProfiles.get(profileId);
                                        profiles.push(holeId);
                        }
            }
    }
}

auto ShellFaceRaycaster::processTriangle(DataBuffer indices, DataBuffer buffer, js::any ray) {
    {
            const js::number first = (indices[js::number(0)] * js::number(3));
            const js::number second = (indices[js::number(1)] * js::number(3));
            const js::number third = (indices[js::number(2)] * js::number(3));
            this->saveTriPoint(this->e, buffer, first);
            this->saveTriPoint(this->f, buffer, second);
            this->saveTriPoint(this->g, buffer, third);
            const js::any found = this->triangleHit(ray);
            if (found) {
                        {
                                        const js::any triangleBuffer = this->getTriangleBuffer(buffer, indices);
                                        found["facePoints"] = triangleBuffer->points;
                                        found["faceIndices"] = triangleBuffer->indices;
                                        this->includedVertices.push(found);
                        }
            }
    }
}

auto ShellFaceRaycaster::processAllCollisions(Shell shell, DataBuffer buffer, js::any ray) {
    {
            const js::any count = ShellUtils::getProfilesLength(shell);
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        this->resetVectors();
                                        const js::any indices = this->getIndices(shell, id);
                                        const js::any valid = this->getValidCollision(indices, buffer, ray, id, shell);
                                        if (valid) {
                                                            {
                                                                                    this->processCollision(shell, id, buffer, indices);
                                                            }
                                        }
                        }
            }
    }
}

auto ShellFaceRaycaster::saveTriPoint(js::any vector, DataBuffer buffer, js::number first) {
    {
            const js::any x1 = buffer[first];
            const js::any y1 = buffer[(first + js::number(1))];
            const js::any z1 = buffer[(first + js::number(2))];
            vector["set"](x1, y1, z1);
    }
}

auto ShellFaceRaycaster::getIndices(Shell shell, js::number id) {
    {
            const js::any currentProfile = ShellUtils::getProfile(shell, id);
            return currentProfile->indicesArray();
    }
}

auto ShellFaceRaycaster::getIsTriangle(DataBuffer indices) {
    {
            const js::any indexAmount = indices.length();
            return indexAmount === js::number(3);
    }
}

auto ShellFaceRaycaster::getNormal() {
    {
            this->tempTriangle.a = this->e;
            this->tempTriangle.b = this->f;
            this->tempTriangle.c = this->g;
            const std::shared_ptr<three::Vector3> result = std::make_shared<three::Vector3>();
            this->tempTriangle.getNormal(result);
            return result;
    }
}

auto ShellFaceRaycaster::isHole(js::number id, Shell shell, DataBuffer buffer) {
    {
            if (this->interiorProfiles.has(id)) {
                        {
                                        const js::any interiorProfiles = this->interiorProfiles.get(id);
                                        return this->holeContains(interiorProfiles, shell, buffer);
                        }
            }
            return false;
    }
}

auto ShellFaceRaycaster::computeNormal(DataBuffer data, DataBuffer indices) {
    {
            this->d.set(js::number(0), js::number(0), js::number(0));
            const js::any count = indices.length();
            for (js::number i1 = js::number(0); (i1 < count); i1++) {
                        {
                                        const js::number i2 = ((i1 + js::number(1)) % count);
                                        const js::number a = (indices[i1] * js::number(3));
                                        const js::number b = (indices[i2] * js::number(3));
                                        this->processNormal(data, a, b);
                        }
            }
            this->d.normalize();
    }
}

auto ShellFaceRaycaster::holeContains(js::array<js::number> indices, Shell shell, DataBuffer data) {
    {
            const js::any count = indices.length();
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        const js::any shellHole = ShellUtils::getHole(shell, indices[i]);
                                        const js::any index = shellHole->indicesArray();
                                        const js::any contained = this->polygonContains(data, index);
                                        if (contained) {
                                                            {
                                                                                    return true;
                                                            }
                                        }
                        }
            }
            return false;
    }
}

auto ShellFaceRaycaster::triangleHit(js::any ray) {
    {
            const js::any e = this->e;
            const js::any f = this->f;
            const js::any g = this->g;
            const js::any hits = ray["intersectTriangle"](e, f, g, false, this->h);
            if (!hits) {
                        {
                                        return js::undefined;
                        }
            }
            const js::any normal = this->getNormal();
            const js::any point = this->h.clone();
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("point", point);
                  obj_temp_0.set("normal", normal);
                  return js::any(obj_temp_0);
                }();
    }
}

auto ShellFaceRaycaster::getValidCollision(DataBuffer indices, DataBuffer buffer, js::any ray, js::number id, Shell shell) {
    {
            const js::any isTriangle = this->getIsTriangle(indices);
            if (isTriangle) {
                        {
                                        this->processTriangle(indices, buffer, ray);
                                        return false;
                        }
            }
            const js::any collidesPlane = this->getCollidesPlane(indices, buffer, ray);
            if (!collidesPlane) {
                        {
                                        return false;
                        }
            }
            const js::any isHole = this->isHole(id, shell, buffer);
            if (isHole) {
                        {
                                        return false;
                        }
            }
            return true;
    }
}

auto ShellFaceRaycaster::processCollision(Shell shell, js::number profileId, DataBuffer buffer, DataBuffer indices) {
    {
            const js::any contains = this->polygonContains(buffer, indices);
            if (!contains) {
                        return;
            }
            const js::any point = this->b.clone();
            const js::any normal = this->tempPlane.normal.clone();
            const js::any faceBuffer = this->getFaceBuffer(shell, profileId, buffer);
            this->includedVertices.push([]() {
                  js::object obj_temp_1;
                  obj_temp_1.set("point", point);
                  obj_temp_1.set("normal", normal);
                  obj_temp_1.set("facePoints", faceBuffer->points);
                  obj_temp_1.set("faceIndices", faceBuffer->indices);
                  return js::any(obj_temp_1);
                }());
    }
}

auto ShellFaceRaycaster::newOrthoNormalBasis() {
    {
            const js::any a1 = this->tempPlane.normal;
            const js::any a2 = this->j;
            const js::any a3 = this->i;
            const js::any n1 = js::Math::abs(a1["x"]);
            const js::any n2 = js::Math::abs(a1["y"]);
            if (n1 >= n2) {
                        {
                                        const js::number inverse = (js::number(1) / js::Math::sqrt(((a1["x"] * a1["x"]) + (a1["z"] * a1["z"]))));
                                        const js::number a2x = (-a1["z"] * inverse);
                                        const js::number a2y = js::number(0);
                                        const js::number a2z = (a1["x"] * inverse);
                                        a2["set"](a2x, a2y, a2z);
                                        const js::number a3x = (a1["y"] * a2["z"]);
                                        const js::number a3y = ((a1["z"] * a2["x"]) - (a1["x"] * a2["z"]));
                                        const js::number a3z = (-a1["y"] * a2["x"]);
                                        a3["set"](a3x, a3y, a3z);
                        }
            } else {
                        {
                                        const js::number inverse = (js::number(1) / js::Math::sqrt(((a1["y"] * a1["y"]) + (a1["z"] * a1["z"]))));
                                        const js::number a2x = js::number(0);
                                        const js::number a2y = (a1["z"] * inverse);
                                        const js::number a2z = (-a1["y"] * inverse);
                                        a2["set"](a2x, a2y, a2z);
                                        const js::number a3x = ((a1["y"] * a2["z"]) - (a1["z"] * a2["y"]));
                                        const js::number a3y = (-a1["x"] * a2["z"]);
                                        const js::number a3z = (a1["x"] * a2["y"]);
                                        a3["set"](a3x, a3y, a3z);
                        }
            }
            a2["normalize"]();
            a3["normalize"]();
    }
}

auto ShellFaceRaycaster::polygonContains(DataBuffer data, DataBuffer indices) {
    {
            bool contains = false;
            this->newOrthoNormalBasis();
            this->setPolyContainVec(indices, data);
            js::any a = this->k.dot(this->i);
            js::any b = this->k.dot(this->j);
            for (js::number i = js::number(0); (i < indices.length()); i++) {
                        {
                                        const js::number current = (indices[i] * js::number(3));
                                        const js::any x = data->current;
                                        const js::any y = data->(current + js::number(1));
                                        const js::any z = data->(current + js::number(2));
                                        this->k.set(x, y, z);
                                        this->k.sub(this->b);
                                        const js::any c = this->k.dot(this->i);
                                        const js::any d = this->k.dot(this->j);
                                        const bool n1 = (d > js::number(0));
                                        const bool n2 = (b > js::number(0));
                                        if (n1 !== n2) {
                                                            {
                                                                                    const bool crosses = (((((a - c) * -d) / (b - d)) + c) > js::number(0));
                                                                                    if (crosses) {
                                                                                                                {
                                                                                                                                                contains = !contains;
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                                        a = c;
                                        b = d;
                        }
            }
            return contains;
    }
}

auto ShellFaceRaycaster::processNormal(DataBuffer data, js::number i1, js::number i2) {
    {
            const js::any x1 = data->(i1 + js::number(0));
            const js::any x2 = data->(i2 + js::number(0));
            const js::any y1 = data->(i1 + js::number(1));
            const js::any y2 = data->(i2 + js::number(1));
            const js::any z1 = data->(i1 + js::number(2));
            const js::any z2 = data->(i2 + js::number(2));
            this->d.x += ((y1 - y2) * (z1 + z2));
            this->d.y += ((z1 - z2) * (x1 + x2));
            this->d.z += ((x1 - x2) * (y1 + y2));
    }
}

auto ShellFaceRaycaster::getCollidesPlane(DataBuffer indices, DataBuffer buffer, js::any ray) {
    {
            const js::number first = (indices[js::number(0)] * js::number(3));
            const js::any x = buffer[first];
            const js::any y = buffer[(first + js::number(1))];
            const js::any z = buffer[(first + js::number(2))];
            this->a.set(x, y, z);
            this->computeNormal(buffer, indices);
            this->tempPlane.setFromNormalAndCoplanarPoint(this->d, this->a);
            const js::any collidesPlane = ray["intersectPlane"](this->tempPlane, this->b);
            return collidesPlane;
    }
}

auto ShellFaceRaycaster::setPolyContainVec(DataBuffer indices, DataBuffer data) {
    {
            const js::number end = (indices[(indices.length() - js::number(1))] * js::number(3));
            const js::any x = data->end;
            const js::any y = data->(end + js::number(1));
            const js::any z = data->(end + js::number(2));
            this->k.set(x, y, z);
            this->k.sub(this->b);
    }
}

auto ShellFaceRaycaster::getTriangleBuffer(DataBuffer buffer, DataBuffer indices) {
    {
            js::array<js::number> points = js::array<js::any>{};
            js::array<js::number> newIndices = js::array<js::any>{};
            for (js::number i = js::number(0); (i < indices.length()); i++) {
                        {
                                        const js::number index = (indices[i] * js::number(3));
                                        points.push(buffer[index], buffer[(index + js::number(1))], buffer[(index + js::number(2))]);
                                        newIndices.push(i);
                        }
            }
            return []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("points", std::make_shared<Float32Array>(points));
                  obj_temp_2.set("indices", newIndices);
                  return js::any(obj_temp_2);
                }();
    }
}

auto ShellFaceRaycaster::getFaceBuffer(Shell shell, js::number profileId, DataBuffer buffer) {
    {
            const js::any indices = ShellUtils::getProfileIndices(shell, profileId);
            auto _temp9972 = indices;
            const auto outer = _temp9972["outer"];
            const auto inners = _temp9972["inners"];
            js::array<js::number> points = js::array<js::any>{};
            for (js::number i = js::number(0); (i < outer.length()); i++) {
                        {
                                        const js::number index = (outer[i] * js::number(3));
                                        points.push(buffer[index], buffer[(index + js::number(1))], buffer[(index + js::number(2))]);
                        }
            }
            js::array<js::any> holesIndices = js::array<js::any>{};
            for (js::number i = js::number(0); (i < inners.length()); i++) {
                        {
                                        const js::any currentHole = inners[i];
                                        holesIndices.push((points.length() / js::number(3)));
                                        for (js::number j = js::number(0); (j < currentHole.length()); j++) {
                                                            {
                                                                                    const js::number index = (currentHole->j * js::number(3));
                                                                                    points.push(buffer[index], buffer[(index + js::number(1))], buffer[(index + js::number(2))]);
                                                            }
                                        }
                        }
            }
            const std::shared_ptr<three::Vector3> a = std::make_shared<three::Vector3>();
            const std::shared_ptr<three::Vector3> b = std::make_shared<three::Vector3>();
            const std::shared_ptr<three::Vector3> c = std::make_shared<three::Vector3>();
            a["set"](points[js::number(0)], points[js::number(1)], points[js::number(2)]);
            b["set"](points[js::number(3)], points[js::number(4)], points[js::number(5)]);
            c["set"](points[js::number(6)], points[js::number(7)], points[js::number(8)]);
            const std::shared_ptr<three::Triangle> tri = std::make_shared<three::Triangle>();
            tri["set"](a, b, c);
            const std::shared_ptr<three::Vector3> normal = std::make_shared<three::Vector3>();
            tri["getNormal"](normal);
            auto _temp1999 = FaceUtils::getEarcutDimensions(normal);
            const auto dim1 = _temp1999[0];
            const auto dim2 = _temp1999[1];
            js::array<js::any> projectedPoints = js::array<js::any>{};
            for (js::number i = js::number(0); (i < points.length()); i += js::number(3)) {
                        {
                                        const js::any x = points[i];
                                        const js::any y = points[(i + js::number(1))];
                                        const js::any z = points[(i + js::number(2))];
                                        js::array<js::any> point = js::array<js::any>{x, y, z};
                                        projectedPoints.push(point[dim1], point[dim2]);
                        }
            }
            const js::any result = earcut(projectedPoints, holesIndices);
            return []() {
                  js::object obj_temp_3;
                  obj_temp_3.set("points", std::make_shared<Float32Array>(points));
                  obj_temp_3.set("indices", result);
                  return js::any(obj_temp_3);
                }();
    }
}
