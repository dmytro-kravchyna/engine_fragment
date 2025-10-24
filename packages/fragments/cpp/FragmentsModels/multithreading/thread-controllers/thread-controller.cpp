#include "index_generated.h"
#include "thread-controller.h"

using namespace js;

ThreadController::ThreadController(FragmentsThread thread) {
    {
            this->id = this->getId();
            this->thread = thread;
            this->thread.actions[this->id] = [&](js::any input) -> auto { return this->execute(input); };
    }
}
