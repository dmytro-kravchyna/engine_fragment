#ifndef THREADS_DATA_H
#define THREADS_DATA_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "./multithreading-helper.h"

using namespace js;

// Forward declarations
class ThreadsData;

class ThreadsData {
public:
    ThreadsData(js::string threadPath);
    virtual auto usePlaceholder(js::string id);
    virtual auto getAmount(Thread thread);
    virtual auto getThread(js::string modelId);
    virtual auto getAndCheckThread(js::string id);
    virtual auto set(js::string modelId, Thread thread);
    virtual auto deleteModel(js::string modelId);
    virtual auto getThreadSafe(js::string modelId);
    virtual auto deleteThread(Thread thread);
    virtual auto getThreadAmount();
    virtual auto balanceThreadLoad(js::any input);
    virtual auto getAmountSafe(Thread thread);
    virtual auto setPort(Thread thread, MessagePort port);
    virtual auto setAmount(Thread thread, js::number amount);
    virtual auto getPort(Thread thread);
private:
    auto _modelThread;
    auto _threadsModelAmount;
    auto _threadPort;
    js::string _threadPath;
    std::shared_ptr<Thread> _placeholder;
    virtual auto getLessBusyThread();
};

#endif // THREADS_DATA_H