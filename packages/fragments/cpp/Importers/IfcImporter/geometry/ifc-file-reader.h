#ifndef IFC_FILE_READER_H
#define IFC_FILE_READER_H

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
#include <web-ifc.h>
#include <three.h>
#include "./geometry/geometry-processor.h"
#include "./geometry/utils.h"
#include "../../../../Schema.h"
#include "./geometry/bbox.h"
#include "../../../../Utils.h"
#include "./ifc/civil-reader.h"
#include "../../../../FragmentsModels.h"
#include "../...h"
#include "../types.h"

using namespace js;

// Forward declarations
class IfcFileReader;

class IfcFileReader {
public:
    auto wasm;
    js::any webIfcSettings;
    js::typed::Nullable<unknown> scene;
    js::typed::Nullable<Set> isolatedMeshes;
    IfcFileReader(IfcImporter _serializer);
    std::shared_ptr<std::function<void(js::any)>> onElementLoaded;
    std::shared_ptr<std::function<void(js::any)>> onGeometryLoaded;
    std::shared_ptr<std::function<void(IfcLocalTransform)>> onLocalTransformLoaded;
    std::shared_ptr<std::function<void(js::number)>> onMaxIdFound;
    std::shared_ptr<std::function<void(TransformData)>> onCoordinatesLoaded;
    std::shared_ptr<std::function<void(js::array<AlignmentData>)>> onAlignmentsLoaded;
    virtual auto load(ProcessData data);
private:
    js::typed::Nullable<unknown> _ifcAPI;
    auto _tempObject1;
    auto _tempObject2;
    auto _tempMatrix1;
    auto _previousGeometries;
    auto _previousGeometriesIDs;
    auto _previousGeometriesScales;
    auto _previousLocalTransforms;
    auto _problematicGeometries;
    auto _problematicGeometriesHashes;
    auto _coordinatesInitialized;
    auto _civilReader;
    auto _maxId;
    auto _rawCategories;
    virtual auto loadCircleExtrusionGeometry(js::number modelID, IfcElement element, js::any mesh, js::number geometryIndex, js::array<js::number> elementTransform);
    virtual auto loadShellGeometry(js::number modelID, IfcElement element, js::any mesh, js::number geometryIndex, js::array<js::number> elementTransform);
    virtual auto getScaleHash(js::any units);
    virtual auto getLocalTransform(js::array<js::number> elementTransform, js::any transformWithoutScale, IfcGeometryInstance geometryData);
    virtual auto removeScale(js::array<js::number> elements);
    virtual auto decompose(js::any transform);
    virtual auto getVolume(js::Uint32Array index, js::Float32Array pos);
    virtual auto getSignedVolumeOfTriangle(js::any p1, js::any p2, js::any p3);
    virtual auto getGeometryBuffers(js::number modelID, js::any geometryRef);
    virtual js::any crossProduct(js::any v1, js::any v2);
    virtual auto computeCircleCurveProperties(js::any point1, js::any point2, js::any point3);
};

#endif // IFC_FILE_READER_H