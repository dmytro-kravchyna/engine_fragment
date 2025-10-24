#include "index_generated.h"
#include "misc-helper.h"

using namespace js;

auto MiscHelper::fixNumber(js::number value) {
    {
            if (Number::isNaN(value)) {
                        {
                                        return js::number(0);
                        }
            }
            if (!Number::isFinite(value)) {
                        {
                                        return js::number(0);
                        }
            }
            return value;
    }
}

auto MiscHelper::forEach(js::any items, ForEachCallback callback) {
    {
            if (js::array.isArray(items)) {
                        {
                                        js::number counter = js::number(0);
                                        for (const auto& item : items) {
                                                            {
                                                                                    callback(item, counter++);
                                                            }
                                        }
                                        return;
                        }
            }
            callback(items, js::number(0));
    }
}
