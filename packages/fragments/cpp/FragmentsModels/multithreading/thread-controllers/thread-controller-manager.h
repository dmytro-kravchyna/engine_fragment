#ifndef THREAD_CONTROLLER_MANAGER_H
#define THREAD_CONTROLLER_MANAGER_H

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
#include "./thread-model-creator.h"
#include "./thread-raycaster.h"
#include "./thread-model-deleter.h"
#include "./thread-view-refresher.h"
#include "./thread-box-fetcher.h"
#include "./thread-executor.h"
#include "./thread-updater.h"

using namespace js;

// Forward declarations
class ThreadControllerManager;

class ThreadControllerManager {
public:
    std::shared_ptr<FragmentsThread> thread;
    std::shared_ptr<ThreadModelCreator> modelCreator;
    std::shared_ptr<ThreadRaycaster> raycaster;
    std::shared_ptr<ThreadModelDeleter> modelDeleter;
    std::shared_ptr<ThreadViewRefresher> viewRefresher;
    std::shared_ptr<ThreadBoxFetcher> boxFetcher;
    std::shared_ptr<ThreadExecutor> executor;
    std::shared_ptr<ThreadUpdater> updater;
    ThreadControllerManager(FragmentsThread thread);
};

#endif // THREAD_CONTROLLER_MANAGER_H