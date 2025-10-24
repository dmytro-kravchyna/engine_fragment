#include "index_generated.h"
#include "int-helper.h"

using namespace js;

auto IntHelper::check(js::number data) {
    {
            const js::any isInteger = Number::isInteger(data);
            const bool notOverflow = (data < this->_max);
            const bool notUnderflow = (data > this->_min);
            return ((isInteger && notOverflow) && notUnderflow);
    }
}
