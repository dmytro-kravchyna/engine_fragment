#include "index_generated.h"
#include "plane.h"

using namespace js;

Plane::Plane(js::any plane, js::number precission, js::number normalPrecision) {
    {
            const js::any nx = round(plane["normal"]["x"], normalPrecision);
            const js::any ny = round(plane["normal"]["y"], normalPrecision);
            const js::any nz = round(plane["normal"]["z"], normalPrecision);
            const js::any c = round(plane["constant"], precission);
            this->normal = std::make_shared<three::Vector3>(nx, ny, nz);
            this->constant = c;
            const js::string planeSeparator = "||"_S;
            this->id = (js::toString(nx) + js::toString(planeSeparator) + js::toString(ny) + js::toString(planeSeparator) + js::toString(nz) + js::toString(planeSeparator) + js::toString(c));
    }
}
