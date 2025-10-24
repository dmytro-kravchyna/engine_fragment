#include "index_generated.h"
#include "connection-handlers.h"

using namespace js;

auto ConnectionHandlers::setupInput(js::any input) {
    {
            input["requestId"] = this->_communicationKey++;
    }
}

auto ConnectionHandlers::set(js::number id, js::any reject, js::any resolve) {
    {
            const js::any handler = this->newHandler(reject, resolve);
            this->_list.set(id, handler);
    }
}

auto ConnectionHandlers::run(js::any data) {
    {
            const js::any handler = this->_list.get(data->requestId);
            this->_list.delete(data->requestId);
            handler(data);
    }
}

auto ConnectionHandlers::newHandler(js::any reject, js::any resolve) {
    {
            return [&](js::any response) -> auto {
            if (response["errorInfo"]) {
                        {
                                        reject(response["errorInfo"]);
                                        return;
                        }
            }
            resolve(response);
            };
    }
}
