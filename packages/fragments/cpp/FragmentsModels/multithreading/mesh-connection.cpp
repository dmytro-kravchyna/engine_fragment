#include "index_generated.h"
#include "mesh-connection.h"

using namespace js;

MeshConnection::MeshConnection(js::string modelId, Connection connection) {
    {
            this->_modelId = modelId;
            this->_connection = connection;
            this->_updater = MultithreadingHelper::newUpdater(this->refresh, this->_rate);
    }
}

void MeshConnection::dispose() {
    {
            MultithreadingHelper::deleteUpdater(this->_updater);
    }
}

auto MeshConnection::clean() {
    {
            this->_list = MultithreadingHelper::cleanRequests(this->_list);
    }
}

void MeshConnection::process(js::any request) {
    {
            this->_list.push(request);
            if (this->needsRefresh) {
                        {
                                        this->refresh();
                        }
            }
    }
}
