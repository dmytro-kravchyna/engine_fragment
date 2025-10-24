#include "index_generated.h"
#include "connection.h"

using namespace js;

Connection::Connection(ThreadHandler handleInput) {
    {
            this->_handleInput = handleInput;
    }
}

auto Connection::fetchMeshCompute(js::string modelId, js::array<js::any> list) {
    {
            const js::any helper = MultithreadingHelper;
            const js::any input = helper["getMeshComputeRequest"](modelId, list);
            const js::any content = helper["getRequestContent"](input);
            this->fetch(input, content);
    }
}

auto Connection::fetch(js::any input, std::optional<js::array<js::any>> content) {
    {
            this->_handlers.setupInput(input);
            return std::make_shared<Promise>([&](auto resolve, auto reject) -> auto {
            this->_handlers.set(input["requestId"], reject, resolve);
            this->executeConnection(input, content);
            });
    }
}

auto Connection::init(MessagePort port) {
    {
            this->_port = port;
            this->initConnection(port);
    }
}

auto Connection::initConnection(MessagePort connection) {
    {
            connection->onmessage = this->onInput;
    }
}

auto Connection::fetchConnection(js::any _input) {
    {
            if (!this->_port) {
                        {
                                        throw js::any(js::Error("Fragments: Connection not initialized"_S));
                        }
            }
            return this->_port;
    }
}

auto Connection::executeConnection(js::any input, std::optional<js::array<js::any>> content) {
    {
            const js::any connectionPort = co_await this->fetchConnection(input);
            connectionPort->postMessage(input, content);
    }
}

auto Connection::manageOutput(js::any input) {
    {
            const js::any connection = co_await this->fetchConnection(input);
            input["toMainThread"] = true;
            connection->postMessage(input);
    }
}

auto Connection::manageConnection(js::any input) {
    {
            try {
                        co_await this->_handleInput(input);
            } catch (const js::any& error) {
                        input["errorInfo"] = error.toString();
                        js::console.error(error);
            }
    }
}

std::future<void> Connection::manageInput(js::any input) {
    {
            co_await this->manageConnection(input);
            co_await this->manageOutput(input);
    }
}
