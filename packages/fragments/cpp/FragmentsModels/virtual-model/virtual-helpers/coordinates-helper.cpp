#include "index_generated.h"
#include "coordinates-helper.h"

using namespace js;

auto CoordinatesHelper::getPositions(VirtualFragmentsModel model, js::array<js::number> localIds) {
    {
            js::array<js::any> positions = js::array<js::any>{};
            const js::any itemIds = model["properties"]["getItemIdsFromLocalIds"](localIds);
            for (const auto& id : itemIds) {
                        {
                                        const js::any transform = model["tiles"]["meshes"]["globalTransforms"](id);
                                        if (!transform) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        const js::any position = transform["position"]();
                                        const js::any x = position["x"]();
                                        const js::any y = position["y"]();
                                        const js::any z = position["z"]();
                                        positions.push([]() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("x", x);
                                              obj_temp_0.set("y", y);
                                              obj_temp_0.set("z", z);
                                              return js::any(obj_temp_0);
                                            }());
                        }
            }
            return positions;
    }
}

js::array<js::number> CoordinatesHelper::getCoordinates(VirtualFragmentsModel model) {
    {
            const js::any meshes = model["data"]["meshes"]();
            const js::any coords = meshes["coordinates"]();
            const js::any position = coords["position"]();
            const js::any xDir = coords["xDirection"]();
            const js::any yDir = coords["yDirection"]();
            const js::any x = position["x"]();
            const js::any y = position["y"]();
            const js::any z = position["z"]();
            const js::any xx = xDir->x();
            const js::any xy = xDir->y();
            const js::any xz = xDir->z();
            const js::any yx = yDir->x();
            const js::any yy = yDir->y();
            const js::any yz = yDir->z();
            return js::array<js::any>{x, y, z, xx, xy, xz, yx, yy, yz};
    }
}
