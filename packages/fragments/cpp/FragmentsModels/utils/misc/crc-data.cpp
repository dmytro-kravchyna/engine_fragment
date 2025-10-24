#include "index_generated.h"
#include "crc-data.h"

using namespace js;

CRCData::CRCData() {
    {
            auto _temp5290 = this->newBuffers();
            const auto intBuffer = _temp5290["intBuffer"];
            const auto floatBuffer = _temp5290["floatBuffer"];
            const auto buffer = _temp5290["buffer"];
            this->int = intBuffer;
            this->float = floatBuffer;
            this->buffer = buffer;
    }
}

auto CRCData::newBuffers() {
    {
            const std::shared_ptr<Int32Array> intBuffer = std::make_shared<Int32Array>(js::number(1));
            const js::any data = intBuffer->buffer;
            const std::shared_ptr<Float32Array> floatBuffer = std::make_shared<Float32Array>(data);
            const std::shared_ptr<Uint8Array> buffer = std::make_shared<Uint8Array>(data);
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("intBuffer", intBuffer);
                  obj_temp_0.set("floatBuffer", floatBuffer);
                  obj_temp_0.set("buffer", buffer);
                  return js::any(obj_temp_0);
                }();
    }
}
