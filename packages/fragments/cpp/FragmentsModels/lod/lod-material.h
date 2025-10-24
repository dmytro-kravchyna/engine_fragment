#ifndef LOD_MATERIAL_H
#define LOD_MATERIAL_H

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
#include <three/examples/jsm/lines/LineMaterial.js.h>
#include "./lod-helper.h"

using namespace js;

// Forward declarations
class LodMaterial;

class LodMaterial : public three::ShaderMaterial {
public:
    auto isLodMaterial;
    auto isLineMaterial;
    LodMaterial(LineMaterialParameters parameters);
};

#endif // LOD_MATERIAL_H