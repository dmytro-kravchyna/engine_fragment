#ifndef CRC_DATA_H
#define CRC_DATA_H

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

using namespace js;

// Forward declarations
class CRCData;

class CRCData {
public:
    std::shared_ptr<DataBuffer> int;
    std::shared_ptr<DataBuffer> float;
    std::shared_ptr<DataBuffer> buffer;
    auto s1;
    auto s2;
    CRCData();
private:
    virtual auto newBuffers();
};

#endif // CRC_DATA_H