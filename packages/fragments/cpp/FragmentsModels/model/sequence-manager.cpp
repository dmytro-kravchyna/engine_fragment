#include "index_generated.h"
#include "sequence-manager.h"

using namespace js;

auto SequenceManager::getSequenced(FragmentsModel model, T result, js::array<U> fromItems, std::optional<js::any> inputs) {
    {
            js::array<js::any> args = js::array<js::any>{result, fromItems, inputs};
            const js::any response = co_await model["threads"]["invoke"](model["modelId"], "getSequenced"_S, args);
            return response;
    }
}
