#include "index_generated.h"
#include "fragments-connection.h"

using namespace js;

FragmentsConnection::FragmentsConnection(ThreadHandler handleInput, js::string threadPath) : Connection(handleInput) {
    {
            this->_data = std::make_shared<ThreadsData>(threadPath);
    }
}

auto FragmentsConnection::delete(js::string model) {
    {
            const js::any thread = this->_data.getThreadSafe(model);
            const js::number amount = (this->_data.getAmountSafe(thread) - js::number(1));
            this->_data.deleteModel(model);
            if (amount === js::number(0)) {
                        {
                                        this->_data.deleteThread(thread);
                        }
            }
    }
}

auto FragmentsConnection::invoke(js::string model, js::string method, js::array<js::any> args) {
    {
            const js::any helper = MultithreadingHelper;
            const js::any requestData = helper["getExecuteRequest"](model, method, args);
            const js::any response = co_await this->fetch(requestData);
            return response["result"];
    }
}

auto FragmentsConnection::fetchConnection(js::any input) {
    {
            const js::any thread = this->_data.getAndCheckThread(input["modelId"]);
            if (thread) {
                        {
                                        return this->_data.getPort(thread);
                        }
            }
            return this->setupNewThread(input);
    }
}

auto FragmentsConnection::setupNewThread(js::any input) {
    {
            const js::any helper = MultithreadingHelper;
            this->_data.usePlaceholder(input["modelId"]);
            const js::any currentThreads = this->_data.getThreadAmount();
            const js::any areCoresAvailable = helper["areCoresAvailable"](currentThreads);
            if (areCoresAvailable) {
                        {
                                        return this->newThread(input, this->_data.path);
                        }
            }
            return this->_data.balanceThreadLoad(input);
    }
}

auto FragmentsConnection::setupThread(Thread newThread) {
    {
            const std::shared_ptr<MessageChannel> threadChannel = std::make_shared<MessageChannel>();
            const js::any p1 = threadChannel->port1;
            const js::any p2 = threadChannel->port2;
            this->initConnection(p1);
            this->_data.setPort(newThread, p1);
            newThread->postMessage(p2, js::array<js::any>{p2});
    }
}

auto FragmentsConnection::newThread(js::any input, js::string url) {
    {
            const js::any newThread = MultithreadingHelper::newThread(url);
            this->setupThread(newThread);
            this->_data.setAmount(newThread, js::number(1));
            this->_data.set(input["modelId"], newThread);
            return this->_data.getPort(newThread);
    }
}
