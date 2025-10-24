#include "index_generated.h"
#include "coordinates-manager.h"

using namespace js;

auto CoordinatesManager::getCoordinationMatrix(FragmentsModel model) {
    {
            js::any matrix = this->_coordinationMatrices.get(model["modelId"]);
            if (matrix) {
                        {
                                        return matrix;
                        }
            }
            matrix = std::make_shared<three::Matrix4>();
            this->_coordinationMatrices.set(model["modelId"], matrix);
            auto _temp2160 = co_await this->getCoordinates(model);
            const auto x = _temp2160[0];
            const auto y = _temp2160[1];
            const auto z = _temp2160[2];
            const auto xx = _temp2160[3];
            const auto xy = _temp2160[4];
            const auto xz = _temp2160[5];
            const auto yx = _temp2160[6];
            const auto yy = _temp2160[7];
            const auto yz = _temp2160[8];
            const std::shared_ptr<three::Vector3> xDir = std::make_shared<three::Vector3>(xx, xy, xz);
            const std::shared_ptr<three::Vector3> yDir = std::make_shared<three::Vector3>(yx, yy, yz);
            const js::any zDir = std::make_shared<three::Vector3>().crossVectors(xDir, yDir);
            matrix["set"](xx, yx, zDir->x, x, xy, yy, zDir->y, y, xz, yz, zDir->z, z, js::number(0), js::number(0), js::number(0), js::number(1));
            return matrix;
    }
}

auto CoordinatesManager::getCoordinates(FragmentsModel model) {
    {
            const js::any id = model["modelId"];
            return model["threads"]["invoke"](id, "getCoordinates"_S);
    }
}

auto CoordinatesManager::getPositions(FragmentsModel model, std::optional<js::array<js::number>> localIds) {
    {
            js::array<js::any> args = js::array<js::any>{localIds};
            const js::any localPositions = co_await model["threads"]["invoke"](model["modelId"], "getPositions"_S, args);
            return this->getAbsolutePositions(localPositions, model);
    }
}

auto CoordinatesManager::getAbsolutePositions(js::array<js::any> result, FragmentsModel model) {
    {
            js::array<unknown> positions = js::array<js::any>{};
            for (const auto& position : result) {
                        {
                                        auto _temp931 = position;
                                        const auto x = _temp931["x"];
                                        const auto y = _temp931["y"];
                                        const auto z = _temp931["z"];
                                        const std::shared_ptr<three::Vector3> vector = std::make_shared<three::Vector3>(x, y, z);
                                        vector["applyMatrix4"](model["object"]["matrixWorld"]);
                                        positions.push(vector);
                        }
            }
            return positions;
    }
}
