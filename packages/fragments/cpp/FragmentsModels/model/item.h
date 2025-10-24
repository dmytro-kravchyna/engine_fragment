#ifndef ITEM_H
#define ITEM_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "runtime/async.h"
#include "./item-attributes.h"
#include "./item-relations.h"
#include "./item-geometry.h"
#include "./fragments-model.h"
#include "./model-types.h"

using namespace js;

// Forward declarations
class Item;

class Item {
public:
    std::shared_ptr<FragmentsModel> model;
    Item(FragmentsModel model, Identifier id);
    virtual auto getLocalId();
    virtual auto getAttributes();
    virtual auto getRelations();
    virtual auto getGuid();
    virtual auto getCategory();
    virtual auto getGeometry();
    virtual auto getData(js::array<js::number> collector = js::array<js::any>{});
private:
    js::typed::Nullable<js::number> _localId;
    js::typed::Nullable<ItemAttributes> _attributes;
    js::typed::Nullable<ItemRelations> _relations;
    js::typed::Nullable<js::string> _guid;
    js::typed::Nullable<js::string> _category;
    js::typed::Nullable<ItemGeometry> _geometry;
};

#endif // ITEM_H