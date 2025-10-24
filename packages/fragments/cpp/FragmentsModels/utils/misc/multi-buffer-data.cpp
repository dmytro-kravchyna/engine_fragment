#include "index_generated.h"
#include "multi-buffer-data.h"

using namespace js;

MultiBufferData::MultiBufferData(js::number size, T firstElement) {
    {
            this->_first = this->newData(size, firstElement);
    }
}

auto MultiBufferData::getComplementary(js::any data, std::function<void(js::number, js::number)> callback) {
    {
            js::number past = js::number(0);
            const js::any length = data->position.length();
            past = this->makeBufferComplementary(length, data, past, callback);
            if (past !== js::number::POSITIVE_INFINITY) {
                        {
                                        callback(past, js::number::POSITIVE_INFINITY);
                        }
            }
    }
}

auto MultiBufferData::get(MultiBufferData data, js::array<js::number> positions, std::optional<Filter> filter, std::optional<std::function<void(js::number, T)>> callback) {
    {
            auto _temp8221 = this->getData(data, filter);
            const auto filtered = _temp8221["filtered"];
            const auto position = _temp8221["position"];
            const auto size = _temp8221["size"];
            this->setAllBufferData(filtered, positions, position, size, callback);
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("position", position);
                  obj_temp_0.set("size", size);
                  return js::any(obj_temp_0);
                }();
    }
}

auto MultiBufferData::fullOf(T data) {
    {
            const js::any followingItem = this->_first.following;
            const js::any first = this->_first.data;
            const js::any noFollowing = followingItem === js::null;
            const js::any sameData = first === data;
            return (noFollowing && sameData);
    }
}

auto MultiBufferData::update(js::number position, T data) {
    {
            const js::any input = this->getBufferData(position);
            const js::any isSame = input["data"] === data;
            if (!isSame) {
                        {
                                        auto _temp4951 = this->newBuffers(position, input, data);
                                        const auto a = _temp4951["a"];
                                        const auto c = _temp4951["c"];
                                        const auto b = _temp4951["b"];
                                        this->setupInputData(input, a, c);
                                        this->setupUpdateBuffers(a, b, c);
                        }
            }
    }
}

auto MultiBufferData::size(std::optional<Filter> filter) {
    {
            js::number index = js::number(0);
            js::any data = this->_first;
            while (js::null) {
                        {
                        }
            }
            return index;
    }
}

auto MultiBufferData::setAllBufferData(js::array<BufferData> filtered, js::array<js::number> positions, js::Uint32Array position, js::Uint32Array size, std::optional<std::function<void(js::number, T)>> callback) {
    {
            for (js::number i = js::number(0); (i < filtered.length()); ++i) {
                        {
                                        const js::any input = filtered[i];
                                        this->transform(input, positions);
                                        this->setBuffers(position, size, i);
                                        if (callback) {
                                                            {
                                                                                    callback(i, input["data"]);
                                                            }
                                        }
                        }
            }
    }
}

auto MultiBufferData::makeBufferComplementary(js::any length, js::any data, js::number past, std::function<void(js::number, js::number)> callback) {
    {
            for (js::number i = js::number(0); (i < length); ++i) {
                        {
                                        const js::any input = this->getBuffers(data, i);
                                        auto _temp1874 = input;
                                        const auto position = _temp1874["position"];
                                        const auto size = _temp1874["size"];
                                        if ((position > past)) {
                                                            {
                                                                                    callback(past, (position - past));
                                                            }
                                        }
                                        past = (position + size);
                        }
            }
            return past;
    }
}

auto MultiBufferData::setBuffers(DataBuffer position, DataBuffer size, js::number i) {
    {
            position[i] = this->_tempData.position;
            const js::any isInf = this->_tempData.size === js::number::POSITIVE_INFINITY;
            if (isInf) {
                        {
                                        size[i] = this->_inf;
                        }
            } else {
                        {
                                        size[i] = this->_tempData.size;
                        }
            }
    }
}

auto MultiBufferData::add(js::number position, js::number size, T data) {
    {
            const js::any stashExists = MultiBufferData::_stash::length;
            if (!stashExists) {
                        {
                                        return this->newData(size, data, position);
                        }
            }
            const js::any stashed = MultiBufferData::_stash::pop();
            if (!stashed) {
                        {
                                        throw js::any(js::Error("Fragments: No stash found"_S));
                        }
            }
            stashed["position"] = position;
            stashed["size"] = size;
            stashed["data"] = data;
            return stashed;
    }
}

auto MultiBufferData::remove(BufferData data) {
    {
            if (data) {
                        {
                                        data->following = js::null;
                                        data->past = js::null;
                                        MultiBufferData::_stash::push(data);
                        }
            }
    }
}

auto MultiBufferData::getData(MultiBufferData data, std::optional<Filter> filter) {
    {
            const js::any filtered = data.filter(filter);
            const js::any length = filtered.length();
            const std::shared_ptr<Uint32Array> position = std::make_shared<Uint32Array>(length);
            const std::shared_ptr<Uint32Array> size = std::make_shared<Uint32Array>(length);
            return []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("filtered", filtered);
                  obj_temp_1.set("position", position);
                  obj_temp_1.set("size", size);
                  return js::any(obj_temp_1);
                }();
    }
}

auto MultiBufferData::filter(std::optional<Filter> filter) {
    {
            js::array<js::any> found = js::array<js::any>{};
            js::typed::Nullable<BufferData> data = this->_first;
            while (js::null) {
                        {
                        }
            }
            return found;
    }
}

