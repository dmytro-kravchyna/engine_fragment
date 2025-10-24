#ifndef ALIGNMENTS_CONTROLLER_H
#define ALIGNMENTS_CONTROLLER_H

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
#include "../../../../Schema.h"
#include "../../model/model-types.h"

using namespace js;

// Forward declarations
class AlignmentsController;

class AlignmentsController {
public:
    AlignmentsController(Model model);
    virtual auto getAlignments();
private:
    std::shared_ptr<Model> _model;
    virtual auto constructAlignment(Alignment alignment, AlignmentData current, js::any type);
};

#endif // ALIGNMENTS_CONTROLLER_H