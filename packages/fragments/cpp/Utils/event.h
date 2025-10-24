#ifndef EVENT_H
#define EVENT_H

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
class Event;

template<typename T>
class Event {
public:
    Event() = default;
    auto enabled;
    virtual void add(js::any handler);
    virtual void remove(js::any handler);
    auto trigger;
    virtual auto reset();
private:
    js::array<js::any> handlers;
};

#endif // EVENT_H