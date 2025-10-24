#include "index_generated.h"
#include "item.h"

using namespace js;

Item::Item(FragmentsModel model, Identifier id) {
    {
            this->model = model;
            if (js::typeof_op(id) === "number"_S) {
                        this->_localId = id;
            }
            if (js::typeof_op(id) === "string"_S) {
                        this->_guid = id;
            }
    }
}

auto Item::getLocalId() {
    {
            if (!this->_localId) {
                        {
                                        if (this->_guid) {
                                                            {
                                                                                    js::array<js::any>{this->_localId} = co_await this->model.threads.invoke(this->model.modelId, "getLocalIdsByGuids"_S, js::array<js::any>{js::array<js::any>{this->_guid}});
                                                            }
                                        } else {
                                                            {
                                                                                    throw js::any(js::Error("Fragments: Item localId couldn't be get."_S));
                                                            }
                                        }
                        }
            }
            return this->_localId;
    }
}

auto Item::getAttributes() {
        {
                if (this->_attributes) {
                            return this->_attributes;
                }
                const js::any localId = co_await this->getLocalId();
                if (localId === js::null) {
                            return js::null;
                }
                const js::any data = co_await this->model.threads.invoke(this->model.modelId, "getItemAttributes"_S, js::array<js::any>{localId});
                this->_attributes = std::make_shared<ItemAttributes>(localId);
                if (!data) {
                            {
                                            const js::any changes = this->model.attrsChanges.get(localId);
                                            if (!(changes && changes["type"] === "added"_S)) {
                                                                return js::null;
                                            }
                                            this->_attributes.localId = localId;
                                            for (const auto& js::undefined : js::Object::entries(changes["data"])) {
                                                                this->_attributes.set(key, value);
                                            }
                                            return this->_attributes;
                            }
                }
                const js::any changes = this->model.attrsChanges.get(localId);
                if ((changes && changes["type"] === "modified"_S)) {
                            {
                                            for (const auto& js::undefined : js::Object::entries(changes["added"])) {
                                                                this->_attributes.set(key, value);
                                            }
                            }
                }
                    for (auto& name_pair : js::Object::entries(data)) {
                                auto name = name_pair.first;
                                    {
                                                        auto _temp185 = data->name;
                                                        const auto value = _temp185["value"];
                                                        const auto type = _temp185["type"];
                                                        if ((changes["type"] === "modified"_S && changes["deleted"].includes(name))) {
                                                                                continue;
                                                        }
                                                        if ((changes["type"] === "modified"_S && js::in_op(name, changes["modified"]))) {
                                                                                {
                                                                                                            this->_attributes.set(name, changes["modified"][name]);
                                                                                }
                                                        } else {
                                                                                {
                                                                                                            this->_attributes.set(name, []() {
                                                                                                                  js::object obj_temp_0;
                                                                                                                  obj_temp_0.set("value", value);
                                                                                                                  obj_temp_0.set("type", type);
                                                                                                                  return js::any(obj_temp_0);
                                                                                                                }());
                                                                                }
                                                        }
                                    }
                    }
                    this->_attributes.tracker = this->model.attrsChanges;
                    return this->_attributes;
        }
}

auto Item::getRelations() {
        {
                    if (this->_relations) {
                                    return this->_relations;
                    }
                    const js::any localId = co_await this->getLocalId();
                    if (localId === js::null) {
                                    return js::null;
                    }
                    const js::any data = co_await this->model.threads.invoke(this->model.modelId, "getItemRelations"_S, js::array<js::any>{localId});
                    if (!data) {
                                    return js::null;
                    }
                    this->_relations = std::make_shared<ItemRelations>(localId);
                    this->_relations.onItemsRequested = [&](auto ids) -> auto {
                    js::array<Item> items = js::array<js::any>{};
                    for (const auto& id : ids) {
                                    {
                                                        const js::any item = this->model.getItem(id);
                                                        if (!item) {
                                                                                continue;
                                                        }
                                                        items.push(item);
                                    }
                    }
                    return items;
                    };
                    const js::any changes = this->model.relsChanges.get(localId);
                    if ((changes && changes["type"] === "modified"_S)) {
                                    {
                                                        for (const auto& js::undefined : js::Object::entries(changes["added"])) {
                                                                                this->_relations.set(key, value);
                                                        }
                                    }
                    }
                    for (const auto& js::undefined : js::Object::entries(data)) {
                                    {
                                                        if ((changes["type"] === "modified"_S && changes["deleted"]["has"](relation))) {
                                                                                continue;
                                                        }
                                                        if ((changes["type"] === "modified"_S && js::in_op(relation, changes["modified"]))) {
                                                                                {
                                                                                                            const std::shared_ptr<Set> data = std::make_shared<Set>(js::array<js::any>().concat(changes["modified"][relation]).concat(localIds));
                                                                                                            this->_relations.set(relation, std::make_shared<Set>(data));
                                                                                }
                                                        } else {
                                                                                {
                                                                                                            this->_relations.set(relation, std::make_shared<Set>(localIds));
                                                                                }
                                                        }
                                    }
                    }
                    this->_relations.tracker = this->model.relsChanges;
                    return this->_relations;
        }
}

