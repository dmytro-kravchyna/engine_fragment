#include "index_generated.h"
#include "shell-point-raycaster.h"

using namespace js;

ShellPointRaycaster::ShellPointRaycaster(Meshes _meshes) {
    {
            this->_meshes = _meshes;
    }
}

auto ShellPointRaycaster::pointRaycast(js::number id, js::any frustum) {
    {
            const js::any shell = ShellUtils::getShell(this->_meshes, id);
            js::array<js::any> points = js::array<js::any>{};
            this->cast(shell, frustum, points);
            return points;
    }
}

auto ShellPointRaycaster::cast(Shell shell, js::any frustum, js::array<js::any> points) {
    {
            const js::any count = shell["pointsLength"]();
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        ShellUtils::point(shell, id, this->_tempVec);
                                        const js::any pointFound = frustum["containsPoint"](this->_tempVec);
                                        if (!pointFound) {
                                                            continue;
                                        }
                                        const js::any point = this->_tempVec.clone();
                                        points.push([]() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("point", point);
                                              return js::any(obj_temp_0);
                                            }());
                        }
            }
    }
}
