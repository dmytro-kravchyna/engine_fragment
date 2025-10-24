#include "index_generated.h"
#include "data-map.h"

using namespace js;

DataMap::DataMap(std::optional<js::any> iterable) : Map(iterable) {
    {
    }
}

auto DataMap::clear() {
    {
            for (const auto& js::undefined : this) {
                        {
                                        this->onBeforeDelete.trigger([]() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("key", key);
                                              obj_temp_0.set("value", value);
                                              return js::any(obj_temp_0);
                                            }());
                        }
            }
            Map::clear();
            this->onCleared.trigger();
    }
}

auto DataMap::set(K key, V value) {
    {
            const js::any triggerUpdate = this->has(key);
            const js::any guard = (this->guard.has_value() ? this->guard : [&]() -> auto { return true; });
            const js::any isValid = guard(key, value);
            if (!isValid) {
                        return this;
            }
            const js::any result = Map::set(key, value);
            if (triggerUpdate) {
                        {
                                        if (!this->onItemUpdated) {
                                                            {
                                                                                    this->onItemUpdated = std::make_shared<Event>();
                                                            }
                                        }
                                        this->onItemUpdated.trigger([]() {
                                              js::object obj_temp_1;
                                              obj_temp_1.set("key", key);
                                              obj_temp_1.set("value", value);
                                              return js::any(obj_temp_1);
                                            }());
                        }
            } else {
                        {
                                        if (!this->onItemSet) {
                                                            {
                                                                                    this->onItemSet = std::make_shared<Event>();
                                                            }
                                        }
                                        this->onItemSet.trigger([]() {
                                              js::object obj_temp_2;
                                              obj_temp_2.set("key", key);
                                              obj_temp_2.set("value", value);
                                              return js::any(obj_temp_2);
                                            }());
                        }
            }
            return result;
    }
}

auto DataMap::delete(K key) {
    {
            const js::any value = this->get(key);
            if (!value) {
                        return false;
            }
            this->onBeforeDelete.trigger([]() {
                  js::object obj_temp_3;
                  obj_temp_3.set("key", key);
                  obj_temp_3.set("value", value);
                  return js::any(obj_temp_3);
                }());
            const js::any deleted = Map::delete(key);
            if (deleted) {
                        this->onItemDeleted.trigger(key);
            }
            return deleted;
    }
}

auto DataMap::getKey(V item) {
    {
            for (const auto& js::undefined : this) {
                        {
                                        if (value === item) {
                                                            return key;
                                        }
                        }
            }
            return js::undefined;
    }
}

auto DataMap::update(V item) {
    {
            const js::any key = this->getKey(item);
            if (key) {
                        this->set(key, item);
            }
    }
}

auto DataMap::deleteIf(std::function<bool(V, K)> predicate) {
    {
            for (const auto& js::undefined : this) {
                        {
                                        if (predicate(value, key)) {
                                                            {
                                                                                    this->delete(key);
                                                            }
                                        }
                        }
            }
    }
}

auto DataMap::replaceKey(K oldKey, K newKey, auto fullReplace) {
    {
            const js::any oldKeyItem = this->get(oldKey);
            if (!oldKeyItem) {
                        return false;
            }
            const js::any newKeyItem = this->get(newKey);
            if ((newKeyItem && !fullReplace)) {
                        return false;
            }
            this->eventsEnabled = false;
            this->delete(oldKey);
            this->eventsEnabled = true;
            this->set(newKey, oldKeyItem);
            return true;
    }
}

auto DataMap::dispose() {
    {
            this->clear();
            this->onItemSet.reset();
            this->onItemDeleted.reset();
            this->onItemUpdated.reset();
            this->onCleared.reset();
            this->onBeforeDelete.reset();
    }
}
