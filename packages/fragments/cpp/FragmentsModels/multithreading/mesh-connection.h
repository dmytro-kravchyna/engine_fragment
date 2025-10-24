#ifndef MESH_CONNECTION_H
#define MESH_CONNECTION_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "./connection.h"
#include "./multithreading-helper.h"

using namespace js;

// Forward declarations
class MeshConnection;

class MeshConnection {
public:
    MeshConnection(js::string modelId, Connection connection);
    virtual void dispose();
    virtual auto clean();
    virtual void process(js::any request);
private:
    auto _rate;
    js::any _updater;
    js::string _modelId;
    auto _threshold;
    std::shared_ptr<Connection> _connection;
    js::array<js::any> _list;
    auto refresh;
};

#endif // MESH_CONNECTION_H