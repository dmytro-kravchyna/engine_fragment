#ifndef SHELL_FACE_4_H
#define SHELL_FACE_4_H

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
#include "./shell-face-x.h"

using namespace js;

// Forward declarations
class ShellFace4;

class ShellFace4 {
public:
    ShellFace4() = default;
    auto create(js::any indices, js::Float32Array data, js::Int16Array normals, js::number id, TileData mesh, DataSizes sizes, js::number faceId);
private:
    auto a;
    auto b;
    auto c;
    auto d;
    auto e;
    auto f;
    auto g;
    auto h;
    auto i;
    auto _vecs;
    auto _convexIndices;
    auto totalIncrease;
    auto indexIncrease;
    auto vertexIncrease;
    auto setAllVectors(js::any indices, js::Float32Array data);
    auto processConvexFace4(TileData mesh, DataSizes sizes, js::Int16Array normals, js::number faceId);
    auto setFaceId(TileData mesh, DataSizes sizes, js::number faceId);
    auto getIsConvex();
    auto getCrossVectors();
    auto updateData(DataSizes sizes);
    auto processPoints(TileData mesh, DataSizes sizes);
    auto setVector(js::any indices, js::Float32Array data, js::any vector, js::number offset);
    auto processNormal(TileData mesh, DataSizes sizes, js::Int16Array normals);
    auto processIndices(TileData mesh, DataSizes sizes);
};

#endif // SHELL_FACE_4_H