#ifndef THREAD_EXECUTOR_H
#define THREAD_EXECUTOR_H

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
#include "../multithreading-helper.h"
#include "./thread-controller.h"

using namespace js;

// Forward declarations
class ThreadExecutor;

class ThreadExecutor : public ThreadController {
public:
    ThreadExecutor() = default;
protected:
    auto getId() override;
    auto execute(js::any input) override;
private:
    auto safeCopyData(js::any input) override;
};

#endif // THREAD_EXECUTOR_H