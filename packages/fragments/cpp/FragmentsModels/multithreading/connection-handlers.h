#ifndef CONNECTION_HANDLERS_H
#define CONNECTION_HANDLERS_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"

using namespace js;

// Forward declarations
class ConnectionHandlers;

class ConnectionHandlers {
public:
    ConnectionHandlers() = default;
    virtual auto setupInput(js::any input);
    virtual auto set(js::number id, js::any reject, js::any resolve);
    virtual auto run(js::any data);
private:
    auto _list;
    auto _communicationKey;
    virtual auto newHandler(js::any reject, js::any resolve);
};

#endif // CONNECTION_HANDLERS_H