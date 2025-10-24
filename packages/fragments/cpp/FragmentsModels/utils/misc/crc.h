#ifndef CRC_H
#define CRC_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../../model/model-types.h"
#include "./crc-data.h"
#include "./int-helper.h"

using namespace js;

// Forward declarations
class CRC;

class CRC {
public:
    CRC();
    virtual auto fromMaterialData(js::any data);
    virtual auto generate(js::array<js::any> input);
    virtual auto compute(js::any input);
    virtual auto reset();
private:
    auto _polynomial;
    auto _core;
    js::any _handlers;
    auto _result;
    virtual auto getHandler(js::any input);
    virtual auto newHandlers();
    auto handleObject;
    auto handleString;
    auto handleBoolean;
    auto handleNumber;
    virtual auto update();
};

#endif // CRC_H