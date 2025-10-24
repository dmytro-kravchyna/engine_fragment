#ifndef THREAD_RAYCASTER_H
#define THREAD_RAYCASTER_H

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
#include "../multithreading-helper.h"

using namespace js;

// Forward declarations
class ThreadRaycaster;

// Enum RaycastType
namespace RaycastType {
    extern const js::number BEAM;
    extern const js::number RECTANGLE;
    extern const js::number WITH_SNAP;
    js::string getName(js::number key);
}

class ThreadRaycaster : public ThreadController {
public:
    ThreadRaycaster() = default;
protected:
    auto getId() override;
    auto execute(js::any input) override;
private:
    auto getRaycastType(js::any input) override;
    auto raycastRectangle(js::any input) override;
    auto raycastWithSnap(js::any input) override;
    auto raycastBeam(js::any input) override;
};

#endif // THREAD_RAYCASTER_H