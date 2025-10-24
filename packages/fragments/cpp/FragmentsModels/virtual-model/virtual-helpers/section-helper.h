#ifndef SECTION_HELPER_H
#define SECTION_HELPER_H

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
#include "../virtual-fragments-model.h"
#include "../../model/model-types.h"
#include "../../utils.h"

using namespace js;

// Forward declarations
class SectionHelper;

class SectionHelper {
public:
    SectionHelper() = default;
    virtual auto getSection(VirtualFragmentsModel model, js::any plane, js::array<js::number> indices);
private:
    auto _sectionGenerator;
};

#endif // SECTION_HELPER_H