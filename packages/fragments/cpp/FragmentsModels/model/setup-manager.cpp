#include "index_generated.h"
#include "setup-manager.h"

using namespace js;

auto SetupManager::setup(FragmentsModel model, js::any bbox, ArrayBuffer modelData, std::optional<bool> raw, std::optional<VirtualModelConfig> config) {
    {
            const js::any message = this->getCreateModelMessage(model, modelData, raw, config);
            const js::any data = this->formatModelData(modelData);
            const js::any result = co_await model["threads"]["fetch"](message, data);
            this->updateBox(bbox, result);
    }
}

auto SetupManager::formatModelData(ArrayBuffer modelData) {
    {
            if (js::instanceof_op(modelData, "ArrayBuffer")) {
                        {
                                        return js::array<js::any>{modelData};
                        }
            }
            return js::undefined;
    }
}

auto SetupManager::updateBox(js::any bbox, js::any result) {
    {
            bbox["min"]["copy"](result->boundingBox.min);
            bbox["max"]["copy"](result->boundingBox.max);
    }
}

auto SetupManager::getCreateModelMessage(FragmentsModel model, ArrayBuffer modelData, js::typed::Nullable<bool> raw, js::typed::Nullable<VirtualModelConfig> config) {
    {
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("class", MultiThreadingRequestClass::CREATE_MODEL);
                  obj_temp_0.set("modelId", model["modelId"]);
                  obj_temp_0.set("modelData", modelData);
                  obj_temp_0.set("raw", raw);
                  obj_temp_0.set("config", config);
                  return js::any(obj_temp_0);
                }();
    }
}
