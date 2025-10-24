#ifndef THREAD_MODEL_DELETER_H
#define THREAD_MODEL_DELETER_H

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
#include "../../model/model-types.h"
#include "./thread-controller.h"

using namespace js;

// Forward declarations
class ThreadModelDeleter;

class ThreadModelDeleter : public ThreadController {
public:
    ThreadModelDeleter() = default;
protected:
    auto getId() override;
    auto execute(js::any input) override;
};

#endif // THREAD_MODEL_DELETER_H