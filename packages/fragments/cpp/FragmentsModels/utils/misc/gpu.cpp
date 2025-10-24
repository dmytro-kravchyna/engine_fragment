#include "index_generated.h"
#include "gpu.h"

using namespace js;

auto GPU::estimateCapacity() {
    {
            const js::any factor = this->capacityFactor;
            const js::any width = window["screen"]["width"];
            const js::any height = window["screen"]["height"];
            const js::any ratio = window["devicePixelRatio"];
            const js::any result = js::Math::trunc(((((width * height) * ratio) * ratio) * factor));
            return result;
    }
}
