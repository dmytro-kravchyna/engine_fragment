#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

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
#include "../../../../../Schema.h"

using namespace js;

// Forward declarations
class ShellUtils;

class ShellUtils {
public:
    ShellUtils() = default;
    auto getProfile(Shell shell, js::number id, std::optional<js::any> input = std::nullopt);
    auto getPoints(Shell shell);
    auto getProfileIndices(Shell shell, js::number profileId);
    auto getHole(Shell shell, js::number id, std::optional<js::any> input = std::nullopt);
    auto getProfilesLength(Shell shell);
    auto getHolesLength(Shell shell);
    auto getShell(Meshes meshes, js::number id);
    auto point(Shell shell, js::number id, js::any result);
    auto getNormalsOfShellProfile(Shell shell, js::array<unknown> result);
    auto computeNormalsAvg(js::any indices, js::number faceId, js::array<unknown> faceNormals, Map pointsFaces);
    auto getBuffer(Shell shell);
    auto getPointsShell(Shell shell);
private:
    auto _faceThreshold;
    auto _shell;
    auto _normalBuffer;
    auto _tempNormal;
    auto _tempPoint;
    auto _shellProfile;
    auto _bigShellProfile;
    auto _shellHole;
    auto _bigShellHole;
    auto _pointsByProfile;
    auto _v1;
    auto _v2;
    auto _v3;
    auto addNormals(js::array<js::number> pointsByProfile, js::array<unknown> faceNormals, js::any profileNormal);
    auto setupNormalBuffer(js::any indices);
    auto fetchNormalsOfProfile(Shell shell, js::any profile);
    auto fetchAllPointsByHole(Shell shell);
    auto computeProfileNormal(js::number length, js::any profile, Shell shell);
    auto computeProfilePointNormal();
    auto aggregateNormals(js::typed::Nullable<js::array<js::number>> pointsByProfile, js::array<unknown> faceNormals, js::any profileNormal);
    auto fetchPointsForNormal(js::number id, js::number length, js::any profile, Shell shell);
    auto savePointByProfile(js::number index, js::number id);
    auto isTooSmall(Shell shell, js::number length);
    auto fetchAllPointsByProfile(Shell shell);
    auto computeAvgNormal(js::number id);
    auto getTempProfile(Shell shell);
    auto getTempHole(Shell shell);
};

#endif // SHELL_UTILS_H