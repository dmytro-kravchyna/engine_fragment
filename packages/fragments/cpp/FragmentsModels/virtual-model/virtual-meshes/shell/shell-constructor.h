#ifndef SHELL_CONSTRUCTOR_H
#define SHELL_CONSTRUCTOR_H

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
#include "../../../../../Schema.h"
#include "../types.h"
#include "./types.h"
#include "./shell-utils.h"
#include "../../../model/model-types.h"
#include "./shell-face-x.h"
#include "./shell-face-4.h"
#include "./shell-face-3.h"

using namespace js;

// Forward declarations
class ShellConstructor;

class ShellConstructor {
public:
    ShellConstructor() = default;
    virtual auto construct(Shell shell, js::any meshData);
private:
    auto point;
    auto _shellHole;
    auto _bigShellHole;
    auto interiorProfiles;
    auto normalsAvgInterior;
    auto _pointsPerProfile;
    auto _shellProfile;
    auto _bigShellProfile;
    auto _normalsAvg;
    js::array<unknown> _normals;
    auto _indices;
    std::shared_ptr<DataSizes> _sizes;
    std::shared_ptr<TileData> _tileData;
    auto _nextFaceId;
    virtual auto getIntProfileNormalsAvg(Shell shell, js::number id);
    virtual auto saveInteriorProfile(Shell shell);
    virtual auto computeNormalsAvg(Shell shell, js::any indices, js::number id);
    virtual auto isShell(Shell shell);
    virtual auto getPointsPerWire(Shell shell);
    virtual auto getIndices(Shell shell, js::number id);
    virtual auto resetConstructData(AnyTileData meshData);
    virtual auto initializeIndices();
    virtual auto constructFace4(js::any indices, js::Float32Array data, js::number id);
    virtual auto initializeSizes();
    virtual auto getInteriorProfileBuffer(Shell shell, ShellHoleData intProfile);
    virtual auto constructProfile(js::number id, Shell shell, js::any indices, js::Float32Array data);
    virtual auto getIntProfileNormals(ShellHoleData hole, js::number id);
    virtual auto saveExistingInteriorProfile(js::number id);
    virtual auto getNewIntProfileData();
    virtual auto constructFace3(js::any indices, js::Float32Array data);
    virtual auto getIntProfilePoints(js::number i, Shell shell, ShellHoleData holeData);
    virtual auto manageMemory(Shell shell, js::any meshData);
    auto nextBuffer;
    virtual auto initializeFaceIds();
    virtual auto getNextFaceId();
    virtual auto newShellInteriorProfiles(Shell shell);
    virtual auto initializePositions();
    virtual auto initializeNormals();
    virtual auto setTileData(AnyTileData bufferGeometries);
    virtual auto constructShell(Shell shell, js::Float32Array data, AnyTileData meshData);
    virtual auto constructFaceX(js::any indices, js::Float32Array data, js::number id);
    virtual auto getTempProfile(Shell shell);
    virtual auto getTempHole(Shell shell);
};

#endif // SHELL_CONSTRUCTOR_H