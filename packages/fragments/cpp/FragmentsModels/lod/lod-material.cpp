#include "index_generated.h"
#include "lod-material.h"

using namespace js;

LodMaterial::LodMaterial(LineMaterialParameters parameters) : three::ShaderMaterial(LodHelper::newLodMaterialParams(parameters)) {
    {
            this->clipping = true;
            this->lights = false;
            this->needsUpdate = true;
    }
}
