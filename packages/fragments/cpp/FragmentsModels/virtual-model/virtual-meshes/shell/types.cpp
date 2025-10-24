#include "index_generated.h"
#include "types.h"

using namespace js;

// Enum PolygonSize implementation
const js::number PolygonSize::four = js::number(4);
const js::number PolygonSize::three = js::number(3);

js::string PolygonSize::getName(js::number key) {
    if (key.value() == js::number(4).value()) return "four"_S;
    if (key.value() == js::number(3).value()) return "three"_S;
    return "undefined"_S;
}

