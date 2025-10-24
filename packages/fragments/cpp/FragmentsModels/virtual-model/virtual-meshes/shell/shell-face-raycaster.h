#ifndef SHELL_FACE_RAYCASTER_H
#define SHELL_FACE_RAYCASTER_H

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
#include <earcut.h>
#include "./shell-utils.h"
#include "../../../../../Schema.h"
#include "../../../model/model-types.h"
#include "../../../utils.h"

using namespace js;

// Forward declarations
class ShellFaceRaycaster;

class ShellFaceRaycaster {
public:
    ShellFaceRaycaster(Meshes meshes);
    virtual auto faceRaycast(js::number id, js::any ray);
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
    auto j;
    auto k;
    auto tempTriangle;
    auto tempPlane;
    auto includedVertices;
    std::shared_ptr<Map> interiorProfiles;
    std::shared_ptr<Meshes> _meshes;
    virtual auto resetVectors();
    virtual auto resetData();
    virtual auto getInteriorProfiles(Shell shell);
    virtual auto processTriangle(DataBuffer indices, DataBuffer buffer, js::any ray);
    virtual auto processAllCollisions(Shell shell, DataBuffer buffer, js::any ray);
    virtual auto saveTriPoint(js::any vector, DataBuffer buffer, js::number first);
    virtual auto getIndices(Shell shell, js::number id);
    virtual auto getIsTriangle(DataBuffer indices);
    virtual auto getNormal();
    virtual auto isHole(js::number id, Shell shell, DataBuffer buffer);
    virtual auto computeNormal(DataBuffer data, DataBuffer indices);
    virtual auto holeContains(js::array<js::number> indices, Shell shell, DataBuffer data);
    virtual auto triangleHit(js::any ray);
    virtual auto getValidCollision(DataBuffer indices, DataBuffer buffer, js::any ray, js::number id, Shell shell);
    virtual auto processCollision(Shell shell, js::number profileId, DataBuffer buffer, DataBuffer indices);
    virtual auto newOrthoNormalBasis();
    virtual auto polygonContains(DataBuffer data, DataBuffer indices);
    virtual auto processNormal(DataBuffer data, js::number i1, js::number i2);
    virtual auto getCollidesPlane(DataBuffer indices, DataBuffer buffer, js::any ray);
    virtual auto setPolyContainVec(DataBuffer indices, DataBuffer data);
    virtual auto getTriangleBuffer(DataBuffer buffer, DataBuffer indices);
    virtual auto getFaceBuffer(Shell shell, js::number profileId, DataBuffer buffer);
};

#endif // SHELL_FACE_RAYCASTER_H