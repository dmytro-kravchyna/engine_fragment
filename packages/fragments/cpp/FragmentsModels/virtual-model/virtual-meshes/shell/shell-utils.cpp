#include "index_generated.h"
#include "shell-utils.h"

using namespace js;

auto ShellUtils::getProfile(Shell shell, js::number id, std::optional<js::any> input) {
    {
            const js::any isBigShell = shell["type"]() === ShellType::BIG;
            if (isBigShell) {
                        {
                                        return shell["bigProfiles"](id, input);
                        }
            }
            return shell["profiles"](id, input);
    }
}

auto ShellUtils::getPoints(Shell shell) {
    {
            const std::shared_ptr<Float32Array> points = std::make_shared<Float32Array>((shell["pointsLength"]() * js::number(3)));
            for (js::number i = js::number(0); (i < shell["pointsLength"]()); i++) {
                        {
                                        shell["points"](i, this->_tempPoint);
                                        points[(i * js::number(3))] = this->_tempPoint.x();
                                        points[((i * js::number(3)) + js::number(1))] = this->_tempPoint.y();
                                        points[((i * js::number(3)) + js::number(2))] = this->_tempPoint.z();
                        }
            }
            return points;
    }
}

auto ShellUtils::getProfileIndices(Shell shell, js::number profileId) {
    {
            const js::any isBigShell = shell["type"]() === ShellType::BIG;
            const js::any indices = []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("outer", js::array<js::any>{});
                  obj_temp_0.set("inners", js::array<js::any>{});
                  return js::any(obj_temp_0);
                }();
            const js::any length = (js::null ? js::null : js::null);
            const js::any holeId = (js::null ? js::null : js::null);
            const js::any profile = ShellUtils::getProfile(shell, profileId);
            indices["outer"] = js::array.from(profile["indicesArray"]());
            for (js::number i = js::number(0); (i < length); i++) {
                        {
                                        const js::any hole = shell[holeId](i);
                                        if (hole["profileId"]() === profileId) {
                                                            {
                                                                                    const js::any currentIndices = js::array.from(hole["indicesArray"]());
                                                                                    indices["inners"].push(currentIndices);
                                                            }
                                        }
                        }
            }
            return indices;
    }
}

auto ShellUtils::getHole(Shell shell, js::number id, std::optional<js::any> input) {
    {
            const js::any isBigShell = shell["type"]() === ShellType::BIG;
            if (isBigShell) {
                        {
                                        return shell["bigHoles"](id, input);
                        }
            }
            return shell["holes"](id, input);
    }
}

auto ShellUtils::getProfilesLength(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return shell["bigProfilesLength"]();
                        }
            }
            return shell["profilesLength"]();
    }
}

auto ShellUtils::getHolesLength(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return shell["bigHolesLength"]();
                        }
            }
            return shell["holesLength"]();
    }
}

auto ShellUtils::getShell(Meshes meshes, js::number id) {
    {
            return meshes["shells"](id, this->_shell);
    }
}

auto ShellUtils::point(Shell shell, js::number id, js::any result) {
    {
            if (js::instanceof_op(shell, "Shell")) {
                        {
                                        shell["points"](id, this->_tempPoint);
                        }
            }
            const js::any x = this->_tempPoint.x();
            const js::any y = this->_tempPoint.y();
            const js::any z = this->_tempPoint.z();
            result->set(x, y, z);
    }
}

auto ShellUtils::getNormalsOfShellProfile(Shell shell, js::array<unknown> result) {
    {
            const js::any count = ShellUtils::getProfilesLength(shell);
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        const js::any profile = ShellUtils::getProfile(shell, id);
                                        const js::any normals = this->fetchNormalsOfProfile(shell, profile);
                                        result.push(normals);
                        }
            }
            return result;
    }
}

auto ShellUtils::computeNormalsAvg(js::any indices, js::number faceId, js::array<unknown> faceNormals, Map pointsFaces) {
    {
            this->setupNormalBuffer(indices);
            const js::any profileNormal = faceNormals->faceId;
            for (js::number id = js::number(0); (id < indices.length()); id++) {
                        {
                                        const js::any current = indices[id];
                                        const js::any pointsByProfile = pointsFaces->get(current);
                                        this->aggregateNormals(pointsByProfile, faceNormals, profileNormal);
                                        this->computeAvgNormal(id);
                        }
            }
            return this->_normalBuffer;
    }
}

auto ShellUtils::getBuffer(Shell shell) {
    {
            const js::any data = shell["bb"];
            const js::number distance = js::number(8);
            const js::any shellOffset = data->__offset(shell["bb_pos"], distance);
            const js::number length = (shell["pointsLength"]() * js::number(3));
            const js::any offset = data->__vector((shell["bb_pos"] + shellOffset));
            const js::any rawBytes = data->bytes();
            const js::any rawBuffer = rawBytes->buffer;
            return std::make_shared<Float32Array>(rawBuffer, offset, length);
    }
}

auto ShellUtils::getPointsShell(Shell shell) {
    {
            this->_pointsByProfile.clear();
            this->fetchAllPointsByProfile(shell);
            ShellUtils::fetchAllPointsByHole(shell);
            return this->_pointsByProfile;
    }
}

auto ShellUtils::addNormals(js::array<js::number> pointsByProfile, js::array<unknown> faceNormals, js::any profileNormal) {
    {
            for (const auto& id : pointsByProfile) {
                        {
                                        const js::any normal = faceNormals->id;
                                        const js::any dot = profileNormal->dot(normal);
                                        const bool isValid = (dot > this->_faceThreshold);
                                        if (!isValid) {
                                                            continue;
                                        }
                                        this->_tempNormal.add(normal);
                        }
            }
    }
}

