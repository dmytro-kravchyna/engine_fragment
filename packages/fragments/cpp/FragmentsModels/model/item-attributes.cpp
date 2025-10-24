#include "index_generated.h"
#include "item-attributes.h"

using namespace js;

ItemAttributes::ItemAttributes(js::number localId, std::optional<js::any> iterable) : Map(iterable) {
    {
            this->localId = localId;
    }
}

auto ItemAttributes::set(js::string key, AttributeData attr) {
    {
            const js::any guard = (this->guard.has_value() ? this->guard : [&]() -> auto { return true; });
            const js::any isValid = guard(key, attr);
            if (!isValid) {
                        return this;
            }
            const js::any value = (js::null ? js::null : js::null);
            if (!this->tracker) {
                        return Map::set(key, value);
            }
            if (this->localId === js::null) {
                        {
                                        js::console.warn("Item attributes are missing a valid localId. Changes can't be tracked."_S);
                                        return Map::set(key, value);
                        }
            }
            js::any itemChanges = this->tracker.get(this->localId);
            if (!itemChanges) {
                        {
                                        itemChanges = []() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("type", "modified"_S);
                                              obj_temp_0.set("added", []() {
                                              js::object obj_temp_1;
                                              return js::any(obj_temp_1);
                                            }());
                                              obj_temp_0.set("deleted", js::array<js::any>{});
                                              obj_temp_0.set("modified", []() {
                                              js::object obj_temp_2;
                                              return js::any(obj_temp_2);
                                            }());
                                              return js::any(obj_temp_0);
                                            }();
                                        this->tracker.set(this->localId, itemChanges);
                        }
            }
            if (itemChanges->type === "added"_S) {
                        {
                                        itemChanges->data->key = value;
                        }
            } else {
                        if (itemChanges->type === "modified"_S) {
                                        {
                                                            if (this->has(key)) {
                                                                                    {
                                                                                                                itemChanges->modified->key = value;
                                                                                    }
                                                            } else {
                                                                                    if (itemChanges->deleted.includes(key)) {
                                                                                                                {
                                                                                                                                                itemChanges->deleted = itemChanges->deleted.filter([&](auto k) -> auto { return k !== key; });
                                                                                                                                                itemChanges->modified->key = value;
                                                                                                                }
                                                                                    } else {
                                                                                                                {
                                                                                                                                                itemChanges->added->key = value;
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            return Map::set(key, value);
    }
}

auto ItemAttributes::setValue(js::string key, js::any value) {
    {
            return this->set(key, []() {
                  js::object obj_temp_3;
                  obj_temp_3.set("value", value);
                  obj_temp_3.set("type", this->getType(key));
                  return js::any(obj_temp_3);
                }());
    }
}

auto ItemAttributes::setType(js::string key, js::number type) {
    {
            const js::any value = this->getValue(key);
            if (!value) {
                        return this;
            }
            return this->set(key, []() {
                  js::object obj_temp_4;
                  obj_temp_4.set("value", value);
                  obj_temp_4.set("type", type);
                  return js::any(obj_temp_4);
                }());
    }
}

auto ItemAttributes::delete(js::string key) {
    {
            if (!this->tracker) {
                        return Map::delete(key);
            }
            const js::any localId = this->get("localId"_S);
            if ((localId === js::undefined || js::typeof_op(localId) !== "number"_S)) {
                        {
                                        js::console.warn("Item attributes are missing a valid localId. Changes can't be tracked."_S);
                                        if (key === "localId"_S) {
                                                            return false;
                                        }
                                        return Map::delete(key);
                        }
            }
            if (key === "localId"_S) {
                        return false;
            }
            if (!this->has(key)) {
                        return false;
            }
            js::any itemChanges = this->tracker.get(localId);
            if (!itemChanges) {
                        {
                                        itemChanges = []() {
                                              js::object obj_temp_5;
                                              obj_temp_5.set("type", "modified"_S);
                                              obj_temp_5.set("added", []() {
                                              js::object obj_temp_6;
                                              return js::any(obj_temp_6);
                                            }());
                                              obj_temp_5.set("deleted", js::array<js::any>{});
                                              obj_temp_5.set("modified", []() {
                                              js::object obj_temp_7;
                                              return js::any(obj_temp_7);
                                            }());
                                              return js::any(obj_temp_5);
                                            }();
                                        this->tracker.set(localId, itemChanges);
                        }
            }
            if (itemChanges->type === "added"_S) {
                        {
                                        js::delete_property(itemChanges->data, js::toString(key));
                        }
            } else {
                        if (itemChanges->type === "modified"_S) {
                                        {
                                                            if (js::in_op(key, itemChanges->added)) {
                                                                                    {
                                                                                                                js::delete_property(itemChanges->added, js::toString(key));
                                                                                    }
                                                            } else {
                                                                                    if (js::in_op(key, itemChanges->modified)) {
                                                                                                                {
                                                                                                                                                js::delete_property(itemChanges->modified, js::toString(key));
                                                                                                                                                itemChanges->deleted.push(key);
                                                                                                                }
                                                                                    } else {
                                                                                                                {
                                                                                                                                                itemChanges->deleted.push(key);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            return Map::delete(key);
    }
}

auto ItemAttributes::getValue(js::string key) {
    {
            const js::any data = this->get(key);
            if (!data) {
                        return js::null;
            }
            return data->value;
    }
}

auto ItemAttributes::getType(js::string key) {
    {
            return this->get(key).type;
    }
}
