#include "index_generated.h"
#include "section-manager.h"

using namespace js;

auto SectionManager::getSection(FragmentsModel model, js::any plane, std::optional<js::array<js::number>> localIds) {
    {
            js::array<js::any> args = js::array<js::any>{plane, localIds};
            const js::any result = co_await model["threads"]["invoke"](model["modelId"], "getSection"_S, args);
            return result;
    }
}
