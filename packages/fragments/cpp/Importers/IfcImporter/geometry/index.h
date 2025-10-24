#ifndef INDEX_H
#define INDEX_H

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
#include <flatbuffers.h>
#include <three.h>
#include <web-ifc.h>
#include "../../../../Schema.h"
#include "./ifc-file-reader.h"
#include "../../../../Utils.h"
#include "../../../../FragmentsModels.h"
#include "../...h"
#include "../types.h"

using namespace js;

// Forward declarations
class IfcGeometryProcessor;

// Interface GeometriesProcessData
class IGeometriesProcessData {
public:
    virtual ~IGeometriesProcessData() = default;
    // TODO: Interface members
};
class IfcGeometryProcessor {
public:
    auto wasm;
    js::any webIfcSettings;
    IfcGeometryProcessor(IfcImporter _serializer);
    virtual auto process(GeometriesProcessData data);
private:
    std::shared_ptr<IfcImporter> _serializer;
};

#endif // INDEX_H