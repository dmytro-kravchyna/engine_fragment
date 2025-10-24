#ifndef FRAGMENTS_THREAD_H
#define FRAGMENTS_THREAD_H

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
#include "../virtual-model.h"
#include "./connection.h"
#include "./thread-controllers/thread-controller-manager.h"

using namespace js;

// Forward declarations
class FragmentsThread;

class FragmentsThread {
public:
    FragmentsThread() = default;
    js::any actions;
    auto list;
    auto controllerManager;
    virtual auto useConnection(MessagePort connection);
    virtual auto getModel(js::string id);
private:
    std::shared_ptr<Connection> _connection;
};
extern const std::shared_ptr<FragmentsThread> thread;

#endif // FRAGMENTS_THREAD_H