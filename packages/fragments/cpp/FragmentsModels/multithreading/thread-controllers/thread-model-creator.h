#ifndef THREAD_MODEL_CREATOR_H
#define THREAD_MODEL_CREATOR_H

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
#include <pako.h>
#include "../../model/model-types.h"
#include "./thread-controller.h"
#include "../../virtual-model.h"

using namespace js;

// Forward declarations
class ThreadModelCreator;

class ThreadModelCreator : public ThreadController {
public:
    ThreadModelCreator() = default;
protected:
    auto getId() override;
    auto execute(js::any input) override;
private:
    auto setupData(js::any input, VirtualFragmentsModel model) override;
    auto createModel(js::any input) override;
    auto inflate(js::any input) override;
};

#endif // THREAD_MODEL_CREATOR_H