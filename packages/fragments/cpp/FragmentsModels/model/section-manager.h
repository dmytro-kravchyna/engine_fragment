#ifndef SECTION_MANAGER_H
#define SECTION_MANAGER_H

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
#include "./fragments-model.h"
#include "./model-types.h"

using namespace js;

// Forward declarations
class SectionManager;

class SectionManager {
public:
    SectionManager() = default;
    virtual auto getSection(FragmentsModel model, js::any plane, std::optional<js::array<js::number>> localIds = std::nullopt);
};

#endif // SECTION_MANAGER_H