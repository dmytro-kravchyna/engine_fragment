#include "index_generated.h"
#include "crc.h"

using namespace js;

CRC::CRC() {
    {
            this->_handlers = this->newHandlers();
    }
}

auto CRC::fromMaterialData(js::any data) {
    {
            auto _temp2086 = data;
            const auto modelId = _temp2086["modelId"];
            const auto objectClass = _temp2086["objectClass"];
            const auto currentLod = _temp2086["currentLod"];
            const auto templateId = _temp2086["templateId"];
            const auto materialDefinition = [&]() {
              js::object materialDefinition_temp;
              // Copy all properties except extracted ones
              for (const auto& [key, value] : _temp2086.as_object().entries()) {
                if (key != "modelId" && key != "objectClass" && key != "currentLod" && key != "templateId") {
                  materialDefinition_temp.set(key, value);
                }
              }
              return js::any(materialDefinition_temp);
            }();
            this->reset();
            this->compute(modelId);
            this->compute(objectClass);
            this->compute(materialDefinition);
            this->compute(currentLod);
            this->compute(templateId !== js::undefined);
    }
}

auto CRC::generate(js::array<js::any> input) {
    {
            this->reset();
            for (const auto& item : input) {
                        {
                                        this->compute(item);
                        }
            }
            return this->value;
    }
}

auto CRC::compute(js::any input) {
    {
            const js::any handler = this->getHandler(input);
            handler(input);
            return this;
    }
}

auto CRC::reset() {
    {
            this->_result = ~js::number(0);
            return this;
    }
}

auto CRC::getHandler(js::any input) {
    {
            const js::any inputType = js::typeof_op(input);
            const js::any handler = this->_handlers[inputType];
            if (!handler) {
                        {
                                        throw js::any(js::Error("Fragments: Unsupported input type"_S));
                        }
            }
            return handler;
    }
}

auto CRC::newHandlers() {
    {
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("number", this->handleNumber);
                  obj_temp_0.set("boolean", this->handleBoolean);
                  obj_temp_0.set("string", this->handleString);
                  obj_temp_0.set("object", this->handleObject);
                  return js::any(obj_temp_0);
                }();
    }
}

auto CRC::update() {
    {
            for (js::number i = js::number(0); (i < this->_core.s1); ++i) {
                        {
                                        this->_result ^= this->_core.buffer[i];
                                        for (js::number j = js::number(0); (j < this->_core.s2); ++j) {
                                                            {
                                                                                    if ((this->_result & js::number(1))) {
                                                                                                                {
                                                                                                                                                this->_result = ((this->_result >> js::number(1)) ^ CRC::_polynomial);
                                                                                                                }
                                                                                    } else {
                                                                                                                {
                                                                                                                                                this->_result >>= js::number(1);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
    }
}