auto MultiBufferData::transform(BufferData input, js::array<js::number> positions) {
    {
            const js::any result = this->getTempData();
            const js::number finalPosition = (input["position"] + input["size"]);
            const js::any isFinal = finalPosition === positions.length();
            result->position = positions[input["position"]];
            if (isFinal) {
                        {
                                        result->size = js::number::POSITIVE_INFINITY;
                        }
            } else {
                        {
                                        const js::any total = positions[finalPosition];
                                        result->size = (total - result->position);
                        }
            }
            return result;
    }
}

auto MultiBufferData::getBuffers(js::any data, js::number i) {
    {
            const js::any position = data->position[i];
            const js::any isInf = data->size[i] === this->_inf;
            js::number size;
            if (isInf) {
                        {
                                        size = js::number::POSITIVE_INFINITY;
                        }
            } else {
                        {
                                        size = data->size[i];
                        }
            }
            return []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("position", position);
                  obj_temp_2.set("size", size);
                  return js::any(obj_temp_2);
                }();
    }
}

auto MultiBufferData::getTempData() {
    {
            if (!this->_tempData) {
                        {
                                        return []() {
                                              js::object obj_temp_3;
                                              obj_temp_3.set("position", js::number(0));
                                              obj_temp_3.set("size", js::number(0));
                                              return js::any(obj_temp_3);
                                            }();
                        }
            }
            return this->_tempData;
    }
}

auto MultiBufferData::doesFilterPass(js::typed::Nullable<Filter> filter, BufferData data) {
    {
            const js::any noFilter = !filter;
            const js::any filterPass = (noFilter || filter(data->data));
            return filterPass;
    }
}

auto MultiBufferData::setupUpdateBuffers(BufferData a, BufferData b, BufferData c) {
    {
            this->chainBuffers(a, b, c);
            this->setupFirstBuffer(a, b);
            this->setupLastBuffer(c, b);
            this->setupMiddleBufferStart(b);
            this->setupMiddleBufferEnd(b);
    }
}

auto MultiBufferData::setupMiddleBufferEnd(BufferData b) {
    {
            if (b["following"]["data"] === b["data"]) {
                        {
                                        if (!b["following"]) {
                                                            {
                                                                                    return;
                                                            }
                                        }
                                        const js::number newSize = (b["following"]["size"] + b["size"]);
                                        const js::any following = b["following"]["following"];
                                        b["size"] = newSize;
                                        this->remove(b["following"]);
                                        b["following"] = following;
                                        if (b["following"]) {
                                                            {
                                                                                    b["following"]["past"] = b;
                                                            }
                                        }
                        }
            }
    }
}

auto MultiBufferData::setupFirstBuffer(BufferData a, BufferData b) {
    {
            if (!a["size"]) {
                        {
                                        if (a["past"]) {
                                                            {
                                                                                    a["past"]["following"] = b;
                                                            }
                                        } else {
                                                            {
                                                                                    this->_first = b;
                                                            }
                                        }
                                        b["past"] = a["past"];
                                        this->remove(a);
                        }
            }
    }
}

auto MultiBufferData::setupMiddleBufferStart(BufferData b) {
    {
            if (b["past"]["data"] === b["data"]) {
                        {
                                        if (!b["past"]) {
                                                            {
                                                                                    return;
                                                            }
                                        }
                                        b["size"] = (b["past"]["size"] + b["size"]);
                                        b["position"] = b["past"]["position"];
                                        const js::any past = b["past"]["past"];
                                        this->remove(b["past"]);
                                        b["past"] = past;
                                        if (b["past"]) {
                                                            {
                                                                                    b["past"]["following"] = b;
                                                            }
                                        } else {
                                                            {
                                                                                    this->_first = b;
                                                            }
                                        }
                        }
            }
    }
}

auto MultiBufferData::chainBuffers(BufferData a, BufferData b, BufferData c) {
    {
            a["following"] = b;
            b["past"] = a;
            b["following"] = c;
            c["past"] = b;
    }
}

auto MultiBufferData::setupLastBuffer(BufferData c, BufferData b) {
    {
            if (!c["size"]) {
                        {
                                        if (c["following"]) {
                                                            {
                                                                                    c["following"]["past"] = b;
                                                            }
                                        }
                                        b["following"] = c["following"];
                                        this->remove(c);
                        }
            }
    }
}

auto MultiBufferData::newBuffers(js::number position, js::any input, T data) {
    {
            const js::number aSize = (position - input["position"]);
            const js::any a = this->add(input["position"], aSize, input["data"]);
            const js::any b = this->add(position, js::number(1), data);
            const js::number cSize = ((input["size"] - a["size"]) - js::number(1));
            const js::any c = this->add((position + js::number(1)), cSize, input["data"]);
            return []() {
                  js::object obj_temp_4;
                  obj_temp_4.set("a", a);
                  obj_temp_4.set("c", c);
                  obj_temp_4.set("b", b);
                  return js::any(obj_temp_4);
                }();
    }
}

auto MultiBufferData::setupInputData(js::any input, BufferData a, BufferData c) {
    {
            if (input["past"]) {
                        {
                                        input["past"]["following"] = a;
                                        a["past"] = input["past"];
                        }
            } else {
                        {
                                        this->_first = a;
                        }
            }
            if (input["following"]) {
                        {
                                        input["following"]["past"] = c;
                                        c["following"] = input["following"];
                        }
            }
            this->remove(input);
    }
}

auto MultiBufferData::newData(js::number size, T data, auto position) {
    {
            return []() {
                  js::object obj_temp_5;
                  obj_temp_5.set("position", position);
                  obj_temp_5.set("size", size);
                  obj_temp_5.set("past", js::null);
                  obj_temp_5.set("following", js::null);
                  obj_temp_5.set("data", data);
                  return js::any(obj_temp_5);
                }();
    }
}

auto MultiBufferData::getBufferData(js::number index) {
    {
            js::any found = this->_first;
            while (js::null) {
                        {
                        }
            }
    }
}
