#include "index_generated.h"
#include "thread-updater.h"

using namespace js;

ThreadUpdater::ThreadUpdater(FragmentsThread thread) {
    {
            this->_thread = thread;
            const js::any updateAll = [&]() -> auto {
            const js::any updated = this->updateAllModels();
            const js::any delay = (js::null ? js::null : js::null);
            setTimeout(updateAll, delay);
            };
            updateAll();
    }
}

auto ThreadUpdater::updateAllModels() {
    {
            const js::any start = performance["now"]();
            bool isUpdated = true;
            for (const auto& js::undefined : this->_thread.list) {
                        {
                                        const js::any modelUpdated = model["update"](start);
                                        isUpdated = (isUpdated && modelUpdated);
                                        const js::any end = performance["now"]();
                                        const js::number timePassed = (end - start);
                                        if ((timePassed > this->_updateThreshold)) {
                                                            {
                                                                                    break;
                                                            }
                                        }
                        }
            }
            return isUpdated;
    }
}
