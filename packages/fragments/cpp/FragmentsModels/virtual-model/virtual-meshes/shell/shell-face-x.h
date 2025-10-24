#ifndef SHELL_FACE_X_H
#define SHELL_FACE_X_H

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
#include "../types.h"
#include "./types.h"
#include "../../../utils/geometry/earcut.h"
#include "../../../model/model-types.h"
#include "../../../utils.h"

using namespace js;

// Forward declarations
class ShellFaceX;

class ShellFaceX {
public:
    ShellFaceX() = default;
    auto create(js::any indices, js::Float32Array data, js::Int16Array normals, js::number current, TileData mesh, Map holes, DataSizes sizes, js::number faceId);
private:
    auto _tempVec;
    auto setFaceId(js::number amount, DataSizes sizes, TileData mesh, js::number faceId);
    auto getVertices(TileData mesh, js::number amount, DataSizes sizes);
    auto getEvent(TileData mesh, DataSizes sizes, js::number amount);
    auto processBuffers(js::number size, js::any indices, TileData mesh, DataSizes sizes, js::Float32Array data, js::Int16Array normals);
    auto getHoles(Map shellHoles, js::number index, js::number size, TileData mesh, DataSizes sizes);
    auto setHolesBuffers(TileData mesh, ShellHoleData shellHole, DataSizes sizes);
    auto updateBufferData(DataSizes sizes);
    auto processPositionBuffer(TileData mesh, js::any indices, js::number id, DataSizes sizes, js::Float32Array data);
    auto triangulate(Map holes, js::number current, js::number size, TileData mesh, DataSizes sizes, js::number amount);
    auto processNormals(DataBuffer input, js::any result, js::number size, auto position = js::number(0));
    auto processNormalbuffer(TileData mesh, js::Int16Array normals, js::number id, DataSizes sizes);
};

#endif // SHELL_FACE_X_H