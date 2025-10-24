#include "index_generated.h"
#include "face-utils.h"

using namespace js;

auto FaceUtils::getEarcutDimensions(js::any normal) {
    {
            const js::any absX = js::Math::abs(normal["x"]);
            const js::any absY = js::Math::abs(normal["y"]);
            const js::any absZ = js::Math::abs(normal["z"]);
            const js::number xDim = js::number(0);
            const js::number yDim = js::number(1);
            const js::number zDim = js::number(2);
            const js::any isMostlyHorizontal = ((absZ > absX) && (absZ > absY));
            if (isMostlyHorizontal) {
                        {
                                        const bool lookingUp = (normal["z"] > js::number(0));
                                        if (lookingUp) {
                                                            {
                                                                                    return js::array<js::any>{xDim, yDim};
                                                            }
                                        }
                                        return js::array<js::any>{yDim, xDim};
                        }
            }
            const js::any isMostlyLookingToY = ((absY > absX) && (absY > absZ));
            if (isMostlyLookingToY) {
                        {
                                        const bool isLookingYPositive = (normal["y"] > js::number(0));
                                        if (isLookingYPositive) {
                                                            {
                                                                                    return js::array<js::any>{zDim, xDim};
                                                            }
                                        }
                                        return js::array<js::any>{xDim, zDim};
                        }
            }
            const bool isLookingXPositive = (normal["x"] > js::number(0));
            if (isLookingXPositive) {
                        {
                                        return js::array<js::any>{yDim, zDim};
                        }
            }
            return js::array<js::any>{zDim, yDim};
    }
}
