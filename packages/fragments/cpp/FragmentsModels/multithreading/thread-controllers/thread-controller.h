#ifndef THREAD_CONTROLLER_H
#define THREAD_CONTROLLER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../fragments-thread.h"

using namespace js;

// Forward declarations
class ThreadController;

class ThreadController {
public:
    ThreadController(FragmentsThread thread);
protected:
    std::shared_ptr<FragmentsThread> thread;
    virtual js::number getId() = 0;
    virtual std::future<void> execute(js::any input) = 0;
private:
    js::number id;
};

#endif // THREAD_CONTROLLER_H