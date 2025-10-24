#include "index_generated.h"
#include "material-utils.h"

using namespace js;

auto MaterialUtils::isSame(MaterialDefinition a, MaterialDefinition b) {
    {
            const js::any isSameColor = this->checkSameColor(a["color"], b["color"]);
            const js::any isSameOpacity = this->checkSame(a["opacity"], b["opacity"], js::number(1));
            const js::any facesA = a["renderedFaces"];
            const js::any facesB = b["renderedFaces"];
            const js::any isSameFaces = this->checkSame(facesA, facesB, RenderedFaces::ONE);
            return ((isSameColor && isSameOpacity) && isSameFaces);
    }
}

bool MaterialUtils::checkSame(js::any a, js::any b, js::any fallback) {
    {
            if (a === b) {
                        {
                                        return true;
                        }
            }
            if ((a === fallback && b === js::undefined)) {
                        {
                                        return true;
                        }
            }
            if ((a === js::undefined && b === fallback)) {
                        {
                                        return true;
                        }
            }
            return false;
    }
}

auto MaterialUtils::checkSameColor(js::any a, js::any b) {
    {
            if (a === b) {
                        {
                                        return true;
                        }
            }
            if ((a === js::undefined || b === js::undefined)) {
                        {
                                        return false;
                        }
            }
            auto _temp5178 = a;
            const auto ar = _temp5178["r"];
            const auto ag = _temp5178["g"];
            const auto ab = _temp5178["b"];
            auto _temp9468 = b;
            const auto br = _temp9468["r"];
            const auto bg = _temp9468["g"];
            const auto bb = _temp9468["b"];
            if (((ar === br && ag === bg) && ab === bb)) {
                        {
                                        return true;
                        }
            }
            return false;
    }
}
