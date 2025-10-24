#include "index_generated.h"
#include "thread-executor.h"

using namespace js;

auto ThreadExecutor::getId() {
    {
            return MultiThreadingRequestClass::EXECUTE;
    }
}

auto ThreadExecutor::execute(js::any input) {
    {
            const js::any model = this->thread.getModel(input["modelId"]);
            this->safeCopyData(input);
            input["result"] = co_await model[input["function"]](/* spread input["parameters"] */);
            input["parameters"] = js::undefined;
    }
}

auto ThreadExecutor::safeCopyData(js::any input) {
    {
            for (js::number i = js::number(0); (i < input["parameters"].length()); i++) {
                        {
                                        const js::any data = input["parameters"][i];
                                        if (!data) {
                                                            continue;
                                        }
                                        input["parameters"][i] = MultithreadingHelper::data(data);
                        }
            }
    }
}
