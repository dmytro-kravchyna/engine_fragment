#ifndef CONNECTION_H
#define CONNECTION_H

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
#include "./connection-handlers.h"
#include "./multithreading-helper.h"

using namespace js;

// Forward declarations
class Connection;

class Connection {
public:
    Connection(ThreadHandler handleInput);
    virtual auto fetchMeshCompute(js::string modelId, js::array<js::any> list);
    virtual auto fetch(js::any input, std::optional<js::array<js::any>> content = std::nullopt);
    virtual auto init(MessagePort port);
protected:
    virtual auto initConnection(MessagePort connection);
    virtual auto fetchConnection(js::any _input);
private:
    auto _handlers;
    std::shared_ptr<ThreadHandler> _handleInput;
    std::shared_ptr<MessagePort> _port;
    virtual auto executeConnection(js::any input, std::optional<js::array<js::any>> content = std::nullopt);
    virtual auto manageOutput(js::any input);
    auto onInput;
    virtual auto manageConnection(js::any input);
    virtual std::future<void> manageInput(js::any input);
};

#endif // CONNECTION_H