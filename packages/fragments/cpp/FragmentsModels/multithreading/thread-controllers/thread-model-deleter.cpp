#include "index_generated.h"
#include "thread-model-deleter.h"

using namespace js;

auto ThreadModelDeleter::getId() {
    {
            return MultiThreadingRequestClass::DELETE_MODEL;
    }
}

auto ThreadModelDeleter::execute(js::any input) {
    {
            auto _temp7415 = input;
            const auto modelId = _temp7415["modelId"];
            const js::any model = this->thread.getModel(modelId);
            model["dispose"]();
            this->thread.list.delete(modelId);
    }
}