auto Item::getGuid() {
        {
                    if (!this->_guid) {
                                    {
                                                        const js::any localId = co_await this->getLocalId();
                                                        if (localId === js::null) {
                                                                                return js::null;
                                                        }
                                                        js::array<js::any>{this->_guid} = co_await this->model.threads.invoke(this->model.modelId, "getGuidsByLocalIds"_S, js::array<js::any>{js::array<js::any>{localId}});
                                    }
                    }
                    return this->_guid;
        }
}

auto Item::getCategory() {
        {
                    if (!this->_category) {
                                    {
                                                        const js::any localId = co_await this->getLocalId();
                                                        if (localId === js::null) {
                                                                                return js::null;
                                                        }
                                                        this->_category = co_await this->model.threads.invoke(this->model.modelId, "getItemCategory"_S, js::array<js::any>{localId});
                                    }
                    }
                    return this->_category;
        }
}

auto Item::getGeometry() {
        {
                    if (this->_geometry) {
                                    return this->_geometry;
                    }
                    const js::any localId = co_await this->getLocalId();
                    if (localId === js::null) {
                                    return js::null;
                    }
                    const std::shared_ptr<ItemGeometry> geometry = std::make_shared<ItemGeometry>(this->model, localId);
                    return geometry;
        }
}

auto Item::getData(js::array<js::number> collector) {
        {
                    const js::any localId = co_await this->getLocalId();
                    if (localId == js::null) {
                                    return []() {
                                          js::object obj_temp_1;
                                          return js::any(obj_temp_1);
                                        }();
                    }
                    collector.push(localId);
                    const js::any attrs = co_await this->getAttributes().object;
                    const js::any rels = co_await this->getRelations();
                    const Record relAttrs = []() {
                          js::object obj_temp_2;
                          return js::any(obj_temp_2);
                        }();
                    if (rels) {
                                    {
                                                        for (const auto& key : rels["keys"]()) {
                                                                                {
                                                                                                            const js::any keyItems = js::array<js::any>{};
                                                                                                            relAttrs->key = keyItems;
                                                                                                            const js::any relItems = co_await rels["getItems"](key);
                                                                                                            if (!relItems) {
                                                                                                                                            continue;
                                                                                                            }
                                                                                                            for (const auto& item : relItems) {
                                                                                                                                            {
                                                                                                                                                                                const js::any itemId = co_await item->getLocalId();
                                                                                                                                                                                if (!itemId) {
                                                                                                                                                                                                                        continue;
                                                                                                                                                                                }
                                                                                                                                                                                if (collector.find([&](auto id) -> auto { return id === itemId; }) !== js::undefined) {
                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                    continue;
                                                                                                                                                                                                                        }
                                                                                                                                                                                }
                                                                                                                                                                                collector.push(itemId);
                                                                                                                                                                                const js::any itemAttrs = co_await item->getData(collector);
                                                                                                                                                                                if (!itemAttrs) {
                                                                                                                                                                                                                        continue;
                                                                                                                                                                                }
                                                                                                                                                                                keyItems.push(itemAttrs);
                                                                                                                                            }
                                                                                                            }
                                                                                }
                                                        }
                                    }
                    }
                    const js::any data = []() {
                          js::object obj_temp_3;
                          return js::any(obj_temp_3);
                        }();
                    return data;
        }
}
