#ifndef VIRTUAL_BOX_SORTER_H
#define VIRTUAL_BOX_SORTER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include <three.h>
#include "../model/model-types.h"
#include "./virtual-box-controller.h"

using namespace js;

// Forward declarations
class VirtualBoxSorter;

class VirtualBoxSorter {
public:
    VirtualBoxSorter(VirtualBoxController boxes);
    virtual auto sort(DataBuffer dataBuffer, js::number a, js::number b);
private:
    std::shared_ptr<VirtualBoxController> _boxes;
    auto _total;
    auto _change;
    auto _average;
    auto _tempCenterVector;
    auto _tempVectors;
    virtual auto anySort(js::number a, js::number b, DataBuffer dataBuffer);
    virtual auto getDataToTotal(js::number a, js::number b, DataBuffer dataBuffer);
    virtual auto sortDim(js::any dimension, js::number threshold, js::number first, js::number second, DataBuffer elements);
    virtual auto exchange(js::number first, js::number second, DataBuffer elements);
    virtual auto getValue(DataBuffer elements, js::number i, js::any dimension);
    virtual auto average(js::any result, DataBuffer elements, js::number first, js::number second);
    virtual auto aggregate(js::number first, js::number second, DataBuffer elements, js::any box, js::any result);
    virtual auto adjust(js::number b, js::number a, js::number result);
    virtual auto getBox(DataBuffer elements, js::number index);
};

#endif // VIRTUAL_BOX_SORTER_H