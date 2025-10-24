#include "index_generated.h"
#include "box-manager.h"

using namespace js;

auto BoxManager::getBoxes(FragmentsModel model, std::optional<js::array<js::number>> localIds) {
    {
            const js::any ids = this->getIndividualBoxesIds(localIds);
            const js::any request = this->getBoxRequest(model, ids);
            const js::any response = co_await model["threads"]["fetch"](request);
            return this->getAllBoxes(response, model);
    }
}

auto BoxManager::getMergedBox(FragmentsModel model, js::array<js::number> localIds) {
    {
            const js::any request = this->getBoxRequest(model, js::array<js::any>{localIds});
            auto _temp7458 = co_await model["threads"]["fetch"](request);
            const auto boxes = _temp7458["boxes"];
            auto _temp563 = boxes;
            const auto box = _temp563[0];
            return this->getAbsoluteBox(box, model);
    }
}

auto BoxManager::getAbsoluteBox(js::any box, FragmentsModel model) {
    {
            const std::shared_ptr<three::Box3> merged = std::make_shared<three::Box3>();
            merged["copy"](box);
            merged["applyMatrix4"](model["object"]["matrixWorld"]);
            return merged;
    }
}

auto BoxManager::getIndividualBoxesIds(js::typed::Nullable<js::array<js::number>> localIds) {
    {
            if (!localIds) {
                        return js::undefined;
            }
            js::array<js::array<js::number>> ids = js::array<js::any>{};
            for (const auto& id : localIds) {
                        {
                                        ids.push(js::array<js::any>{id});
                        }
            }
            return ids;
    }
}

auto BoxManager::getAllBoxes(js::any response, FragmentsModel model) {
    {
            const js::any rawBoxes = response["boxes"];
            js::array<unknown> result = js::array<js::any>{};
            for (const auto& box : rawBoxes) {
                        {
                                        const std::shared_ptr<three::Box3> newBox = std::make_shared<three::Box3>();
                                        newBox->copy(box);
                                        newBox->applyMatrix4(model["object"]["matrixWorld"]);
                                        result.push(newBox);
                        }
            }
            return result;
    }
}

auto BoxManager::getBoxRequest(FragmentsModel model, js::typed::Nullable<js::array<js::array<js::number>>> localIds) {
    {
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("class", MultiThreadingRequestClass::FETCH_BOXES);
                  obj_temp_0.set("modelId", model["modelId"]);
                  obj_temp_0.set("localIds", localIds);
                  return js::any(obj_temp_0);
                }();
    }
}
