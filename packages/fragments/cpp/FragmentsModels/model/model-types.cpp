#include "index_generated.h"
#include "model-types.h"

using namespace js;

const js::number limitOf2Bytes = js::number(65536);

// Enum ObjectClass implementation
const js::number ObjectClass::LINE = js::number(0);
const js::number ObjectClass::SHELL = js::number(1);

js::string ObjectClass::getName(js::number key) {
    if (key.value() == js::number(0).value()) return "LINE"_S;
    if (key.value() == js::number(1).value()) return "SHELL"_S;
    return "undefined"_S;
}


// Enum TileRequestClass implementation
const js::number TileRequestClass::UPDATE = js::number(0);
const js::number TileRequestClass::CREATE = js::number(1);
const js::number TileRequestClass::DELETE = js::number(2);
const js::number TileRequestClass::FINISH = js::number(3);

js::string TileRequestClass::getName(js::number key) {
    if (key.value() == js::number(0).value()) return "UPDATE"_S;
    if (key.value() == js::number(1).value()) return "CREATE"_S;
    if (key.value() == js::number(2).value()) return "DELETE"_S;
    if (key.value() == js::number(3).value()) return "FINISH"_S;
    return "undefined"_S;
}


// Enum MultiThreadingRequestClass implementation
const js::number MultiThreadingRequestClass::CREATE_MODEL = js::number(0);
const js::number MultiThreadingRequestClass::DELETE_MODEL = js::number(1);
const js::number MultiThreadingRequestClass::EXECUTE = js::number(2);
const js::number MultiThreadingRequestClass::RAYCAST = js::number(3);
const js::number MultiThreadingRequestClass::FETCH_BOXES = js::number(4);
const js::number MultiThreadingRequestClass::REFRESH_VIEW = js::number(5);
const js::number MultiThreadingRequestClass::RECOMPUTE_MESHES = js::number(6);
const js::number MultiThreadingRequestClass::CREATE_MATERIAL = js::number(7);
const js::number MultiThreadingRequestClass::THROW_ERROR = js::number(8);

js::string MultiThreadingRequestClass::getName(js::number key) {
    if (key.value() == js::number(0).value()) return "CREATE_MODEL"_S;
    if (key.value() == js::number(1).value()) return "DELETE_MODEL"_S;
    if (key.value() == js::number(2).value()) return "EXECUTE"_S;
    if (key.value() == js::number(3).value()) return "RAYCAST"_S;
    if (key.value() == js::number(4).value()) return "FETCH_BOXES"_S;
    if (key.value() == js::number(5).value()) return "REFRESH_VIEW"_S;
    if (key.value() == js::number(6).value()) return "RECOMPUTE_MESHES"_S;
    if (key.value() == js::number(7).value()) return "CREATE_MATERIAL"_S;
    if (key.value() == js::number(8).value()) return "THROW_ERROR"_S;
    return "undefined"_S;
}


// Enum ItemConfigClass implementation
const js::number ItemConfigClass::VISIBLE = js::number(0);

js::string ItemConfigClass::getName(js::number key) {
    if (key.value() == js::number(0).value()) return "VISIBLE"_S;
    return "undefined"_S;
}


// Enum SnappingClass implementation
const js::number SnappingClass::POINT = js::number(0);
const js::number SnappingClass::LINE = js::number(1);
const js::number SnappingClass::FACE = js::number(2);

js::string SnappingClass::getName(js::number key) {
    if (key.value() == js::number(0).value()) return "POINT"_S;
    if (key.value() == js::number(1).value()) return "LINE"_S;
    if (key.value() == js::number(2).value()) return "FACE"_S;
    return "undefined"_S;
}

