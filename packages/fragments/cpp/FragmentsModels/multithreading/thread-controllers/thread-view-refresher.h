#ifndef THREAD_VIEW_REFRESHER_H
#define THREAD_VIEW_REFRESHER_H

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
#include "../../model/model-types.h"
#include "../multithreading-helper.h"
#include "./thread-controller.h"

using namespace js;

// Forward declarations
class ThreadViewRefresher;

class ThreadViewRefresher : public ThreadController {
public:
    ThreadViewRefresher() = default;
protected:
    auto getId() override;
    auto execute(js::any input) override;
private:
    auto safeCopyFrustum(js::any input) override;
    auto safeCopyPosition(js::any input) override;
    auto safeCopyPlanes(js::any input) override;
};

#endif // THREAD_VIEW_REFRESHER_H