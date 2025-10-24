#include "index_generated.h"
#include "bit-utils.h"

using namespace js;

auto BitUtils::check(DataBuffer data, js::number id, ItemConfigClass config) {
    {
            const js::any filter = this->get(config);
            const js::any currentData = data->id;
            const js::any result = Boolean((currentData & filter));
            return result;
    }
}

void BitUtils::apply(DataBuffer data, js::number id, ItemConfigClass config, bool value) {
    {
            const js::any filter = this->get(config);
            if (value) {
                        {
                                        data->id |= filter;
                                        return;
                        }
            }
            data->id &= ~filter;
    }
}

auto BitUtils::checkMemory(js::number id) {
    {
            if ((id > limitOf2Bytes)) {
                        {
                                        throw js::any(js::Error("Fragments: Memory overflow!"_S));
                        }
            }
    }
}

auto BitUtils::get(js::number value) {
    {
            return (js::number(1) << value);
    }
}
