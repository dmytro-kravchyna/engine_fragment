#include "index_generated.h"
#include "sequence-helper.h"

using namespace js;

SequenceHelper::SequenceHelper(VirtualFragmentsModel model) {
    {
            this->_model = model;
    }
}

auto SequenceHelper::getSequenced(ItemInformationType result, js::array<ItemSelectionType> fromItems, std::optional<js::any> inputs) {
    {
            const js::any resultFunction = this->sequenceResultFunction[result];
            if (!resultFunction) {
                        return js::null;
            }
            js::array<js::number> partial = js::array<js::any>{};
            js::number iterations = js::number(0);
            for (const auto& action : fromItems) {
                        {
                                        const js::any selectorFunction = this->sequenceSelectorFunction[action];
                                        if (!selectorFunction) {
                                                            continue;
                                        }
                                        const js::any input = inputs["selector"][action];
                                        const js::any data = (js::null ? js::null : js::null);
                                        partial = selectorFunction(data);
                                        iterations++;
                        }
            }
            const js::any input = inputs["result"];
            const js::any out = resultFunction(partial, input);
            return out;
    }
}
