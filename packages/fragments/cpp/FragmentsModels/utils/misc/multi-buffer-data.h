#ifndef MULTI_BUFFER_DATA_H
#define MULTI_BUFFER_DATA_H

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
class MultiBufferData;

// Interface BufferData
class IBufferData {
public:
    virtual ~IBufferData() = default;
    // TODO: Interface members
};
template<typename T>
class MultiBufferData {
public:
    MultiBufferData(js::number size, T firstElement);
    auto getComplementary(js::any data, std::function<void(js::number, js::number)> callback);
    auto get(MultiBufferData data, js::array<js::number> positions, std::optional<Filter> filter = std::nullopt, std::optional<std::function<void(js::number, T)>> callback = std::nullopt);
    virtual auto fullOf(T data);
    virtual auto update(js::number position, T data);
    virtual auto size(std::optional<Filter> filter = std::nullopt);
private:
    js::array<BufferData> _stash;
    std::shared_ptr<BufferData> _first;
    auto _tempData;
    auto _inf;
    auto setAllBufferData(js::array<BufferData> filtered, js::array<js::number> positions, js::Uint32Array position, js::Uint32Array size, std::optional<std::function<void(js::number, T)>> callback = std::nullopt);
    auto makeBufferComplementary(js::any length, js::any data, js::number past, std::function<void(js::number, js::number)> callback);
    auto setBuffers(DataBuffer position, DataBuffer size, js::number i);
    virtual auto add(js::number position, js::number size, T data);
    virtual auto remove(BufferData data);
    auto getData(MultiBufferData data, std::optional<Filter> filter = std::nullopt);
    virtual auto filter(std::optional<Filter> filter = std::nullopt);
    auto transform(BufferData input, js::array<js::number> positions);
    auto getBuffers(js::any data, js::number i);
    auto getTempData();
    virtual auto doesFilterPass(js::typed::Nullable<Filter> filter, BufferData data);
    virtual auto setupUpdateBuffers(BufferData a, BufferData b, BufferData c);
    virtual auto setupMiddleBufferEnd(BufferData b);
    virtual auto setupFirstBuffer(BufferData a, BufferData b);
    virtual auto setupMiddleBufferStart(BufferData b);
    virtual auto chainBuffers(BufferData a, BufferData b, BufferData c);
    virtual auto setupLastBuffer(BufferData c, BufferData b);
    virtual auto newBuffers(js::number position, js::any input, T data);
    virtual auto setupInputData(js::any input, BufferData a, BufferData c);
    virtual auto newData(js::number size, T data, auto position = js::number(0));
    virtual auto getBufferData(js::number index);
};

#endif // MULTI_BUFFER_DATA_H