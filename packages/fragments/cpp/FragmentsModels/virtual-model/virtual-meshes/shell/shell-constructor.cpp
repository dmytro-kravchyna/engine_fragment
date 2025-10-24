#include "index_generated.h"
#include "shell-constructor.h"

using namespace js;

auto ShellConstructor::construct(Shell shell, js::any meshData) {
    {
            this->resetConstructData(meshData);
            this->getPointsPerWire(shell);
            const js::any data = ShellUtils::getBuffer(shell);
            this->newShellInteriorProfiles(shell);
            this->constructShell(shell, data, meshData);
            this->_tileData = js::undefined;
    }
}

auto ShellConstructor::getIntProfileNormalsAvg(Shell shell, js::number id) {
    {
            const js::any hole = this->getTempHole(shell);
            const js::any indices = hole["indicesArray"]();
            this->normalsAvgInterior = ShellUtils::computeNormalsAvg(indices, id, this->_normals, this->_pointsPerProfile);
    }
}

auto ShellConstructor::saveInteriorProfile(Shell shell) {
    {
            const js::any hole = this->getTempHole(shell);
            const js::any id = hole["profileId"]();
            if (this->interiorProfiles.has(id)) {
                        {
                                        this->saveExistingInteriorProfile(id);
                                        return id;
                        }
            }
            const js::any data = this->getNewIntProfileData();
            this->interiorProfiles.set(id, data);
            return id;
    }
}

auto ShellConstructor::computeNormalsAvg(Shell shell, js::any indices, js::number id) {
    {
            const js::any isShell = this->isShell(shell);
            if (!isShell) {
                        return;
            }
            const js::any n = this->_normals;
            const js::any ppp = this->_pointsPerProfile;
            this->_normalsAvg = ShellUtils::computeNormalsAvg(indices, id, n, ppp);
    }
}

auto ShellConstructor::isShell(Shell shell) {
    {
            return js::instanceof_op(shell, "Shell");
    }
}

auto ShellConstructor::getPointsPerWire(Shell shell) {
    {
            const js::any isShell = this->isShell(shell);
            if (!isShell) {
                        return;
            }
            ShellUtils::getNormalsOfShellProfile(shell, this->_normals);
            this->_pointsPerProfile = ShellUtils::getPointsShell(shell);
    }
}

auto ShellConstructor::getIndices(Shell shell, js::number id) {
    {
            const js::any profile = this->getTempProfile(shell);
            ShellUtils::getProfile(shell, id, profile);
            return profile["indicesArray"]();
    }
}

auto ShellConstructor::resetConstructData(AnyTileData meshData) {
    {
            this->_indices = js::number(0);
            this->_tileData = js::undefined;
            this->nextBuffer(meshData);
            this->_normals.length() = js::number(0);
    }
}

auto ShellConstructor::initializeIndices() {
    {
            const js::any size = this->_tileData.indexCount;
            this->_tileData.indexBuffer = std::make_shared<Uint16Array>(size);
    }
}

auto ShellConstructor::constructFace4(js::any indices, js::Float32Array data, js::number id) {
    {
            const js::any faceId = this->getNextFaceId();
            ShellFace4::create(indices, data, this->_normalsAvg, id, this->_tileData, this->_sizes, faceId);
    }
}

auto ShellConstructor::initializeSizes() {
    {
            this->_sizes.vertices = js::number(0);
            this->_sizes.indices = js::number(0);
            this->_sizes.verticesAmount = js::number(0);
            this->_sizes.normalsAmount = js::number(0);
            this->_sizes.normals = js::number(0);
    }
}

auto ShellConstructor::getInteriorProfileBuffer(Shell shell, ShellHoleData intProfile) {
    {
            const js::any hole = this->getTempHole(shell);
            const js::any count = hole["indicesLength"]();
            const js::any isShell = this->isShell(shell);
            if (!isShell) {
                        return;
            }
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        this->getIntProfilePoints(id, shell, intProfile);
                                        this->getIntProfileNormals(intProfile, id);
                        }
            }
    }
}

auto ShellConstructor::constructProfile(js::number id, Shell shell, js::any indices, js::Float32Array data) {
    {
            const js::any profile = this->getTempProfile(shell);
            const js::any indexAmount = profile["indicesLength"]();
            const js::any notAHole = !this->interiorProfiles.has(id);
            const js::any isFace3 = indexAmount === PolygonSize::three;
            if ((isFace3 && notAHole)) {
                        {
                                        this->constructFace3(indices, data);
                                        return;
                        }
            }
            const js::any isFace4 = indexAmount === PolygonSize::four;
            if ((isFace4 && notAHole)) {
                        {
                                        this->constructFace4(indices, data, id);
                                        return;
                        }
            }
            this->constructFaceX(indices, data, id);
    }
}

