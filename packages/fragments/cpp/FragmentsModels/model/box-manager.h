#ifndef BOX_MANAGER_H
#define BOX_MANAGER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "runtime/async.h"
#include <three.h>
#include "./model-types.h"
#include "./fragments-model.h"

using namespace js;

// Forward declarations
class BoxManager;

class BoxManager {
public:
    BoxManager() = default;
    virtual auto getBoxes(FragmentsModel model, std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto getMergedBox(FragmentsModel model, js::array<js::number> localIds);
private:
    virtual auto getAbsoluteBox(js::any box, FragmentsModel model);
    virtual auto getIndividualBoxesIds(js::typed::Nullable<js::array<js::number>> localIds);
    virtual auto getAllBoxes(js::any response, FragmentsModel model);
    virtual auto getBoxRequest(FragmentsModel model, js::typed::Nullable<js::array<js::array<js::number>>> localIds);
};

#endif // BOX_MANAGER_H