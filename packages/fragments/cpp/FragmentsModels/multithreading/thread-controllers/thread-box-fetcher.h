#ifndef THREAD_BOX_FETCHER_H
#define THREAD_BOX_FETCHER_H

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
#include "./thread-controller.h"

using namespace js;

// Forward declarations
class ThreadBoxFetcher;

class ThreadBoxFetcher : public ThreadController {
public:
    ThreadBoxFetcher() = default;
protected:
    auto getId() override;
    auto execute(js::any input) override;
private:
    auto getBoxesFromLocalIds(js::any input) override;
    auto getAllBoxes(js::any input) override;
};

#endif // THREAD_BOX_FETCHER_H