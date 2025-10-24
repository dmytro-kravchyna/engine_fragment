#include "index_generated.h"
#include "shell-template-constructor.h"

using namespace js;

auto ShellTemplateConstructor::newMeshTemplate(Shell shell) {
    {
            const js::any isEmpty = this->getIsEmpty(shell);
            if (isEmpty) {
                        {
                                        return []() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("objectClass", ObjectClass::SHELL);
                                              return js::any(obj_temp_0);
                                            }();
                        }
            }
            this->reset(true);
            this->processShell(shell);
            return this->getResult();
    }
}

auto ShellTemplateConstructor::manageDataLeft() {
    {
            const js::any isDataLeft = this->getIsDataLeft();
            if (isDataLeft) {
                        {
                                        this->setMesh();
                        }
            }
    }
}

auto ShellTemplateConstructor::getIsEmpty(Shell shell) {
    {
            const js::any length = ShellUtils::getProfilesLength(shell);
            return length === js::number(0);
    }
}

auto ShellTemplateConstructor::processShellHoles(Shell shell, js::number id) {
    {
            bool shellHolesExist = false;
            const js::any count = ShellUtils::getHolesLength(shell);
            const js::any hole = this->getTempHole(shell);
            for (js::number i = js::number(0); (i < count); i++) {
                        {
                                        ShellUtils::getHole(shell, i, hole);
                                        const js::any profileId = hole["profileId"]();
                                        if (profileId !== id) {
                                                            continue;
                                        }
                                        this->updateBuffers(shell, shellHolesExist);
                                        shellHolesExist = true;
                        }
            }
            this->manageFoundHoles(shell, shellHolesExist);
    }
}

auto ShellTemplateConstructor::newMesh() {
    {
            return []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("objectClass", ObjectClass::SHELL);
                  obj_temp_1.set("indexCount", (this->triangleAmount * js::number(3)));
                  obj_temp_1.set("positionCount", ((this->holePoints + this->profilePoints) * js::number(3)));
                  obj_temp_1.set("normalCount", ((this->holePoints + this->profilePoints) * js::number(3)));
                  return js::any(obj_temp_1);
                }();
    }
}

auto ShellTemplateConstructor::reset(bool evenMeshes) {
    {
            this->holePoints = js::number(0);
            this->profilePoints = js::number(0);
            this->triangleAmount = js::number(0);
            if (evenMeshes) {
                        {
                                        this->meshes = js::undefined;
                        }
            }
    }
}

auto ShellTemplateConstructor::getIsDataLeft() {
    {
            const bool areTriangles = (this->triangleAmount > js::number(0));
            const bool areHoles = (this->holePoints > js::number(0));
            const bool areProfiles = (this->profilePoints > js::number(0));
            return ((areTriangles || areHoles) || areProfiles);
    }
}

auto ShellTemplateConstructor::processShell(Shell shell) {
    {
            const js::any count = ShellUtils::getProfilesLength(shell);
            const js::any profile = this->getTempProfile(shell);
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        ShellUtils::getProfile(shell, id, profile);
                                        this->indexCount = profile["indicesLength"]();
                                        this->profilePoints += this->indexCount;
                                        this->processShellHoles(shell, id);
                                        this->manageMemory();
                        }
            }
            this->manageDataLeft();
    }
}

auto ShellTemplateConstructor::manageFoundHoles(Shell shell, bool shellHolesExist) {
    {
            const js::any profile = this->getTempProfile(shell);
            const js::any indicesAmount = profile["indicesLength"]();
            if (shellHolesExist) {
                        {
                                        this->triangleAmount += indicesAmount;
                                        return;
                        }
            }
            if ((indicesAmount > js::number(2))) {
                        {
                                        this->triangleAmount += (indicesAmount - js::number(2));
                        }
            }
    }
}

auto ShellTemplateConstructor::getResult() {
    {
            const js::any meshes = this->meshes;
            this->meshes = js::undefined;
            return meshes;
    }
}

auto ShellTemplateConstructor::manageMemory() {
    {
            const js::number memory = ((this->holePoints + this->profilePoints) + this->indexCount);
            const bool memoryOverflow = (memory > limitOf2Bytes);
            if (memoryOverflow) {
                        {
                                        this->setMesh();
                        }
            }
    }
}

auto ShellTemplateConstructor::updateBuffers(Shell shell, bool shellHolesExist) {
    {
            const js::any hole = this->getTempHole(shell);
            this->holePoints += hole["indicesLength"]();
            this->triangleAmount += hole["indicesLength"]();
            if (shellHolesExist) {
                        {
                                        this->triangleAmount += js::number(2);
                        }
            }
    }
}

auto ShellTemplateConstructor::setMesh() {
    {
            const js::any mesh = this->newMesh();
            if (!this->meshes) {
                        {
                                        this->meshes = mesh;
                        }
            } else {
                        if (js::array.isArray(this->meshes)) {
                                        {
                                                            this->meshes.push(mesh);
                                        }
                        } else {
                                        {
                                                            this->meshes = js::array<js::any>{this->meshes, mesh};
                                        }
                        }
            }
            this->reset(false);
    }
}

auto ShellTemplateConstructor::getTempProfile(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return this->_bigShellProfile;
                        }
            }
            return this->_shellProfile;
    }
}

auto ShellTemplateConstructor::getTempHole(Shell shell) {
    {
            if (shell["type"]() === ShellType::BIG) {
                        {
                                        return this->_bigShellHole;
                        }
            }
            return this->_shellHole;
    }
}