auto ShellConstructor::getIntProfileNormals(ShellHoleData hole, js::number id) {
    {
            const js::number index = (id * js::number(3));
            const js::any nx = this->normalsAvgInterior[index];
            const js::any ny = this->normalsAvgInterior[(index + js::number(1))];
            const js::any nz = this->normalsAvgInterior[(index + js::number(2))];
            hole["normals"].push(nx, ny, nz);
    }
}

auto ShellConstructor::saveExistingInteriorProfile(js::number id) {
    {
            const js::any found = this->interiorProfiles.get(id);
            const js::any pointCount = found["points"].length();
            const js::number indexCount = (pointCount / js::number(3));
            found["indices"].push(indexCount);
            this->interiorProfiles.set(id, found);
    }
}

auto ShellConstructor::getNewIntProfileData() {
    {
            js::array<js::number> indices = js::array<js::number>{js::number(0)};
            js::array<js::any> points = js::array<js::any>{};
            js::array<js::any> normals = js::array<js::any>{};
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("indices", indices);
                  obj_temp_0.set("points", points);
                  obj_temp_0.set("normals", normals);
                  return js::any(obj_temp_0);
                }();
    }
}

auto ShellConstructor::constructFace3(js::any indices, js::Float32Array data) {
    {
            const js::any faceId = this->getNextFaceId();
            ShellFace3::create(indices, data, this->_normalsAvg, this->_tileData, this->_sizes, faceId);
    }
}

auto ShellConstructor::getIntProfilePoints(js::number i, Shell shell, ShellHoleData holeData) {
    {
            const js::any hole = this->getTempHole(shell);
            const js::any shellIndex = hole["indices"](i);
            shell["points"](shellIndex, this->point);
            const js::any px = this->point.x();
            const js::any py = this->point.y();
            const js::any pz = this->point.z();
            holeData->points.push(px, py, pz);
    }
}

auto ShellConstructor::manageMemory(Shell shell, js::any meshData) {
    {
            const js::any profile = this->getTempProfile(shell);
            const js::any indexAmount = profile["indicesLength"]();
            const js::number vertexAmount = (this->_sizes.verticesAmount / js::number(3));
            const js::number memoryConsumed = (vertexAmount + indexAmount);
            const bool memoryOverflow = (memoryConsumed > limitOf2Bytes);
            if (memoryOverflow) {
                        {
                                        this->nextBuffer(meshData);
                        }
            }
    }
}

auto ShellConstructor::initializeFaceIds() {
    {
            const js::any size = this->_tileData.positionCount;
            this->_tileData.faceIdBuffer = std::make_shared<Uint32Array>((size / js::number(3)));
    }
}

auto ShellConstructor::getNextFaceId() {
    {
            return this->_nextFaceId++;
    }
}

auto ShellConstructor::newShellInteriorProfiles(Shell shell) {
    {
            this->interiorProfiles.clear();
            const js::any count = ShellUtils::getHolesLength(shell);
            const js::any hole = this->getTempHole(shell);
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        ShellUtils::getHole(shell, i, hole);
                                        const js::any id = this->saveInteriorProfile(shell);
                                        const js::any intProfile = this->interiorProfiles.get(id);
                                        this->getIntProfileNormalsAvg(shell, id);
                                        this->getInteriorProfileBuffer(shell, intProfile);
                        }
            }
            return this->interiorProfiles;
    }
}

auto ShellConstructor::initializePositions() {
    {
            const js::any size = this->_tileData.positionCount;
            this->_tileData.positionBuffer = std::make_shared<Float32Array>(size);
    }
}

auto ShellConstructor::initializeNormals() {
    {
            const js::any size = this->_tileData.normalCount;
            this->_tileData.normalBuffer = std::make_shared<Int16Array>(size);
    }
}

auto ShellConstructor::setTileData(AnyTileData bufferGeometries) {
    {
            if (js::array.isArray(bufferGeometries)) {
                        {
                                        this->_tileData = bufferGeometries->this->_indices;
                                        return;
                        }
            }
            this->_tileData = bufferGeometries;
    }
}

auto ShellConstructor::constructShell(Shell shell, js::Float32Array data, AnyTileData meshData) {
    {
            const js::any count = ShellUtils::getProfilesLength(shell);
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        const js::any indices = this->getIndices(shell, id);
                                        this->computeNormalsAvg(shell, indices, id);
                                        this->constructProfile(id, shell, indices, data);
                                        this->manageMemory(shell, meshData);
                        }
            }
    }
}

auto ShellConstructor::constructFaceX(js::any indices, js::Float32Array data, js::number id) {
    {
            const js::any faceId = this->getNextFaceId();
            ShellFaceX::create(indices, data, this->_normalsAvg, id, this->_tileData, this->interiorProfiles, this->_sizes, faceId);
    }
}

auto ShellConstructor::getTempProfile(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return this->_bigShellProfile;
                        }
            }
            return this->_shellProfile;
    }
}

auto ShellConstructor::getTempHole(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return this->_bigShellHole;
                        }
            }
            return this->_shellHole;
    }
}
