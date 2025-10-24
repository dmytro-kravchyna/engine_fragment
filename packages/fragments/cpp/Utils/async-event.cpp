#include "index_generated.h"
#include "async-event.h"

using namespace js;

void AsyncEvent::add(js::any handler) {
    {
            this->handlers.push(handler);
    }
}

void AsyncEvent::remove(js::any handler) {
    {
            this->handlers = this->handlers.filter([&](auto h) -> auto { return h !== handler; });
    }
}

auto AsyncEvent::reset() {
    {
            this->handlers.length() = js::number(0);
    }
}
