#include "index_generated.h"
#include "shell-line-raycaster.h"

using namespace js;

ShellLineRaycaster::ShellLineRaycaster(Meshes meshes) {
    {
            this->_meshes = meshes;
    }
}

auto ShellLineRaycaster::lineRaycast(js::number id, js::any ray, js::any frustum) {
    {
            this->resetData(id);
            this->lineRaycastItems(ray, frustum);
            return this->_result;
    }
}

auto ShellLineRaycaster::lineRaycastItems(js::any ray, js::any frustum) {
    {
            const js::any profilesCount = ShellUtils::getProfilesLength(this->_shell);
            for (js::number id = js::number(0); (id < profilesCount); id++) {
                        {
                                        const js::any profile = this->getTempProfile(this->_shell);
                                        ShellUtils::getProfile(this->_shell, id, profile);
                                        this->lineRaycastProfile(ray, frustum, id);
                        }
            }
    }
}

auto ShellLineRaycaster::resetData(js::number id) {
    {
            this->_shell = ShellUtils::getShell(this->_meshes, id);
            this->_normals.length() = js::number(0);
            ShellUtils::getNormalsOfShellProfile(this->_shell, this->_normals);
            this->_pointsByProfile = ShellUtils::getPointsShell(this->_shell);
            this->_result = js::array<js::any>{};
    }
}

auto ShellLineRaycaster::lineRaycastProfile(js::any ray, js::any frustum, js::number id) {
    {
            const js::any profile = this->getTempProfile(this->_shell);
            const js::any indicesCount = profile["indicesLength"]();
            for (js::number i = js::number(0); (i < indicesCount); i++) {
                        {
                                        const js::any i1 = profile["indices"](i);
                                        const js::any i2 = this->getSecondIndex(i, indicesCount);
                                        const js::any success = this->cast(i1, i2, ray, frustum, id);
                                        if (success) {
                                                            {
                                                                                    this->saveResult(id);
                                                            }
                                        }
                        }
            }
    }
}

auto ShellLineRaycaster::isInvalidAngle(js::number firstIndex, js::number secondIndex, js::number id) {
    {
            const js::any profile = this->getProfile(firstIndex, secondIndex, id);
            if (!profile.length()) {
                        {
                                        return true;
                        }
            }
            const js::any normal1 = this->_normals[profile[js::number(0)]];
            const js::any normal2 = this->_normals[id];
            const js::any angle = normal1["dot"](normal2);
            return (angle > js::Math::cos(this->_minAngle));
    }
}

auto ShellLineRaycaster::getProfile(js::number firstIndex, js::number secondIndex, js::number id) {
    {
            const js::any profile1 = this->_pointsByProfile.get(firstIndex);
            const js::any profile2 = this->_pointsByProfile.get(secondIndex);
            js::array<js::number> result = js::array<js::any>{};
            for (const auto& index : profile1) {
                        {
                                        if (profile2.indexOf(index) === -js::number(1)) {
                                                            continue;
                                        }
                                        if (index === id) {
                                                            continue;
                                        }
                                        result.push(index);
                        }
            }
            return result;
    }
}

auto ShellLineRaycaster::cast(js::number i1, js::number i2, js::any ray, js::any frustum, js::number id) {
    {
            ShellUtils::point(this->_shell, i1, this->_tempV1);
            ShellUtils::point(this->_shell, i2, this->_tempV2);
            this->raycastSegment(ray);
            const js::any pointFound = frustum["containsPoint"](this->_tempPoint);
            if (!pointFound) {
                        {
                                        return false;
                        }
            }
            const js::any invalidAngle = this->isInvalidAngle(i1, i2, id);
            if (invalidAngle) {
                        {
                                        return false;
                        }
            }
            return true;
    }
}

auto ShellLineRaycaster::saveResult(js::number id) {
    {
            const js::any snappedEdgeP1 = this->_tempV1.clone();
            const js::any snappedEdgeP2 = this->_tempV2.clone();
            const js::any normal = this->_normals[id];
            const js::any point = this->_tempPoint.clone();
            this->_result.push([]() {
                  js::object obj_temp_0;
                  obj_temp_0.set("point", point);
                  obj_temp_0.set("normal", normal);
                  obj_temp_0.set("snappedEdgeP1", snappedEdgeP1);
                  obj_temp_0.set("snappedEdgeP2", snappedEdgeP2);
                  return js::any(obj_temp_0);
                }());
    }
}

auto ShellLineRaycaster::getSecondIndex(js::number id, js::number count) {
    {
            const js::any isLast = id === (count - js::number(1));
            const js::any profile = this->getTempProfile(this->_shell);
            if (isLast) {
                        {
                                        return profile["indices"](js::number(0));
                        }
            }
            return profile["indices"]((id + js::number(1)));
    }
}

auto ShellLineRaycaster::raycastSegment(js::any ray) {
    {
            ray["distanceSqToSegment"](this->_tempV1, this->_tempV2, js::undefined, this->_tempPoint);
    }
}

auto ShellLineRaycaster::getTempProfile(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return this->_bigShellProfile;
                        }
            }
            return this->_shellProfile;
    }
}
