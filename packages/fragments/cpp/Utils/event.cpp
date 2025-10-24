#include "index_generated.h"
#include "event.h"

using namespace js;

void Event::add(js::any handler) {
    {
            this->handlers.push(handler);
    }
}

void Event::remove(js::any handler) {
    {
            this->handlers = this->handlers.filter([&](auto h) -> auto { return h !== handler; });
    }
}

auto Event::reset() {
    {
            this->handlers.length() = js::number(0);
    }
}
