#include "index_generated.h"
#include "thread-model-creator.h"

using namespace js;

auto ThreadModelCreator::getId() {
    {
            return MultiThreadingRequestClass::CREATE_MODEL;
    }
}

auto ThreadModelCreator::execute(js::any input) {
    {
            this->inflate(input);
            const js::any model = this->createModel(input);
            this->setupData(input, model);
    }
}

auto ThreadModelCreator::setupData(js::any input, VirtualFragmentsModel model) {
    {
            input["boundingBox"] = model["getFullBBox"]();
            input["modelData"] = js::undefined;
    }
}

auto ThreadModelCreator::createModel(js::any input) {
    {
            auto _temp8149 = input;
            const auto modelId = _temp8149["modelId"];
            const auto modelData = _temp8149["modelData"];
            const auto config = _temp8149["config"];
            auto _temp5926 = this->thread;
            const auto connection = _temp5926["connection"];
            const std::shared_ptr<VirtualFragmentsModel> model = std::make_shared<VirtualFragmentsModel>(modelId, modelData, connection, config);
            model["setupData"]();
            this->thread.list.set(modelId, model);
            return model;
    }
}

auto ThreadModelCreator::inflate(js::any input) {
    {
            if (!input["raw"]) {
                        {
                                        input["modelData"] = Pako::inflate(input["modelData"]);
                        }
            }
    }
}
