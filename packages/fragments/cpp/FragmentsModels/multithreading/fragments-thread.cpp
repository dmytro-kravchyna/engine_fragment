#include "index_generated.h"
#include "fragments-thread.h"

using namespace js;

auto FragmentsThread::useConnection(MessagePort connection) {
    {
            const js::any handler = [&](js::any input) -> auto {
            co_await this->actions[input["class"]](input);
            };
            this->connection = std::make_shared<Connection>(handler);
            this->connection.init(connection);
    }
}

auto FragmentsThread::getModel(js::string id) {
    {
            const js::any model = this->list.get(id);
            if (!model) {
                        {
                                        throw js::any(js::Error(("Fragments: Model not found: "_S + js::toString(id))));
                        }
            }
            return model;
    }
}

const std::shared_ptr<FragmentsThread> thread = std::make_shared<FragmentsThread>();

// Entry point
void Main() {
    globalThis->onmessage = [](MessageEvent input) -> auto {
thread["useConnection"](input["data"]);
};
}

int main(int /*argc*/, char** /*argv*/) {
    Main();
    return 0;
}