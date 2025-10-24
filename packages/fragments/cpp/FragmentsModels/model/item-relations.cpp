#include "index_generated.h"
#include "item-relations.h"

using namespace js;

ItemRelations::ItemRelations(js::number localId, std::optional<js::any> iterable) : Map(iterable) {
    {
            this->localId = localId;
    }
}

auto ItemRelations::set(js::string key, Set value) {
    {
            const js::any keyExisted = this->has(key);
            const js::any guard = (this->guard.has_value() ? this->guard : [&]() -> auto { return true; });
            const js::any isValid = guard(key, value);
            if (!isValid) {
                        return this;
            }
            const js::any itemChanges = this->itemChanges;
            if (!itemChanges) {
                        return Map::set(key, value);
            }
            if (keyExisted) {
                        {
                                        itemChanges->modified->key = value;
                        }
            } else {
                        {
                                        itemChanges->added->key = value;
                        }
            }
            return Map::set(key, value);
    }
}

auto ItemRelations::add(js::string key, js::number item) {
    {
            const js::any keyExisted = this->has(key);
            js::any items = this->get(key);
            if (!items) {
                        {
                                        items = std::make_shared<Set>(js::array<js::any>{item});
                                        this->set(key, items);
                                        return true;
                        }
            }
            if ((!items || items["has"](item))) {
                        return false;
            }
            const js::any itemChanges = this->itemChanges;
            if (!itemChanges) {
                        {
                                        items["add"](item);
                                        return true;
                        }
            }
            if (keyExisted) {
                        {
                                        if (itemChanges->removed->key->has(item)) {
                                                            {
                                                                                    itemChanges->removed->key->delete(item);
                                                                                    if (itemChanges->removed->key->size === js::number(0)) {
                                                                                                                js::delete_property(itemChanges->removed, js::toString(key));
                                                                                    }
                                                            }
                                        } else {
                                                            {
                                                                                    js::any modificationChanges = itemChanges->modified->key;
                                                                                    if (!modificationChanges) {
                                                                                                                {
                                                                                                                                                modificationChanges = std::make_shared<Set>();
                                                                                                                                                itemChanges->modified->key = modificationChanges;
                                                                                                                }
                                                                                    }
                                                                                    modificationChanges->add(item);
                                                            }
                                        }
                        }
            } else {
                        {
                                        js::any addedChanges = itemChanges->added->key;
                                        if (!addedChanges) {
                                                            {
                                                                                    addedChanges = std::make_shared<Set>();
                                                                                    itemChanges->added->key = addedChanges;
                                                            }
                                        }
                                        addedChanges->add(item);
                        }
            }
            items["add"](item);
            return true;
    }
}

auto ItemRelations::remove(js::string key, js::number item) {
    {
            const js::any items = this->get(key);
            if (!items) {
                        return false;
            }
            if (!items["has"](item)) {
                        return false;
            }
            const js::any itemChanges = this->itemChanges;
            if (!itemChanges) {
                        return items["delete"](item);
            }
            if (itemChanges->modified->key->has(item)) {
                        {
                                        itemChanges->modified->key->delete(item);
                                        if (itemChanges->modified->key->size === js::number(0)) {
                                                            js::delete_property(itemChanges->modified, js::toString(key));
                                        }
                        }
            } else {
                        {
                                        js::any removeChanges = itemChanges->removed->key;
                                        if (!removeChanges) {
                                                            {
                                                                                    removeChanges = std::make_shared<Set>();
                                                                                    itemChanges->removed->key = removeChanges;
                                                            }
                                        }
                                        removeChanges->add(item);
                        }
            }
            return items["delete"](item);
    }
}

auto ItemRelations::delete(js::string key) {
    {
            if (!this->has(key)) {
                        return false;
            }
            const js::any itemChanges = this->itemChanges;
            if (!itemChanges) {
                        return Map::delete(key);
            }
            itemChanges->deleted->add(key);
            return Map::delete(key);
    }
}

auto ItemRelations::getItems(js::string key) {
    {
            if (!this->onItemsRequested) {
                        return js::null;
            }
            const js::any relations = this->get(key);
            if (!relations) {
                        return js::null;
            }
            const js::any items = co_await this->onItemsRequested(js::array<js::any>().concat(relations));
            return items;
    }
}
