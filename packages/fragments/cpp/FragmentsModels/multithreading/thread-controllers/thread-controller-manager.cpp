#include "index_generated.h"
#include "thread-controller-manager.h"

using namespace js;

ThreadControllerManager::ThreadControllerManager(FragmentsThread thread) {
    {
            this->thread = thread;
            this->modelCreator = std::make_shared<ThreadModelCreator>(thread);
            this->raycaster = std::make_shared<ThreadRaycaster>(thread);
            this->modelDeleter = std::make_shared<ThreadModelDeleter>(thread);
            this->viewRefresher = std::make_shared<ThreadViewRefresher>(thread);
            this->boxFetcher = std::make_shared<ThreadBoxFetcher>(thread);
            this->executor = std::make_shared<ThreadExecutor>(thread);
            this->updater = std::make_shared<ThreadUpdater>(thread);
    }
}
