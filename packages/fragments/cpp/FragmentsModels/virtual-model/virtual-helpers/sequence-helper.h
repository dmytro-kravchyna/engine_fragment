#ifndef SEQUENCE_HELPER_H
#define SEQUENCE_HELPER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../../model/model-types.h"
#include "../virtual-fragments-model.h"

using namespace js;

// Forward declarations
class SequenceHelper;

class SequenceHelper {
public:
    SequenceHelper(VirtualFragmentsModel model);
    virtual auto getSequenced(ItemInformationType result, js::array<ItemSelectionType> fromItems, std::optional<js::any> inputs = std::nullopt);
private:
    std::shared_ptr<VirtualFragmentsModel> _model;
    std::shared_ptr<Record> sequenceSelectorFunction;
    std::shared_ptr<Record> sequenceResultFunction;
};

#endif // SEQUENCE_HELPER_H