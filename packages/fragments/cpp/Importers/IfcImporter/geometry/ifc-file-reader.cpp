#include "index_generated.h"
#include "ifc-file-reader.h"

using namespace js;

IfcFileReader::IfcFileReader(IfcImporter _serializer) {
    {
    }
}

auto IfcFileReader::load(ProcessData data) {
    {
            data->progressCallback(js::number(0), []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("process", "conversion"_S);
                  obj_temp_0.set("state", "start"_S);
                  return js::any(obj_temp_0);
                }());
            this->_previousGeometriesIDs.clear();
            this->_ifcAPI = std::make_shared<web-ifc::IfcAPI>();
            this->_ifcAPI.SetWasmPath(this->wasm.path, this->wasm.absolute);
            co_await this->_ifcAPI.Init();
            js::number modelID = js::number(0);
            if ((data->readFromCallback && data->readCallback)) {
                        {
                                        modelID = this->_ifcAPI.OpenModelFromCallback(data->readCallback, this->webIfcSettings);
                        }
            } else {
                        if (data->bytes) {
                                        {
                                                            modelID = co_await this->_ifcAPI.OpenModel(data->bytes, this->webIfcSettings);
                                        }
                        } else {
                                        {
                                                            throw js::any(js::Error("Fragments: No data provided"_S));
                                        }
                        }
            }
            this->_ifcAPI.SetLogLevel(web-ifc::LogLevel.LOG_LEVEL_OFF);
            this->_maxId = this->_ifcAPI.GetMaxExpressID(modelID);
            this->onLocalTransformLoaded([]() {
                  js::object obj_temp_1;
                  obj_temp_1.set("id", js::number(0));
                  obj_temp_1.set("data", js::array<js::number>{js::number(0), js::number(0), js::number(0), js::number(1), js::number(0), js::number(0), js::number(0), js::number(1), js::number(0)});
                  return js::any(obj_temp_1);
                }());
            const std::shared_ptr<three::Vector3> tempPosition = std::make_shared<three::Vector3>();
            const js::any callback = [&](js::any mesh) -> auto {
            if (this->_ifcAPI === js::null) {
                        {
                                        throw js::any(js::Error("Fragments: IfcAPI not initialized"_S));
                        }
            }
            if (!this->_coordinatesInitialized) {
                        {
                                        const js::any coordinates = this->_ifcAPI.GetCoordinationMatrix(modelID);
                                        this->_tempMatrix1.fromArray(coordinates);
                                        const js::any coordinatesData = this->decompose(this->_tempMatrix1);
                                        this->onCoordinatesLoaded(coordinatesData);
                                        this->_coordinatesInitialized = true;
                        }
            }
            const js::any properties = this->_ifcAPI.GetLine(js::number(0), mesh["expressID"]);
            const IfcElement element = []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("id", mesh["expressID"]);
                  obj_temp_2.set("type", properties["type"]);
                  obj_temp_2.set("guid", properties["GlobalId"]["value"]);
                  obj_temp_2.set("geometries", js::array<js::any>{});
                  return js::any(obj_temp_2);
                }();
            const js::any geometryCount = mesh["geometries"]["size"]();
            const js::any firstGeometryRef = mesh["geometries"]["get"](js::number(0));
            const js::any transformArray = firstGeometryRef->flatTransformation;
            auto _temp2559 = this->removeScale(transformArray);
            const auto transformWithoutScale = _temp2559["transformWithoutScale"];
            const js::any distanceThreshold = this->_serializer.distanceThreshold;
            if (distanceThreshold !== js::null) {
                        {
                                        tempPosition->set(js::number(0), js::number(0), js::number(0));
                                        tempPosition->applyMatrix4(transformWithoutScale);
                                        if ((((tempPosition->x > distanceThreshold) || (tempPosition->y > distanceThreshold)) || (tempPosition->z > distanceThreshold))) {
                                                            {
                                                                                    js::console.log(("Object "_S + js::toString(element->id) + " is more than "_S + js::toString(distanceThreshold) + " meters away from the origin and will be skipped."_S));
                                                                                    return;
                                                            }
                                        }
                        }
            }
            for (js::number i = js::number(0); (i < geometryCount); i++) {
                        {
                                        if (element->type === web-ifc::IFCREINFORCINGBAR) {
                                                            {
                                                                                    this->loadCircleExtrusionGeometry(modelID, element, mesh, i, transformWithoutScale->elements);
                                                            }
                                        } else {
                                                            {
                                                                                    this->loadShellGeometry(modelID, element, mesh, i, transformWithoutScale->elements);
                                                            }
                                        }
                        }
            }
            auto _temp107 = this->decompose(transformWithoutScale);
            const auto dxx = _temp107["dxx"];
            const auto dxy = _temp107["dxy"];
            const auto dxz = _temp107["dxz"];
            const auto dyx = _temp107["dyx"];
            const auto dyy = _temp107["dyy"];
            const auto dyz = _temp107["dyz"];
            const auto px = _temp107["px"];
            const auto py = _temp107["py"];
            const auto pz = _temp107["pz"];
            if ((element->geometries.length() > js::number(0))) {
                        {
                                        this->onElementLoaded([]() {
                                              js::object obj_temp_3;
                                              obj_temp_3.set("element", element);
                                              obj_temp_3.set("position", js::array<js::any>{px, py, pz});
                                              obj_temp_3.set("xDirection", js::array<js::any>{dxx, dxy, dxz});
                                              obj_temp_3.set("yDirection", js::array<js::any>{dyx, dyy, dyz});
                                              return js::any(obj_temp_3);
                                            }());
                        }
            }
            };
            if (this->isolatedMeshes.size) {
                        {
                                        this->_ifcAPI.StreamMeshes(modelID, js::array.from(this->isolatedMeshes), callback);
                        }
            } else {
                        {
                                        const js::any modelClasses = this->_ifcAPI.GetAllTypesOfModel(modelID).map([&](auto entry) -> auto { return entry["typeID"]; });
                                        const js::any toProcess = modelClasses.filter([&](auto type) -> auto { return this->_serializer.classes.elements.has(type); });
                                        const js::number categoryPercentage = (js::number(0.5) / toProcess.length());
                                        for (const auto& js::undefined : toProcess->entries()) {
                                                            {
                                                                                    const js::any state = [&]() -> auto {
                                                                                    if (index === js::number(0)) {
                                                                                                                return "start"_S;
                                                                                    }
                                                                                    if ((index + js::number(1)) === toProcess.length()) {
                                                                                                                return "finish"_S;
                                                                                    }
                                                                                    return "inProgress"_S;
                                                                                    }();
                                                                                    const js::any idsVector = this->_ifcAPI.GetLineIDsWithType(modelID, category);
                                                                                    js::array<js::number> ids = js::array<js::any>{};
                                                                                    for (js::number i = js::number(0); (i < idsVector->size()); i++) {
                                                                                                                {
                                                                                                                                                ids.push(idsVector->get(i));
                                                                                                                }
                                                                                    }
                                                                                    if ((ids.length() > js::number(0))) {
                                                                                                                {
                                                                                                                                                this->_ifcAPI.StreamMeshes(modelID, ids, callback);
                                                                                                                                                data->progressCallback((categoryPercentage * (index + js::number(1))), []() {
                                                                                                                                                      js::object obj_temp_4;
                                                                                                                                                      obj_temp_4.set("process", "geometries"_S);
                                                                                                                                                      obj_temp_4.set("state", state);
                                                                                                                                                      obj_temp_4.set("class", ifcCategoryMap->category);
                                                                                                                                                      obj_temp_4.set("entitiesProcessed", ids.length());
                                                                                                                                                      return js::any(obj_temp_4);
                                                                                                                                                    }());
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            const js::any alignments = this->_civilReader.read(this->_ifcAPI);
            this->onAlignmentsLoaded(alignments);
            this->onMaxIdFound(this->_maxId);
            this->_ifcAPI.Dispose();
            this->_ifcAPI = js::null;
            this->_ifcAPI = std::make_shared<web-ifc::IfcAPI>();
            this->_ifcAPI.SetWasmPath(this->wasm.path, this->wasm.absolute);
            co_await this->_ifcAPI.Init();
            this->_previousGeometries.clear();
            this->_previousGeometriesIDs.clear();
            this->_previousGeometriesScales.clear();
            this->_maxId = js::number(0);
            this->_previousLocalTransforms.clear();
            this->_problematicGeometries.clear();
            this->_problematicGeometriesHashes.clear();
    }
}

auto IfcFileReader::loadCircleExtrusionGeometry(js::number modelID, IfcElement element, js::any mesh, js::number geometryIndex, js::array<js::number> elementTransform) {
    {
            if (this->_ifcAPI === js::null) {
                        {
                                        throw js::any(js::Error("Fragments: IfcAPI not initialized"_S));
                        }
            }
            const js::any geometryRef = mesh["geometries"]["get"](geometryIndex);
            const js::any transformArray = geometryRef->flatTransformation;
            auto _temp7092 = this->removeScale(transformArray);
            const auto units = _temp7092["units"];
            auto _temp8775 = geometryRef->color;
            const auto x = _temp8775["x"];
            const auto y = _temp8775["y"];
            const auto z = _temp8775["z"];
            const auto w = _temp8775["w"];
            const IfcGeometryInstance geometryData = []() {
                  js::object obj_temp_5;
                  obj_temp_5.set("id", geometryRef->geometryExpressID);
                  obj_temp_5.set("color", js::array<js::any>{x, y, z, w});
                  obj_temp_5.set("localTransformID", js::null);
                  return js::any(obj_temp_5);
                }();
            element->geometries.push(geometryData);
            auto _temp7128 = this->removeScale(geometryRef->flatTransformation);
            const auto transformWithoutScale = _temp7128["transformWithoutScale"];
            if (this->_previousGeometriesIDs.has(geometryData->id)) {
                        {
                                        this->getLocalTransform(elementTransform, transformWithoutScale, geometryData);
                                        geometryData->id = this->_previousGeometriesIDs.get(geometryData->id);
                                        return;
                        }
            }
            this->getLocalTransform(elementTransform, transformWithoutScale, geometryData);
            const js::any geometry = this->_ifcAPI.GetGeometry(modelID, geometryData->id);
            const js::any circleExtrusion = geometry["GetSweptDiskSolid"]();
            js::array<js::array<js::number>> circleCurves = js::array<js::any>{};
            js::array<js::array<js::any>> axisPoints = js::array<js::any>{};
            const js::any axisSize = circleExtrusion->axis->size();
            for (js::number i = js::number(0); (i < axisSize); i++) {
                        {
                                        const js::any axis = circleExtrusion->axis->get(i);
                                        js::array<js::number> circleCurveTemp = js::array<js::any>{};
                                        for (js::number j = js::number(0); (j < axis["arcSegments"]["size"]()); j++) {
                                                            {
                                                                                    circleCurveTemp.push(axis["arcSegments"]["get"](j));
                                                            }
                                        }
                                        circleCurves.push(circleCurveTemp);
                                        js::array<js::any> axisTemp = js::array<js::any>{};
                                        for (js::number j = js::number(0); (j < axis["points"]["size"]()); j++) {
                                                            {
                                                                                    const js::any p = axis["points"]["get"](j);
                                                                                    axisTemp.push([]() {
                                                                                          js::object obj_temp_6;
                                                                                          obj_temp_6.set("x", (p->x * units["x"]));
                                                                                          obj_temp_6.set("y", (p->y * units["y"]));
                                                                                          obj_temp_6.set("z", (p->z * units["z"]));
                                                                                          return js::any(obj_temp_6);
                                                                                        }());
                                                            }
                                        }
                                        axisPoints.push(axisTemp);
                        }
            }
            js::array<js::number> indicesArray = js::array<js::any>{};
            js::array<js::number> typesArray = js::array<js::any>{};
            js::array<js::array<js::number>> segments = js::array<js::any>{};
            js::array<js::array<js::number>> circleCurveData = js::array<js::any>{};
            for (js::number i = js::number(0); (i < axisPoints.length()); i++) {
                        {
                                        js::array<js::any> axisPointsList = axisPoints->i;
                                        js::array<js::number> curves = circleCurves->i;
                                        const js::any pointsSize = axisPointsList.length();
                                        for (js::number j = js::number(0); (j < (pointsSize - js::number(1))); j++) {
                                                            {
                                                                                    js::any startCircleCurve = -js::number(1);
                                                                                    js::any endCircleCurve = -js::number(1);
                                                                                    for (js::number k = js::number(0); (k < curves.length()); k += js::number(2)) {
                                                                                                                {
                                                                                                                                                if (curves[k] === j) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            startCircleCurve = j;
                                                                                                                                                                                                                            endCircleCurve = curves[(k + js::number(1))];
                                                                                                                                                                                                                            break;
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                                                    if (startCircleCurve === -js::number(1)) {
                                                                                                                {
                                                                                                                                                js::array<js::number> newSegment = js::array<js::any>{};
                                                                                                                                                const js::any currentPoint = axisPointsList->j;
                                                                                                                                                const js::any nextPoint = axisPointsList->(j + js::number(1));
                                                                                                                                                const js::any currentX = currentPoint->x;
                                                                                                                                                const js::any currentY = currentPoint->y;
                                                                                                                                                const js::any currentZ = currentPoint->z;
                                                                                                                                                const js::any nextX = nextPoint->x;
                                                                                                                                                const js::any nextY = nextPoint->y;
                                                                                                                                                const js::any nextZ = nextPoint->z;
                                                                                                                                                indicesArray.push(segments.length());
                                                                                                                                                newSegment.push(currentX, currentY, currentZ, nextX, nextY, nextZ);
                                                                                                                                                segments.push(newSegment);
                                                                                                                                                typesArray.push(../../../../Schema::AxisPartClass.WIRE);
                                                                                                                }
                                                                                    } else {
                                                                                                                {
                                                                                                                                                js::array<js::number> newCircleCurve = js::array<js::any>{};
                                                                                                                                                const js::any firstPointIndex = startCircleCurve;
                                                                                                                                                const js::any midPointIndex = js::Math::round(((startCircleCurve + endCircleCurve) / js::number(2)));
                                                                                                                                                const js::any lastPointIndex = endCircleCurve;
                                                                                                                                                const js::any point1 = axisPointsList->firstPointIndex;
                                                                                                                                                const js::any point2 = axisPointsList->midPointIndex;
                                                                                                                                                const js::any point3 = axisPointsList->lastPointIndex;
                                                                                                                                                const js::any circleCurveProperties = this->computeCircleCurveProperties(point1, point2, point3);
                                                                                                                                                const js::number dx = (point1["x"] - circleCurveProperties->center->x);
                                                                                                                                                const js::number dy = (point1["y"] - circleCurveProperties->center->y);
                                                                                                                                                const js::number dz = (point1["z"] - circleCurveProperties->center->z);
                                                                                                                                                js::any dd = js::Math::sqrt((((dx * dx) + (dy * dy)) + (dz * dz)));
                                                                                                                                                if (dd === js::number(0)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            dd = js::number(1);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                const js::number dx1 = (dx / dd);
                                                                                                                                                const js::number dy1 = (dy / dd);
                                                                                                                                                const js::number dz1 = (dz / dd);
                                                                                                                                                const js::number dxb = (point2["x"] - circleCurveProperties->center->x);
                                                                                                                                                const js::number dyb = (point2["y"] - circleCurveProperties->center->y);
                                                                                                                                                const js::number dzb = (point2["z"] - circleCurveProperties->center->z);
                                                                                                                                                js::any dd2 = js::Math::sqrt((((dxb * dxb) + (dyb * dyb)) + (dzb * dzb)));
                                                                                                                                                if (dd2 === js::number(0)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            dd2 = js::number(1);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                const js::number dx2 = (dxb / dd2);
                                                                                                                                                const js::number dy2 = (dyb / dd2);
                                                                                                                                                const js::number dz2 = (dzb / dd2);
                                                                                                                                                js::any v3 = this->crossProduct([]() {
                                                                                                                                                      js::object obj_temp_7;
                                                                                                                                                      obj_temp_7.set("x", dx1);
                                                                                                                                                      obj_temp_7.set("y", dy1);
                                                                                                                                                      obj_temp_7.set("z", dz1);
                                                                                                                                                      return js::any(obj_temp_7);
                                                                                                                                                    }(), []() {
                                                                                                                                                      js::object obj_temp_8;
                                                                                                                                                      obj_temp_8.set("x", dx2);
                                                                                                                                                      obj_temp_8.set("y", dy2);
                                                                                                                                                      obj_temp_8.set("z", dz2);
                                                                                                                                                      return js::any(obj_temp_8);
                                                                                                                                                    }());
                                                                                                                                                dd = js::Math::sqrt((((v3["x"] * v3["x"]) + (v3["y"] * v3["y"])) + (v3["z"] * v3["z"])));
                                                                                                                                                if (dd === js::number(0)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            dd = js::number(1);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                v3 = []() {
                                                                                                                                                      js::object obj_temp_9;
                                                                                                                                                      obj_temp_9.set("x", (v3["x"] / dd));
                                                                                                                                                      obj_temp_9.set("y", (v3["y"] / dd));
                                                                                                                                                      obj_temp_9.set("z", (v3["z"] / dd));
                                                                                                                                                      return js::any(obj_temp_9);
                                                                                                                                                    }();
                                                                                                                                                indicesArray.push(circleCurveData.length());
                                                                                                                                                newCircleCurve.push(circleCurveProperties->center->x, circleCurveProperties->center->y, circleCurveProperties->center->z, circleCurveProperties->radius, circleCurveProperties->angle, dx1, dy1, dz1, v3["x"], v3["y"], v3["z"]);
                                                                                                                                                circleCurveData.push(newCircleCurve);
                                                                                                                                                typesArray.push(../../../../Schema::AxisPartClass.CIRCLE_CURVE);
                                                                                                                                                j = (lastPointIndex - js::number(1));
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            const js::any buffers = this->getGeometryBuffers(modelID, geometryRef);
            if (buffers === js::null) {
                        {
                                        js::console.log(("Zero length geometry: "_S + js::toString(geometryData->id)));
                                        element->geometries.pop();
                                        this->_problematicGeometries.add(geometryData->id);
                                        return;
                        }
            }
            auto _temp670 = buffers;
            const auto position = _temp670["position"];
            for (js::number i = js::number(0); (i < (position.length() - js::number(2))); i += js::number(3)) {
                        {
                                        position[i] *= units["x"];
                                        position[(i + js::number(1))] *= units["y"];
                                        position[(i + js::number(2))] *= units["z"];
                        }
            }
            const js::any bbox = getAABB(position);
            const js::number radius = (circleExtrusion->profileRadius * units["x"]);
            this->_previousGeometriesIDs.set(geometryData->id, geometryData->id);
            this->onGeometryLoaded([]() {
                  js::object obj_temp_10;
                  obj_temp_10.set("id", geometryData->id);
                  obj_temp_10.set("geometry", []() {
                  js::object obj_temp_11;
                  obj_temp_11.set("type", ../../../../Schema::RepresentationClass.CIRCLE_EXTRUSION);
                  obj_temp_11.set("indicesArray", indicesArray);
                  obj_temp_11.set("typesArray", typesArray);
                  obj_temp_11.set("segments", segments);
                  obj_temp_11.set("circleCurveData", circleCurveData);
                  obj_temp_11.set("radius", radius);
                  obj_temp_11.set("bbox", bbox);
                  return js::any(obj_temp_11);
                }());
                  return js::any(obj_temp_10);
                }());
            geometry["delete"]();
    }
}

auto IfcFileReader::loadShellGeometry(js::number modelID, IfcElement element, js::any mesh, js::number geometryIndex, js::array<js::number> elementTransform) {
    {
            if (this->_ifcAPI === js::null) {
                        {
                                        throw js::any(js::Error("Fragments: IfcAPI not initialized"_S));
                        }
            }
            const js::any geometryRef = mesh["geometries"]["get"](geometryIndex);
            const js::any transformArray = geometryRef->flatTransformation;
            auto _temp3643 = this->removeScale(transformArray);
            const auto units = _temp3643["units"];
            if (this->_problematicGeometries.has(geometryRef->geometryExpressID)) {
                        {
                                        js::console.log((" Problematic geometry: "_S + js::toString(geometryRef->geometryExpressID)));
                                        return;
                        }
            }
            auto _temp9864 = geometryRef->color;
            const auto x = _temp9864["x"];
            const auto y = _temp9864["y"];
            const auto z = _temp9864["z"];
            const auto w = _temp9864["w"];
            const IfcGeometryInstance geometryData = []() {
                  js::object obj_temp_12;
                  obj_temp_12.set("id", geometryRef->geometryExpressID);
                  obj_temp_12.set("color", js::array<js::any>{x, y, z, w});
                  obj_temp_12.set("localTransformID", js::null);
                  return js::any(obj_temp_12);
                }();
            element->geometries.push(geometryData);
            auto _temp4240 = this->removeScale(geometryRef->flatTransformation);
            const auto transformWithoutScale = _temp4240["transformWithoutScale"];
            if (this->_previousGeometriesIDs.has(geometryData->id)) {
                        {
                                        const js::any scaleHash = this->getScaleHash(units);
                                        const js::any previousScaleHash = this->_previousGeometriesScales.get(geometryData->id);
                                        const js::any sameScale = previousScaleHash === scaleHash;
                                        if (sameScale) {
                                                            {
                                                                                    this->getLocalTransform(elementTransform, transformWithoutScale, geometryData);
                                                                                    geometryData->id = this->_previousGeometriesIDs.get(geometryData->id);
                                                                                    return;
                                                            }
                                        }
                                        const js::any newId = ++this->_maxId;
                                        this->_previousGeometriesScales.set(newId, scaleHash);
                                        geometryData->id = newId;
                        }
            }
            const js::any buffers = this->getGeometryBuffers(modelID, geometryRef);
            if (buffers === js::null) {
                        {
                                        js::console.log(("Zero length geometry: "_S + js::toString(geometryData->id)));
                                        element->geometries.pop();
                                        this->_problematicGeometries.add(geometryData->id);
                                        return;
                        }
            }
            auto _temp3835 = buffers;
            const auto position = _temp3835["position"];
            const auto normals = _temp3835["normals"];
            const auto index = _temp3835["index"];
            for (js::number i = js::number(0); (i < (position.length() - js::number(2))); i += js::number(3)) {
                        {
                                        position[i] *= units["x"];
                                        position[(i + js::number(1))] *= units["y"];
                                        position[(i + js::number(2))] *= units["z"];
                        }
            }
            const js::number vertexCount = (position.length() / js::number(3));
            const js::number triangleCount = (index.length() / js::number(3));
            js::number biggestArea = js::number(0);
            js::number areaSum = js::number(0);
            const std::shared_ptr<three::Triangle> triangle = std::make_shared<three::Triangle>();
            const std::shared_ptr<three::Vector3> v1 = std::make_shared<three::Vector3>();
            const std::shared_ptr<three::Vector3> v2 = std::make_shared<three::Vector3>();
            const std::shared_ptr<three::Vector3> v3 = std::make_shared<three::Vector3>();
            const js::any volume = this->getVolume(index, position);
            const std::shared_ptr<three::Vector3> centroid = std::make_shared<three::Vector3>();
            for (js::number i = js::number(0); (i < (index.length() - js::number(2))); i += js::number(3)) {
                        {
                                        const js::any i1 = index[i];
                                        const js::any i2 = index[(i + js::number(1))];
                                        const js::any i3 = index[(i + js::number(2))];
                                        v1["set"](position[(i1 * js::number(3))], position[((i1 * js::number(3)) + js::number(1))], position[((i1 * js::number(3)) + js::number(2))]);
                                        v2["set"](position[(i2 * js::number(3))], position[((i2 * js::number(3)) + js::number(1))], position[((i2 * js::number(3)) + js::number(2))]);
                                        v3["set"](position[(i3 * js::number(3))], position[((i3 * js::number(3)) + js::number(1))], position[((i3 * js::number(3)) + js::number(2))]);
                                        centroid["add"](v1);
                                        centroid["add"](v2);
                                        centroid["add"](v3);
                                        triangle->set(v1, v2, v3);
                                        const js::any area = triangle->getArea();
                                        if ((area > biggestArea)) {
                                                            {
                                                                                    biggestArea = area;
                                                            }
                                        }
                                        areaSum += area;
                        }
            }
            centroid["divideScalar"](index.length());
            v1["set"](position[js::number(0)], position[js::number(1)], position[js::number(2)]);
            v2["set"](position[js::number(3)], position[js::number(4)], position[js::number(5)]);
            v3["set"](position[js::number(6)], position[js::number(7)], position[js::number(8)]);
            const js::number p = js::number(10000);
            const js::any hashAreaSum = round(areaSum, p);
            const js::any hashBigArea = round(biggestArea, p);
            const js::any hashVolume = round(volume, p);
            const js::any x1 = round(v1["x"], p);
            const js::any y1 = round(v1["y"], p);
            const js::any z1 = round(v1["z"], p);
            const js::any cx = round(centroid["x"], p);
            const js::any cy = round(centroid["x"], p);
            const js::any cz = round(centroid["x"], p);
            const js::any hash = (js::toString(vertexCount) + "-"_S + js::toString(triangleCount) + "-"_S + js::toString(hashAreaSum) + "-"_S + js::toString(hashBigArea) + "-"_S + js::toString(hashVolume) + "-"_S + js::toString(cx) + "-"_S + js::toString(cy) + "-"_S + js::toString(cz) + "-"_S + js::toString(x1) + "-"_S + js::toString(y1) + "-"_S + js::toString(z1));
            if (this->_problematicGeometriesHashes.has(hash)) {
                        {
                                        js::console.log(("Problematic geometry: "_S + js::toString(geometryData->id)));
                                        element->geometries.pop();
                                        this->_problematicGeometries.add(geometryData->id);
                                        this->_problematicGeometriesHashes.add(hash);
                                        return;
                        }
            }
            const js::any isNewGeometry = !this->_previousGeometries.has(hash);
            const js::any geomID = geometryData->id;
            if (isNewGeometry) {
                        {
                                        this->_previousGeometries.set(hash, geomID);
                                        this->_previousGeometriesIDs.set(geomID, geomID);
                        }
            } else {
                        {
                                        const js::any previousGeometryID = this->_previousGeometries.get(hash);
                                        if (previousGeometryID === js::undefined) {
                                                            {
                                                                                    throw js::any(js::Error("Fragments: Previous geometry not found"_S));
                                                            }
                                        }
                                        this->_previousGeometriesIDs.set(geomID, previousGeometryID);
                                        geometryData->id = previousGeometryID;
                        }
            }
            this->getLocalTransform(elementTransform, transformWithoutScale, geometryData);
            const js::any raw = this->_rawCategories.has(element->type);
            if (isNewGeometry) {
                        {
                                        try {
                                                            const js::any geomData = getShellData([]() {
                                                                  js::object obj_temp_13;
                                                                  obj_temp_13.set("position", position);
                                                                  obj_temp_13.set("normals", normals);
                                                                  obj_temp_13.set("index", index);
                                                                  obj_temp_13.set("raw", raw);
                                                                  return js::any(obj_temp_13);
                                                                }());
                                                            this->onGeometryLoaded([]() {
                                                                  js::object obj_temp_14;
                                                                  obj_temp_14.set("id", geometryData->id);
                                                                  obj_temp_14.set("geometry", geomData);
                                                                  return js::any(obj_temp_14);
                                                                }());
                                        } catch (const js::any& error) {
                                                            js::console.error(("Fragments: Problematic geometry: "_S + js::toString(geometryData->id)));
                                                            element->geometries.pop();
                                                            this->_problematicGeometries.add(geometryData->id);
                                                            this->_problematicGeometriesHashes.add(hash);
                                        }
                        }
            }
    }
}

auto IfcFileReader::getScaleHash(js::any units) {
    {
            return (js::toString(units["x"]) + "-"_S + js::toString(units["y"]) + "-"_S + js::toString(units["z"]));
    }
}

auto IfcFileReader::getLocalTransform(js::array<js::number> elementTransform, js::any transformWithoutScale, IfcGeometryInstance geometryData) {
    {
            this->_tempObject1.position.set(js::number(0), js::number(0), js::number(0));
            this->_tempObject1.rotation.set(js::number(0), js::number(0), js::number(0));
            this->_tempObject1.scale.set(js::number(1), js::number(1), js::number(1));
            this->_tempObject1.updateMatrix();
            this->_tempMatrix1.fromArray(elementTransform);
            this->_tempObject1.applyMatrix4(this->_tempMatrix1);
            this->_tempObject2.position.set(js::number(0), js::number(0), js::number(0));
            this->_tempObject2.rotation.set(js::number(0), js::number(0), js::number(0));
            this->_tempObject2.scale.set(js::number(1), js::number(1), js::number(1));
            this->_tempObject2.updateMatrix();
            this->_tempObject2.applyMatrix4(transformWithoutScale);
            this->_tempObject1.attach(this->_tempObject2);
            auto _temp8636 = this->decompose(this->_tempObject2.matrix);
            const auto px = _temp8636["px"];
            const auto py = _temp8636["py"];
            const auto pz = _temp8636["pz"];
            const auto dxx = _temp8636["dxx"];
            const auto dxy = _temp8636["dxy"];
            const auto dxz = _temp8636["dxz"];
            const auto dyx = _temp8636["dyx"];
            const auto dyy = _temp8636["dyy"];
            const auto dyz = _temp8636["dyz"];
            this->_tempObject2.removeFromParent();
            const js::any isOrigin = ((((((((px === js::number(0) && py === js::number(0)) && pz === js::number(0)) && dxx === js::number(1)) && dxy === js::number(0)) && dxz === js::number(0)) && dyx === js::number(0)) && dyy === js::number(1)) && dyz === js::number(0));
            if (!isOrigin) {
                        {
                                        const js::any hash = (js::toString(px) + "-"_S + js::toString(py) + "-"_S + js::toString(pz) + "-"_S + js::toString(dxx) + "-"_S + js::toString(dxy) + "-"_S + js::toString(dxz) + "-"_S + js::toString(dyx) + "-"_S + js::toString(dyy) + "-"_S + js::toString(dyz));
                                        const js::any previousLocalTransform = this->_previousLocalTransforms.get(hash);
                                        if (previousLocalTransform) {
                                                            {
                                                                                    geometryData->localTransformID = previousLocalTransform->id;
                                                            }
                                        } else {
                                                            {
                                                                                    const js::number id = (this->_previousLocalTransforms.size + js::number(1));
                                                                                    const IfcLocalTransform localTransform = []() {
                                                                                          js::object obj_temp_15;
                                                                                          obj_temp_15.set("id", id);
                                                                                          obj_temp_15.set("data", js::array<js::any>{px, py, pz, dxx, dxy, dxz, dyx, dyy, dyz});
                                                                                          return js::any(obj_temp_15);
                                                                                        }();
                                                                                    this->_previousLocalTransforms.set(hash, localTransform);
                                                                                    geometryData->localTransformID = localTransform->id;
                                                                                    this->onLocalTransformLoaded(localTransform);
                                                            }
                                        }
                        }
            }
    }
}

auto IfcFileReader::removeScale(js::array<js::number> elements) {
    {
            const js::any matrix = std::make_shared<three::Matrix4>().fromArray(elements);
            const std::shared_ptr<three::Vector3> position = std::make_shared<three::Vector3>();
            const std::shared_ptr<three::Quaternion> quaternion = std::make_shared<three::Quaternion>();
            const std::shared_ptr<three::Vector3> scale = std::make_shared<three::Vector3>();
            matrix["decompose"](position, quaternion, scale);
            const js::any units = scale;
            const std::shared_ptr<three::Matrix4> transformWithoutScale = std::make_shared<three::Matrix4>();
            transformWithoutScale->compose(position, quaternion, std::make_shared<three::Vector3>(js::number(1), js::number(1), js::number(1)));
            return []() {
                  js::object obj_temp_16;
                  obj_temp_16.set("units", units);
                  obj_temp_16.set("transformWithoutScale", transformWithoutScale);
                  return js::any(obj_temp_16);
                }();
    }
}

auto IfcFileReader::decompose(js::any transform) {
    {
            const js::number p = js::number(1000);
            const js::number ap = js::number(100000);
            const js::any dxx = round(transform["elements"][js::number(0)], p);
            const js::any dxy = round(transform["elements"][js::number(1)], p);
            const js::any dxz = round(transform["elements"][js::number(2)], p);
            const js::any dyx = round(transform["elements"][js::number(4)], ap);
            const js::any dyy = round(transform["elements"][js::number(5)], ap);
            const js::any dyz = round(transform["elements"][js::number(6)], ap);
            const js::any dzx = round(transform["elements"][js::number(8)], ap);
            const js::any dzy = round(transform["elements"][js::number(9)], ap);
            const js::any dzz = round(transform["elements"][js::number(10)], ap);
            const js::any px = round(transform["elements"][js::number(12)], ap);
            const js::any py = round(transform["elements"][js::number(13)], ap);
            const js::any pz = round(transform["elements"][js::number(14)], ap);
            return []() {
                  js::object obj_temp_17;
                  obj_temp_17.set("dxx", dxx);
                  obj_temp_17.set("dxy", dxy);
                  obj_temp_17.set("dxz", dxz);
                  obj_temp_17.set("dyx", dyx);
                  obj_temp_17.set("dyy", dyy);
                  obj_temp_17.set("dyz", dyz);
                  obj_temp_17.set("dzx", dzx);
                  obj_temp_17.set("dzy", dzy);
                  obj_temp_17.set("dzz", dzz);
                  obj_temp_17.set("px", px);
                  obj_temp_17.set("py", py);
                  obj_temp_17.set("pz", pz);
                  return js::any(obj_temp_17);
                }();
    }
}

auto IfcFileReader::getVolume(js::Uint32Array index, js::Float32Array pos) {
    {
            js::number volume = js::number(0);
            const std::shared_ptr<three::Vector3> p1 = std::make_shared<three::Vector3>();
            const std::shared_ptr<three::Vector3> p2 = std::make_shared<three::Vector3>();
            const std::shared_ptr<three::Vector3> p3 = std::make_shared<three::Vector3>();
            for (js::number i = js::number(0); (i < (index.length() - js::number(2))); i += js::number(3)) {
                        {
                                        const js::number i1 = (index[i] * js::number(3));
                                        const js::number i2 = (index[(i + js::number(1))] * js::number(3));
                                        const js::number i3 = (index[(i + js::number(2))] * js::number(3));
                                        p1["set"](pos[i1], pos[(i1 + js::number(1))], pos[(i1 + js::number(2))]);
                                        p2["set"](pos[i2], pos[(i2 + js::number(1))], pos[(i2 + js::number(2))]);
                                        p3["set"](pos[i3], pos[(i3 + js::number(1))], pos[(i3 + js::number(2))]);
                                        volume += this->getSignedVolumeOfTriangle(p1, p2, p3);
                        }
            }
            return js::Math::abs(volume);
    }
}

auto IfcFileReader::getSignedVolumeOfTriangle(js::any p1, js::any p2, js::any p3) {
    {
            const js::number v321 = ((p3["x"] * p2["y"]) * p1["z"]);
            const js::number v231 = ((p2["x"] * p3["y"]) * p1["z"]);
            const js::number v312 = ((p3["x"] * p1["y"]) * p2["z"]);
            const js::number v132 = ((p1["x"] * p3["y"]) * p2["z"]);
            const js::number v213 = ((p2["x"] * p1["y"]) * p3["z"]);
            const js::number v123 = ((p1["x"] * p2["y"]) * p3["z"]);
            return ((js::number(1) / js::number(6)) * (((((-v321 + v231) + v312) - v132) - v213) + v123));
    }
}

auto IfcFileReader::getGeometryBuffers(js::number modelID, js::any geometryRef) {
    {
            if (!this->_ifcAPI) {
                        {
                                        throw js::any(js::Error("Fragments: IfcAPI not initialized"_S));
                        }
            }
            const js::any geometry = this->_ifcAPI.GetGeometry(modelID, geometryRef->geometryExpressID);
            const js::any index = this->_ifcAPI.GetIndexArray(geometry["GetIndexData"](), geometry["GetIndexDataSize"]());
            const js::any vertexData = this->_ifcAPI.GetVertexArray(geometry["GetVertexData"](), geometry["GetVertexDataSize"]());
            if ((index.length() === js::number(0) || vertexData.length() === js::number(0))) {
                        {
                                        geometry["delete"]();
                                        return js::null;
                        }
            }
            const std::shared_ptr<Float32Array> position = std::make_shared<Float32Array>((vertexData.length() / js::number(2)));
            const std::shared_ptr<Float32Array> normals = std::make_shared<Float32Array>((vertexData.length() / js::number(2)));
            for (js::number i = js::number(0); (i < vertexData.length()); i += js::number(6)) {
                        {
                                        position[(i / js::number(2))] = vertexData->i;
                                        position[((i / js::number(2)) + js::number(1))] = vertexData->(i + js::number(1));
                                        position[((i / js::number(2)) + js::number(2))] = vertexData->(i + js::number(2));
                                        normals[(i / js::number(2))] = vertexData->(i + js::number(3));
                                        normals[((i / js::number(2)) + js::number(1))] = vertexData->(i + js::number(4));
                                        normals[((i / js::number(2)) + js::number(2))] = vertexData->(i + js::number(5));
                        }
            }
            geometry["delete"]();
            return []() {
                  js::object obj_temp_18;
                  obj_temp_18.set("position", position);
                  obj_temp_18.set("normals", normals);
                  obj_temp_18.set("index", index);
                  return js::any(obj_temp_18);
                }();
    }
}

js::any IfcFileReader::crossProduct(js::any v1, js::any v2) {
    {
            return []() {
                  js::object obj_temp_19;
                  obj_temp_19.set("x", ((v1["y"] * v2["z"]) - (v1["z"] * v2["y"])));
                  obj_temp_19.set("y", ((v1["z"] * v2["x"]) - (v1["x"] * v2["z"])));
                  obj_temp_19.set("z", ((v1["x"] * v2["y"]) - (v1["y"] * v2["x"])));
                  return js::any(obj_temp_19);
                }();
    }
}

auto IfcFileReader::computeCircleCurveProperties(js::any point1, js::any point2, js::any point3) {
    {
            js::null;
            js::null;
            js::null;
            const js::any dirAB = subtract(point2, point1);
            const js::any dirBC = subtract(point3, point2);
            const js::any normal = this->crossProduct(dirAB, dirBC);
            const js::any center = computeCircleCenter(point1, point2, point3);
            const js::any dirAcen = subtract(point1, center);
            const js::any dirBcen = subtract(point3, center);
            const js::any radius = length(subtract(center, point1));
            const js::any initialTangent = subtract(point1, center);
            const js::any tangentMagnitude = length(initialTangent);
            initialTangent->x /= tangentMagnitude;
            initialTangent->y /= tangentMagnitude;
            initialTangent->z /= tangentMagnitude;
            const js::any angle = js::Math::acos(((((dirAcen->x * dirBcen->x) + (dirAcen->y * dirBcen->y)) + (dirAcen->z * dirBcen->z)) / (length(dirAcen) * length(dirBcen))));
            return []() {
                  js::object obj_temp_20;
                  obj_temp_20.set("center", center);
                  obj_temp_20.set("radius", radius);
                  obj_temp_20.set("normal", normal);
                  obj_temp_20.set("initialTangent", initialTangent);
                  obj_temp_20.set("angle", ((angle * js::number(180)) / js::Math::PI));
                  return js::any(obj_temp_20);
                }();
    }
}
