#ifndef THREAD_UPDATER_H
#define THREAD_UPDATER_H

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
class ThreadUpdater;

class ThreadUpdater {
public:
    ThreadUpdater(FragmentsThread thread);
private:
    std::shared_ptr<FragmentsThread> _thread;
    auto _updateThreshold;
    auto _updateDelay;
    virtual auto updateAllModels();
};

#endif // THREAD_UPDATER_H