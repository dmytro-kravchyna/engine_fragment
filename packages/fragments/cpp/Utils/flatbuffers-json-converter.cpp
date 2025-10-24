#include "index_generated.h"
#include "flatbuffers-json-converter.h"

using namespace js;

auto getObject(js::any obj, js::any result) {
    const js::any proto = js::Object::getPrototypeOf(obj);
    const js::any propNames = js::Object::getOwnPropertyNames(proto);
    for (const auto& name : propNames) {
            {
                        if ((name === "constructor"_S || name === "__init"_S)) {
                                        continue;
                        }
                        if (name.includes("mutate_"_S)) {
                                        continue;
                        }
                        if (name.match(js::null)) {
                                        continue;
                        }
                        const js::any value = proto[name];
                        if (js::typeof_op(value) === "function"_S) {
                                        {
                                                            const js::any isArray = (obj->(js::toString(name) + "Length"_S) !== js::undefined && obj->(js::toString(name) + "Array"_S) !== js::undefined);
                                                            if ((value.length() === js::number(2) || isArray)) {
                                                                                    {
                                                                                                                const js::any lengthName = (js::toString(name) + "Length"_S);
                                                                                                                const js::any length = obj->lengthName();
                                                                                                                js::array<js::any> array = js::array<js::any>{};
                                                                                                                result->name = array;
                                                                                                                for (js::number i = js::number(0); (i < length); i++) {
                                                                                                                                                {
                                                                                                                                                                                    const js::any found = obj->name(i);
                                                                                                                                                                                    if (((js::typeof_op(found) === "object"_S && found !== js::null) && js::in_op("bb"_S, found))) {
                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                        const js::any object = []() {
                                                                                                                                                                                                                                                                              js::object obj_temp_0;
                                                                                                                                                                                                                                                                              return js::any(obj_temp_0);
                                                                                                                                                                                                                                                                            }();
                                                                                                                                                                                                                                                                        getObject(found, object);
                                                                                                                                                                                                                                                                        array.push(object);
                                                                                                                                                                                                                            }
                                                                                                                                                                                    } else {
                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                        array.push(found);
                                                                                                                                                                                                                            }
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                                                continue;
                                                                                    }
                                                            }
                                                            const js::any found = obj->name();
                                                            if ((js::typeof_op(found) !== "object"_S || found === js::null)) {
                                                                                    {
                                                                                                                result->name = found;
                                                                                                                continue;
                                                                                    }
                                                            }
                                                            result->name = []() {
                                                                  js::object obj_temp_1;
                                                                  return js::any(obj_temp_1);
                                                                }();
                                                            getObject(found, result->name);
                                        }
                        } else {
                                        {
                                                            result->name = value;
                                        }
                        }
            }
    }
}