auto ShellUtils::setupNormalBuffer(js::any indices) {
    {
            const js::number neededSize = (indices.length() * js::number(3));
            const js::any currentSize = this->_normalBuffer.length();
            const bool insufficientSize = (currentSize < neededSize);
            if (insufficientSize) {
                        {
                                        this->_normalBuffer = std::make_shared<Int16Array>(neededSize);
                        }
            }
    }
}

auto ShellUtils::fetchNormalsOfProfile(Shell shell, js::any profile) {
    {
            const js::any length = profile["indicesLength"]();
            const js::any tooSmall = this->isTooSmall(shell, length);
            if (tooSmall) {
                        {
                                        return std::make_shared<three::Vector3>(js::number(1), js::number(0), js::number(0));
                        }
            }
            return this->computeProfileNormal(length, profile, shell);
    }
}

auto ShellUtils::fetchAllPointsByHole(Shell shell) {
    {
            const js::any holesCount = ShellUtils::getHolesLength(shell);
            const js::any hole = this->getTempHole(shell);
            for (js::number holeId = js::number(0); (holeId < holesCount); holeId++) {
                        {
                                        ShellUtils::getHole(shell, holeId, hole);
                                        const js::any id = hole["profileId"]();
                                        const js::any indicesCount = hole["indicesLength"]();
                                        for (js::number i = js::number(0); (i < indicesCount); i++) {
                                                            {
                                                                                    const js::any index = hole["indices"](i);
                                                                                    ShellUtils::savePointByProfile(index, id);
                                                            }
                                        }
                        }
            }
    }
}

auto ShellUtils::computeProfileNormal(js::number length, js::any profile, Shell shell) {
    {
            this->_v3.set(js::number(0), js::number(0), js::number(0));
            for (js::number id = js::number(0); (id < length); id++) {
                        {
                                        this->fetchPointsForNormal(id, length, profile, shell);
                                        this->computeProfilePointNormal();
                        }
            }
            const js::any result = this->_v3.clone();
            result->normalize();
            return result;
    }
}

auto ShellUtils::computeProfilePointNormal() {
    {
            const js::number dx = (this->_v1.x - this->_v2.x);
            const js::number dy = (this->_v1.y - this->_v2.y);
            const js::number dz = (this->_v1.z - this->_v2.z);
            const js::number sumX = (this->_v1.x + this->_v2.x);
            const js::number sumY = (this->_v1.y + this->_v2.y);
            const js::number sumZ = (this->_v1.z + this->_v2.z);
            this->_v3.x += (dy * sumZ);
            this->_v3.y += (dz * sumX);
            this->_v3.z += (dx * sumY);
    }
}

auto ShellUtils::aggregateNormals(js::typed::Nullable<js::array<js::number>> pointsByProfile, js::array<unknown> faceNormals, js::any profileNormal) {
    {
            this->_tempNormal.set(js::number(0), js::number(0), js::number(0));
            const js::any isZero = (!pointsByProfile || !pointsByProfile.length());
            if (isZero) {
                        {
                                        this->_tempNormal.set(js::number(1), js::number(0), js::number(0));
                                        return;
                        }
            }
            const js::any isJustOne = pointsByProfile.length() === js::number(1);
            if (isJustOne) {
                        {
                                        const js::any first = pointsByProfile->js::number(0);
                                        this->_tempNormal = faceNormals->first->clone();
                                        return;
                        }
            }
            ShellUtils::addNormals(pointsByProfile, faceNormals, profileNormal);
    }
}

auto ShellUtils::fetchPointsForNormal(js::number id, js::number length, js::any profile, Shell shell) {
    {
            const js::number next = (id + js::number(1));
            const js::number id2 = (next % length);
            const js::any profile1 = profile["indices"](id);
            const js::any profile2 = profile["indices"](id2);
            this->point(shell, profile1, this->_v1);
            this->point(shell, profile2, this->_v2);
    }
}

auto ShellUtils::savePointByProfile(js::number index, js::number id) {
    {
            if (!this->_pointsByProfile.has(index)) {
                        {
                                        this->_pointsByProfile.set(index, js::array<js::any>{});
                        }
            }
            this->_pointsByProfile.get(index).push(id);
    }
}

auto ShellUtils::isTooSmall(Shell shell, js::number length) {
    {
            const js::any notEnoughPoints = shell["pointsLength"]() <= js::number(2);
            const js::any notEnoughIndices = length <= js::number(2);
            return (notEnoughPoints || notEnoughIndices);
    }
}

auto ShellUtils::fetchAllPointsByProfile(Shell shell) {
    {
            const js::any count = this->getProfilesLength(shell);
            const js::any profile = this->getTempProfile(shell);
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        ShellUtils::getProfile(shell, id, profile);
                                        const js::any indicesCount = profile["indicesLength"]();
                                        for (js::number i = js::number(0); (i < indicesCount); i++) {
                                                            {
                                                                                    const js::any index = profile["indices"](i);
                                                                                    ShellUtils::savePointByProfile(index, id);
                                                            }
                                        }
                        }
            }
    }
}

auto ShellUtils::computeAvgNormal(js::number id) {
    {
            this->_tempNormal.normalize();
            this->_tempNormal.multiplyScalar(normalizationValue);
            this->_tempNormal.toArray(this->_normalBuffer, (id * js::number(3)));
    }
}

auto ShellUtils::getTempProfile(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return this->_bigShellProfile;
                        }
            }
            return this->_shellProfile;
    }
}

auto ShellUtils::getTempHole(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return this->_bigShellHole;
                        }
            }
            return this->_shellHole;
    }
}
