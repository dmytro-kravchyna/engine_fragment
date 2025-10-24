#include "index_generated.h"
#include "planes-utils.h"

using namespace js;

auto PlanesUtils::containedInParallelPlanes(js::array<unknown> ps, js::any point) {
    {
            bool result = true;
            for (const auto& clipPlane : ps) {
                        {
                                        const js::any distance = clipPlane->distanceToPoint(point);
                                        const js::any isInFront = distance >= js::number(0);
                                        result = (result && isInFront);
                        }
            }
            return result;
    }
}

auto PlanesUtils::collides(js::any box, js::array<unknown> ps, bool included) {
    {
            for (const auto& plane : ps) {
                        {
                                        const js::any distance = this->getPointDistance(plane, included, box);
                                        if ((distance < js::number(0))) {
                                                            {
                                                                                    return false;
                                                            }
                                        }
                        }
            }
            return true;
    }
}

auto PlanesUtils::getPointDistance(js::any plane, bool included, js::any box) {
    {
            const js::any normal = plane["normal"];
            for (const auto& dim : this->dimensions) {
                        {
                                        const js::any isPositive = normal[dim] >= js::number(0);
                                        const js::any isMax = isPositive !== included;
                                        if (isMax) {
                                                            {
                                                                                    this->tempPoint[dim] = box["max"][dim];
                                                            }
                                        } else {
                                                            {
                                                                                    this->tempPoint[dim] = box["min"][dim];
                                                            }
                                        }
                        }
            }
            return plane["distanceToPoint"](this->tempPoint);
    }
}
