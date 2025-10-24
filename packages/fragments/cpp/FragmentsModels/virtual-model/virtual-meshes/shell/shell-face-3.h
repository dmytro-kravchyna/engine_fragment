#ifndef SHELL_FACE_3_H
#define SHELL_FACE_3_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../types.h"
#include "./types.h"

using namespace js;

// Forward declarations
class ShellFace3;

class ShellFace3 {
public:
    ShellFace3() = default;
    auto create(js::any indices, js::Float32Array data, js::Int16Array normals, TileData mesh, DataSizes sizes, js::number faceId);
private:
    auto vertexIncrease;
    auto totalIncrease;
    auto setFaceIds(DataSizes sizes, TileData mesh, js::number faceId);
    auto setNormals(TileData mesh, DataSizes sizes, js::Int16Array normals);
    auto setPoints(js::any indices, TileData mesh, DataSizes sizes, js::Float32Array data);
    auto setIndices(TileData mesh, DataSizes sizes);
    auto updateData(DataSizes sizes);
};

#endif // SHELL_FACE_3_H