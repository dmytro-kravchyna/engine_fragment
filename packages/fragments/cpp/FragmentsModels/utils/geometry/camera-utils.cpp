#include "index_generated.h"
#include "camera-utils.h"

using namespace js;

auto CameraUtils::transform(js::any input, js::any transform, auto result) {
    {
            for (js::number i = js::number(0); (i < result->planes.length()); i++) {
                        {
                                        const js::any resultPlane = result->planes[i];
                                        const js::any inputPlane = input["planes"][i];
                                        resultPlane->copy(inputPlane);
                                        resultPlane->applyMatrix4(transform);
                        }
            }
            return result;
    }
}

auto CameraUtils::isIncluded(js::any box, js::array<unknown> ps) {
    {
            return PlanesUtils::collides(box, ps, true);
    }
}

auto CameraUtils::collides(js::any box, js::array<unknown> ps) {
    {
            return PlanesUtils::collides(box, ps, false);
    }
}
