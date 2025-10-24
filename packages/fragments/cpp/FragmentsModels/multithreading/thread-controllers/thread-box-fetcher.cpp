#include "index_generated.h"
#include "thread-box-fetcher.h"

using namespace js;

auto ThreadBoxFetcher::getId() {
    {
            return MultiThreadingRequestClass::FETCH_BOXES;
    }
}

auto ThreadBoxFetcher::execute(js::any input) {
    {
            input["boxes"] = js::array<js::any>{};
            if (input["localIds"]) {
                        {
                                        this->getBoxesFromLocalIds(input);
                                        return;
                        }
            }
            this->getAllBoxes(input);
    }
}

auto ThreadBoxFetcher::getBoxesFromLocalIds(js::any input) {
    {
            const js::any model = this->thread.getModel(input["modelId"]);
            for (const auto& localIds : input["localIds"]) {
                        {
                                        const js::any itemIds = model["getItemIdsByLocalIds"](localIds);
                                        const js::any box = model["getBBoxes"](itemIds);
                                        input["boxes"].push(box);
                        }
            }
            input["localIds"] = js::undefined;
    }
}

auto ThreadBoxFetcher::getAllBoxes(js::any input) {
    {
            const js::any model = this->thread.getModel(input["modelId"]);
            const js::any size = model["getGeometriesLength"]();
            for (js::number i = js::number(0); (i < size); i++) {
                        {
                                        const js::any box = model["getBBoxes"](js::array<js::any>{i});
                                        input["boxes"].push(box);
                        }
            }
            input["localIds"] = js::undefined;
    }
}
