#ifndef FRAGMENTS_CONNECTION_H
#define FRAGMENTS_CONNECTION_H

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
#include "./connection.h"
#include "./connection-handlers.h"
#include "./multithreading-helper.h"
#include "./threads-data.h"

using namespace js;

// Forward declarations
class FragmentsConnection;

class FragmentsConnection : public Connection {
public:
    FragmentsConnection(ThreadHandler handleInput, js::string threadPath);
    auto delete(js::string model) override;
    auto invoke(js::string model, js::string method, js::array<js::any> args = js::array<js::any>{}) override;
protected:
    auto fetchConnection(js::any input) override;
private:
    std::shared_ptr<ThreadsData> _data;
    auto setupNewThread(js::any input) override;
    auto setupThread(Thread newThread) override;
    auto newThread(js::any input, js::string url) override;
};

#endif // FRAGMENTS_CONNECTION_H