#ifndef ASYNC_EVENT_H
#define ASYNC_EVENT_H

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

using namespace js;

// Forward declarations
class AsyncEvent;

template<typename T>
class AsyncEvent {
public:
    AsyncEvent() = default;
    auto enabled;
    virtual void add(js::any handler);
    virtual void remove(js::any handler);
    auto trigger;
    virtual auto reset();
private:
    js::array<js::any> handlers;
};

#endif // ASYNC_EVENT_H