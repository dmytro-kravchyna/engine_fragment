#include "index_generated.h"
#include "utils.h"

using namespace js;

auto round(js::number value, js::number precission) {
    return (js::Math::round((value * precission)) / precission);
}
