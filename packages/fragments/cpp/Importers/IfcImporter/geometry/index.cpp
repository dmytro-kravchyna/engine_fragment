#include "index_generated.h"
#include "index.h"

using namespace js;

IfcGeometryProcessor::IfcGeometryProcessor(IfcImporter _serializer) {
    {
            this->_serializer = _serializer;
    }
}

auto IfcGeometryProcessor::process(GeometriesProcessData data) {
    {
            auto _temp3543 = data;
            const auto builder = _temp3543["builder"];
            js::number maxLocalID = js::number(0);
            js::array<js::number> localIDs = js::array<js::any>{};
            TransformData coordinates = []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("dxx", js::number(1));
                  obj_temp_0.set("dxy", js::number(0));
                  obj_temp_0.set("dxz", js::number(0));
                  obj_temp_0.set("dyx", js::number(0));
                  obj_temp_0.set("dyy", js::number(1));
                  obj_temp_0.set("dyz", js::number(0));
                  obj_temp_0.set("px", js::number(0));
                  obj_temp_0.set("py", js::number(0));
                  obj_temp_0.set("pz", js::number(0));
                  return js::any(obj_temp_0);
                }();
            js::array<js::any> geometries = js::array<js::any>{};
            js::array<AlignmentData> alignments = js::array<js::any>{};
            js::array<js::any> items = js::array<js::any>{};
            js::array<IfcLocalTransform> localTransforms = js::array<js::any>{};
            const std::shared_ptr<Map> itemIDMap = std::make_shared<Map>();
            const std::shared_ptr<Map> geometryIDMap = std::make_shared<Map>();
            const std::shared_ptr<Map> materialIDMap = std::make_shared<Map>();
            const std::shared_ptr<IfcFileReader> reader = std::make_shared<IfcFileReader>(this->_serializer);
            reader["wasm"] = this->wasm;
            reader["webIfcSettings"] = this->webIfcSettings;
            reader["onGeometryLoaded"] = [&](auto geometry) -> auto {
            geometries.push(geometry);
            };
            reader["onElementLoaded"] = [&](auto element) -> auto {
            items.push(element);
            };
            reader["onLocalTransformLoaded"] = [&](auto localTransform) -> auto {
            localTransforms.push(localTransform);
            };
            reader["onCoordinatesLoaded"] = [&](auto coords) -> auto {
            coordinates = coords;
            };
            reader["onMaxIdFound"] = [&](auto maxId) -> auto {
            maxLocalID = maxId;
            };
            reader["onAlignmentsLoaded"] = [&](auto data) -> auto {
            for (const auto& alignment : data) {
                        {
                                        alignments.push(alignment);
                        }
            }
            };
            co_await reader["load"](data);
            js::array<js::number> geometriesItems = js::array<js::any>{};
            js::number itemCounter = js::number(0);
            ../../../../Schema::Meshes.startGlobalTransformsVector(builder, items.length());
            const std::shared_ptr<Map> itemCategories = std::make_shared<Map>();
            js::array<js::number> categoriesIds = js::array<js::any>{};
            js::array<js::number> localIds = js::array<js::any>{};
            for (js::number i = js::number(0); (i < items.length()); i++) {
                        {
                                        const js::any currentItem = items[((items.length() - js::number(1)) - i)];
                                        geometriesItems.push(itemCounter++);
                                        auto _temp1555 = currentItem;
                                        const auto position = _temp1555["position"];
                                        const auto xDirection = _temp1555["xDirection"];
                                        const auto yDirection = _temp1555["yDirection"];
                                        auto _temp5931 = position;
                                        const auto px = _temp5931[0];
                                        const auto py = _temp5931[1];
                                        const auto pz = _temp5931[2];
                                        auto _temp1704 = xDirection;
                                        const auto dxx = _temp1704[0];
                                        const auto dxy = _temp1704[1];
                                        const auto dxz = _temp1704[2];
                                        auto _temp3722 = yDirection;
                                        const auto dyx = _temp3722[0];
                                        const auto dyy = _temp3722[1];
                                        const auto dyz = _temp3722[2];
                                        localIDs.push(items[i]["element"]["id"]);
                                        const js::number itemIndex = ((items.length() - js::number(1)) - i);
                                        const js::any categoryId = currentItem->element->type;
                                        const js::any category = ifcCategoryMap->categoryId;
                                        if (!itemCategories->has(category)) {
                                                            {
                                                                                    itemCategories->set(category, itemCategories->size);
                                                            }
                                        }
                                        ../../../../Schema::Transform.createTransform(builder, px, py, pz, dxx, dxy, dxz, dyx, dyy, dyz);
                                        const js::any categoryIndex = itemCategories->get(category);
                                        categoriesIds->unshift(categoryIndex);
                                        localIds->unshift(currentItem->element->id);
                                        itemIDMap->set(currentItem->element->id, itemIndex);
                        }
            }
            const js::any globalTransforms = builder->endVector();
            js::array<js::number> shellsOffsets = js::array<js::any>{};
            for (js::number g = js::number(0); (g < geometries.length()); g++) {
                        {
                                        const js::any geometryData = geometries[g];
                                        if (geometryData->geometry->type !== ../../../../Schema::RepresentationClass.SHELL) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        auto _temp4982 = geometryData->geometry;
                                        const auto points = _temp4982["points"];
                                        const auto profiles = _temp4982["profiles"];
                                        const auto holes = _temp4982["holes"];
                                        const js::number ushortMaxValue = js::number(65000);
                                        const bool isBigShell = (points.length() > ushortMaxValue);
                                        const js::any shellType = (js::null ? js::null : js::null);
                                        ../../../../Schema::Shell.startPointsVector(builder, points.length());
                                        for (js::number i = js::number(0); (i < points.length()); i++) {
                                                            {
                                                                                    auto _temp8800 = points[((points.length() - js::number(1)) - i)];
                                                                                    const auto x = _temp8800[0];
                                                                                    const auto y = _temp8800[1];
                                                                                    const auto z = _temp8800[2];
                                                                                    ../../../../Schema::FloatVector.createFloatVector(builder, x, y, z);
                                                            }
                                        }
                                        const js::any pointsOffset = builder->endVector();
                                        js::array<js::number> profilesOffsets = js::array<js::any>{};
                                        js::array<js::number> holesOffsets = js::array<js::any>{};
                                        js::array<js::number> bigProfilesOffsets = js::array<js::any>{};
                                        js::array<js::number> bigHolesOffsets = js::array<js::any>{};
                                        for (const auto& js::undefined : profiles) {
                                                            {
                                                                                    if (isBigShell) {
                                                                                                                {
                                                                                                                                                const js::any indicesOffset = ../../../../Schema::BigShellProfile.createIndicesVector(builder, indices);
                                                                                                                                                const js::any bigProfileOffset = ../../../../Schema::BigShellProfile.createBigShellProfile(builder, indicesOffset);
                                                                                                                                                bigProfilesOffsets.push(bigProfileOffset);
                                                                                                                                                continue;
                                                                                                                }
                                                                                    }
                                                                                    const js::any indicesOffset = ../../../../Schema::ShellProfile.createIndicesVector(builder, indices);
                                                                                    const js::any profileOffset = ../../../../Schema::ShellProfile.createShellProfile(builder, indicesOffset);
                                                                                    profilesOffsets.push(profileOffset);
                                                            }
                                        }
                                        const js::any bigShellProfilesOffset = ../../../../Schema::Shell.createBigProfilesVector(builder, bigProfilesOffsets);
                                        const js::any shellProfilesOffset = ../../../../Schema::Shell.createProfilesVector(builder, profilesOffsets);
                                        for (const auto& js::undefined : holes) {
                                                            {
                                                                                    if (isBigShell) {
                                                                                                                {
                                                                                                                                                for (const auto& indices : indicesSets) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            const js::any indicesOffset = ../../../../Schema::BigShellHole.createIndicesVector(builder, indices);
                                                                                                                                                                                                                            const js::any holeOffset = ../../../../Schema::BigShellHole.createBigShellHole(builder, indicesOffset, holeId);
                                                                                                                                                                                                                            bigHolesOffsets.push(holeOffset);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                continue;
                                                                                                                }
                                                                                    }
                                                                                    for (const auto& indices : indicesSets) {
                                                                                                                {
                                                                                                                                                const js::any indicesOffset = ../../../../Schema::ShellHole.createIndicesVector(builder, indices);
                                                                                                                                                const js::any holeOffset = ../../../../Schema::ShellHole.createShellHole(builder, indicesOffset, holeId);
                                                                                                                                                holesOffsets.push(holeOffset);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                                        const js::any bigShellHolesOffset = ../../../../Schema::Shell.createBigHolesVector(builder, bigHolesOffsets);
                                        const js::any shellHolesOffset = ../../../../Schema::Shell.createHolesVector(builder, holesOffsets);
                                        const js::any shellOffset = ../../../../Schema::Shell.createShell(builder, shellProfilesOffset, shellHolesOffset, pointsOffset, bigShellProfilesOffset, bigShellHolesOffset, shellType);
                                        shellsOffsets.push(shellOffset);
                        }
            }
            const js::any shells = ../../../../Schema::Meshes.createShellsVector(builder, shellsOffsets);
            js::array<js::number> circleExtrusionsOffsets = js::array<js::any>{};
            for (js::number g = js::number(0); (g < geometries.length()); g++) {
                        {
                                        const js::any geometryData = geometries[g];
                                        if (geometryData->geometry->type !== ../../../../Schema::RepresentationClass.CIRCLE_EXTRUSION) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        js::array<js::number> axisOffsets = js::array<js::any>{};
                                        auto _temp1 = geometryData->geometry;
                                        const auto radius = _temp1["radius"];
                                        const auto indicesArray = _temp1["indicesArray"];
                                        const auto typesArray = _temp1["typesArray"];
                                        const auto segments = _temp1["segments"];
                                        const auto circleCurveData = _temp1["circleCurveData"];
                                        ../../../../Schema::Axis.startCircleCurvesVector(builder, circleCurveData.length());
                                        for (js::number i = js::number(0); (i < circleCurveData.length()); i++) {
                                                            {
                                                                                    auto _temp7519 = circleCurveData->i;
                                                                                    const auto x1 = _temp7519[0];
                                                                                    const auto y1 = _temp7519[1];
                                                                                    const auto z1 = _temp7519[2];
                                                                                    const auto radius = _temp7519[3];
                                                                                    const auto angle = _temp7519[4];
                                                                                    const auto dx1 = _temp7519[5];
                                                                                    const auto dy1 = _temp7519[6];
                                                                                    const auto dz1 = _temp7519[7];
                                                                                    const auto dx3 = _temp7519[8];
                                                                                    const auto dy3 = _temp7519[9];
                                                                                    const auto dz3 = _temp7519[10];
                                                                                    ../../../../Schema::CircleCurve.createCircleCurve(builder, (((angle / js::number(360)) * js::number(2)) * js::Math::PI), x1, y1, z1, radius, dx3, dy3, dz3, dx1, dy1, dz1);
                                                            }
                                        }
                                        const js::any circleCurvesOffset = builder->endVector();
                                        ../../../../Schema::Axis.startWiresVector(builder, segments.length());
                                        for (js::number i = js::number(0); (i < segments.length()); i++) {
                                                            {
                                                                                    auto _temp9174 = segments[i];
                                                                                    const auto x1 = _temp9174[0];
                                                                                    const auto y1 = _temp9174[1];
                                                                                    const auto z1 = _temp9174[2];
                                                                                    const auto x2 = _temp9174[3];
                                                                                    const auto y2 = _temp9174[4];
                                                                                    const auto z2 = _temp9174[5];
                                                                                    ../../../../Schema::Wire.createWire(builder, x1, y1, z1, x2, y2, z2);
                                                            }
                                        }
                                        const js::any wiresOffset = builder->endVector();
                                        const js::any ordersOffset = ../../../../Schema::Axis.createOrderVector(builder, indicesArray);
                                        const js::any axisPartsOffset = ../../../../Schema::Axis.createPartsVector(builder, typesArray);
                                        ../../../../Schema::Axis.startWireSetsVector(builder, js::number(0));
                                        const js::any wireSetOffset = builder->endVector();
                                        ../../../../Schema::Axis.startAxis(builder);
                                        ../../../../Schema::Axis.addCircleCurves(builder, circleCurvesOffset);
                                        ../../../../Schema::Axis.addOrder(builder, ordersOffset);
                                        ../../../../Schema::Axis.addWires(builder, wiresOffset);
                                        ../../../../Schema::Axis.addWireSets(builder, wireSetOffset);
                                        ../../../../Schema::Axis.addParts(builder, axisPartsOffset);
                                        const js::any axisOffset = ../../../../Schema::Axis.endAxis(builder);
                                        axisOffsets.push(axisOffset);
                                        const js::any axisVectorOffset = ../../../../Schema::CircleExtrusion.createAxesVector(builder, axisOffsets);
                                        const js::any radiusOffset = ../../../../Schema::CircleExtrusion.createRadiusVector(builder, js::array<js::any>{radius});
                                        ../../../../Schema::CircleExtrusion.startCircleExtrusion(builder);
                                        ../../../../Schema::CircleExtrusion.addAxes(builder, axisVectorOffset);
                                        ../../../../Schema::CircleExtrusion.addRadius(builder, radiusOffset);
                                        const js::any ceOffset = ../../../../Schema::CircleExtrusion.endCircleExtrusion(builder);
                                        circleExtrusionsOffsets.push(ceOffset);
                        }
            }
            const js::any circleExtrusions = ../../../../Schema::Meshes.createCircleExtrusionsVector(builder, circleExtrusionsOffsets);
            ../../../../Schema::Meshes.startRepresentationsVector(builder, geometries.length());
            const std::shared_ptr<Map> geometryClassesCounter = std::make_shared<Map>();
            for (js::number g = js::number(0); (g < geometries.length()); g++) {
                        {
                                        const js::number index = ((geometries.length() - js::number(1)) - g);
                                        const js::any currentGeometry = geometries[index];
                                        const js::any geometryClass = currentGeometry->geometry->type;
                                        js::any previousCount = geometryClassesCounter->get(geometryClass);
                                        if (previousCount === js::undefined) {
                                                            {
                                                                                    previousCount = -js::number(1);
                                                            }
                                        }
                                        geometryClassesCounter->set(geometryClass, (previousCount + js::number(1)));
                        }
            }
            const std::shared_ptr<three::Vector3> tempMin = std::make_shared<three::Vector3>();
            const std::shared_ptr<three::Vector3> tempMax = std::make_shared<three::Vector3>();
            for (js::number g = js::number(0); (g < geometries.length()); g++) {
                        {
                                        const js::number index = ((geometries.length() - js::number(1)) - g);
                                        const js::any currentGeometry = geometries[index];
                                        auto _temp2108 = currentGeometry->geometry;
                                        const auto bbox = _temp2108["bbox"];
                                        geometryIDMap->set(currentGeometry->id, index);
                                        const js::any geometryClass = currentGeometry->geometry->type;
                                        const js::any geomIndex = geometryClassesCounter->get(geometryClass);
                                        if (geomIndex === js::undefined) {
                                                            {
                                                                                    throw js::any(js::Error("Fragments: Malformed geometry definition"_S));
                                                            }
                                        }
                                        geometryClassesCounter->set(geometryClass, (geomIndex - js::number(1)));
                                        tempMin->set(bbox["min"]["x"], bbox["min"]["y"], bbox["min"]["z"]);
                                        tempMax->set(bbox["max"]["x"], bbox["max"]["y"], bbox["max"]["z"]);
                                        const js::any distance = tempMin->distanceTo(tempMax);
                                        if ((distance > js::number(999999))) {
                                                            {
                                                                                    js::console.log(("Infinity bounding box: "_S + js::toString(currentGeometry->id)));
                                                                                    bbox["min"]["x"] = js::number(0);
                                                                                    bbox["min"]["y"] = js::number(0);
                                                                                    bbox["min"]["z"] = js::number(0);
                                                                                    bbox["max"]["x"] = js::number(0.1);
                                                                                    bbox["max"]["y"] = js::number(0.1);
                                                                                    bbox["max"]["z"] = js::number(0.1);
                                                            }
                                        }
                                        ../../../../Schema::Representation.createRepresentation(builder, geomIndex, bbox["min"]["x"], bbox["min"]["y"], bbox["min"]["z"], bbox["max"]["x"], bbox["max"]["y"], bbox["max"]["z"], currentGeometry->geometry->type);
                        }
            }
            const js::any representationsOffsets = builder->endVector();
            js::number materialCounter = js::number(0);
            for (const auto& item : items) {
                        {
                                        for (const auto& geometry : item->element.geometries) {
                                                            {
                                                                                    const js::any colorID = geometry["color"].toString();
                                                                                    if (!materialIDMap->has(colorID)) {
                                                                                                                {
                                                                                                                                                const js::any color = geometry["color"].map([&](auto n) -> auto { return (n * js::number(255)); });
                                                                                                                                                materialIDMap->set(colorID, []() {
                                                                                                                                                      js::object obj_temp_1;
                                                                                                                                                      obj_temp_1.set("id", materialCounter++);
                                                                                                                                                      obj_temp_1.set("color", color);
                                                                                                                                                      return js::any(obj_temp_1);
                                                                                                                                                    }());
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            ../../../../Schema::Meshes.startMaterialsVector(builder, materialIDMap->size);
            const js::any materialMapKeys = js::array.from(materialIDMap->keys());
            for (js::number i = js::number(0); (i < materialMapKeys.length()); i++) {
                        {
                                        const js::any key = materialMapKeys->((materialMapKeys.length() - js::number(1)) - i);
                                        auto _temp1848 = materialIDMap->get(key);
                                        const auto color = _temp1848["color"];
                                        auto _temp5336 = color;
                                        const auto r = _temp5336[0];
                                        const auto g = _temp5336[1];
                                        const auto b = _temp5336[2];
                                        const auto a = _temp5336[3];
                                        ../../../../Schema::Material.createMaterial(builder, r, g, b, a, ../../../../Schema::RenderedFaces.ONE, js::number(0));
                        }
            }
            const js::any materials = builder->endVector();
            js::number sampleCount = js::number(0);
            for (const auto& item : items) {
                        {
                                        sampleCount += item->element.geometries.length();
                        }
            }
            ../../../../Schema::Meshes.startSamplesVector(builder, sampleCount);
            for (js::number g = js::number(0); (g < items.length()); g++) {
                        {
                                        const js::any currentItem = items[((items.length() - js::number(1)) - g)];
                                        const js::any itemID = itemIDMap->get(currentItem->element->id);
                                        const js::any geoms = currentItem->element->geometries;
                                        for (js::number i = js::number(0); (i < geoms.length()); i++) {
                                                            {
                                                                                    const js::any geometry = geoms[((geoms.length() - i) - js::number(1))];
                                                                                    const js::any geometryID = geometryIDMap->get(geometry["id"]);
                                                                                    const js::any materialID = materialIDMap->get(geometry["color"].toString())->id;
                                                                                    const js::any transformID = (geometry["localTransformID"] || js::number(0));
                                                                                    ../../../../Schema::Sample.createSample(builder, itemID, materialID, geometryID, transformID);
                                                            }
                                        }
                        }
            }
            const js::any samplesOffset = builder->endVector();
            ../../../../Schema::Meshes.startLocalTransformsVector(builder, localTransforms.length());
            for (js::number i = js::number(0); (i < localTransforms.length()); i++) {
                        {
                                        const js::any transform = localTransforms->((localTransforms.length() - js::number(1)) - i);
                                        auto _temp2093 = transform["data"];
                                        const auto ox = _temp2093[0];
                                        const auto oy = _temp2093[1];
                                        const auto oz = _temp2093[2];
                                        const auto x1 = _temp2093[3];
                                        const auto x2 = _temp2093[4];
                                        const auto x3 = _temp2093[5];
                                        const auto y1 = _temp2093[6];
                                        const auto y2 = _temp2093[7];
                                        const auto y3 = _temp2093[8];
                                        ../../../../Schema::Transform.createTransform(builder, ox, oy, oz, x1, x2, x3, y1, y2, y3);
                        }
            }
            const js::any localTransformRef = builder->endVector();
            const js::any meshesItemsOffset = ../../../../Schema::Meshes.createMeshesItemsVector(builder, geometriesItems);
            const js::any coordinatesOffset = ../../../../Schema::Transform.createTransform(builder, coordinates["px"], coordinates["py"], coordinates["pz"], coordinates["dxx"], coordinates["dxy"], coordinates["dxz"], coordinates["dyx"], coordinates["dyy"], coordinates["dyz"]);
            ../../../../Schema::Meshes.startMeshes(builder);
            ../../../../Schema::Meshes.addCoordinates(builder, coordinatesOffset);
            ../../../../Schema::Meshes.addGlobalTransforms(builder, globalTransforms);
            ../../../../Schema::Meshes.addShells(builder, shells);
            ../../../../Schema::Meshes.addRepresentations(builder, representationsOffsets);
            ../../../../Schema::Meshes.addSamples(builder, samplesOffset);
            ../../../../Schema::Meshes.addLocalTransforms(builder, localTransformRef);
            ../../../../Schema::Meshes.addMaterials(builder, materials);
            ../../../../Schema::Meshes.addCircleExtrusions(builder, circleExtrusions);
            ../../../../Schema::Meshes.addMeshesItems(builder, meshesItemsOffset);
            const js::any modelMesh = ../../../../Schema::Meshes.endMeshes(builder);
            js::array<js::number> linesOffsets = js::array<js::any>{};
            const std::shared_ptr<Map> absoluteCurvesMap = std::make_shared<Map>();
            const std::shared_ptr<Map> horizontalCurvesMap = std::make_shared<Map>();
            const std::shared_ptr<Map> verticalCurvesMap = std::make_shared<Map>();
            js::number curveCounter = js::number(0);
            for (js::number i = js::number(0); (i < alignments.length()); i++) {
                        {
                                        const js::any index = i;
                                        const js::any alignment = alignments[index];
                                        js::array<js::number> absoluteCurvesIndices = js::array<js::any>{};
                                        absoluteCurvesMap->set(index, absoluteCurvesIndices);
                                        js::array<js::number> horizontalCurvesIndices = js::array<js::any>{};
                                        horizontalCurvesMap->set(index, horizontalCurvesIndices);
                                        js::array<js::number> verticalCurvesIndices = js::array<js::any>{};
                                        verticalCurvesMap->set(index, verticalCurvesIndices);
                                        for (js::number j = js::number(0); (j < alignment["absolute"].length()); j++) {
                                                            {
                                                                                    const js::any curve = alignment["absolute"][((alignment["absolute"].length() - js::number(1)) - j)];
                                                                                    auto _temp1916 = curve;
                                                                                    const auto points = _temp1916["points"];
                                                                                    const js::any pointsOffset = ../../../../Schema::GeometryLines.createPointsVector(builder, points);
                                                                                    ../../../../Schema::GeometryLines.startGeometryLines(builder);
                                                                                    ../../../../Schema::GeometryLines.addPoints(builder, pointsOffset);
                                                                                    const js::any geometryLinesOffset = ../../../../Schema::GeometryLines.endGeometryLines(builder);
                                                                                    linesOffsets.push(geometryLinesOffset);
                                                                                    absoluteCurvesIndices.push(curveCounter++);
                                                            }
                                        }
                                        for (js::number j = js::number(0); (j < alignment["horizontal"].length()); j++) {
                                                            {
                                                                                    const js::any curve = alignment["horizontal"][((alignment["horizontal"].length() - js::number(1)) - j)];
                                                                                    auto _temp9939 = curve;
                                                                                    const auto points = _temp9939["points"];
                                                                                    const js::any pointsOffset = ../../../../Schema::GeometryLines.createPointsVector(builder, points);
                                                                                    ../../../../Schema::GeometryLines.startGeometryLines(builder);
                                                                                    ../../../../Schema::GeometryLines.addPoints(builder, pointsOffset);
                                                                                    const js::any geometryLinesOffset = ../../../../Schema::GeometryLines.endGeometryLines(builder);
                                                                                    linesOffsets.push(geometryLinesOffset);
                                                                                    horizontalCurvesIndices.push(curveCounter++);
                                                            }
                                        }
                                        for (js::number j = js::number(0); (j < alignment["vertical"].length()); j++) {
                                                            {
                                                                                    const js::any curve = alignment["vertical"][((alignment["vertical"].length() - js::number(1)) - j)];
                                                                                    auto _temp5917 = curve;
                                                                                    const auto points = _temp5917["points"];
                                                                                    const js::any pointsOffset = ../../../../Schema::GeometryLines.createPointsVector(builder, points);
                                                                                    ../../../../Schema::GeometryLines.startGeometryLines(builder);
                                                                                    ../../../../Schema::GeometryLines.addPoints(builder, pointsOffset);
                                                                                    const js::any geometryLinesOffset = ../../../../Schema::GeometryLines.endGeometryLines(builder);
                                                                                    linesOffsets.push(geometryLinesOffset);
                                                                                    verticalCurvesIndices.push(curveCounter++);
                                                            }
                                        }
                        }
            }
            const js::any linesVectorOffset = ../../../../Schema::Geometries.createLinesVector(builder, linesOffsets);
            js::any geomReprCounter = curveCounter;
            ../../../../Schema::Geometries.startRepresentationsVector(builder, geomReprCounter);
            js::array<js::number> geomReprIds = js::array<js::any>{};
            geomReprCounter--;
            for (js::number i = js::number(0); (i < alignments.length()); i++) {
                        {
                                        const js::number index = ((alignments.length() - js::number(1)) - i);
                                        const js::any alignment = alignments[index];
                                        for (js::number j = js::number(0); (j < alignment["absolute"].length()); j++) {
                                                            {
                                                                                    const js::any curve = alignment["absolute"][((alignment["absolute"].length() - js::number(1)) - j)];
                                                                                    auto _temp1313 = curve;
                                                                                    const auto type = _temp1313["type"];
                                                                                    geomReprIds->unshift(maxLocalID++);
                                                                                    const js::any id = geomReprCounter--;
                                                                                    ../../../../Schema::GeometryRepresentation.createGeometryRepresentation(builder, id, type);
                                                            }
                                        }
                                        for (js::number j = js::number(0); (j < alignment["horizontal"].length()); j++) {
                                                            {
                                                                                    const js::any curve = alignment["horizontal"][((alignment["horizontal"].length() - js::number(1)) - j)];
                                                                                    auto _temp3396 = curve;
                                                                                    const auto type = _temp3396["type"];
                                                                                    geomReprIds->unshift(maxLocalID++);
                                                                                    const js::any id = geomReprCounter--;
                                                                                    ../../../../Schema::GeometryRepresentation.createGeometryRepresentation(builder, id, type);
                                                            }
                                        }
                                        for (js::number j = js::number(0); (j < alignment["vertical"].length()); j++) {
                                                            {
                                                                                    const js::any curve = alignment["vertical"][((alignment["vertical"].length() - js::number(1)) - j)];
                                                                                    auto _temp5214 = curve;
                                                                                    const auto type = _temp5214["type"];
                                                                                    geomReprIds->unshift(maxLocalID++);
                                                                                    const js::any id = geomReprCounter--;
                                                                                    ../../../../Schema::GeometryRepresentation.createGeometryRepresentation(builder, id, type);
                                                            }
                                        }
                        }
            }
            const js::any geomRepresentationsOffset = builder->endVector();
            js::any samplesCounter = curveCounter;
            js::array<js::number> samplesIds = js::array<js::any>{};
            ../../../../Schema::Geometries.startSamplesVector(builder, samplesCounter);
            samplesCounter--;
            for (js::number i = js::number(0); (i < alignments.length()); i++) {
                        {
                                        const js::number index = ((alignments.length() - js::number(1)) - i);
                                        const js::any alignment = alignments[index];
                                        for (js::number j = js::number(0); (j < alignment["absolute"].length()); j++) {
                                                            {
                                                                                    const js::any id = samplesCounter--;
                                                                                    samplesIds->unshift(maxLocalID++);
                                                                                    ../../../../Schema::GeometrySample.createGeometrySample(builder, id, js::number(0));
                                                            }
                                        }
                                        for (js::number j = js::number(0); (j < alignment["horizontal"].length()); j++) {
                                                            {
                                                                                    const js::any id = samplesCounter--;
                                                                                    samplesIds->unshift(maxLocalID++);
                                                                                    ../../../../Schema::GeometrySample.createGeometrySample(builder, id, js::number(0));
                                                            }
                                        }
                                        for (js::number j = js::number(0); (j < alignment["vertical"].length()); j++) {
                                                            {
                                                                                    const js::any id = samplesCounter--;
                                                                                    samplesIds->unshift(maxLocalID++);
                                                                                    ../../../../Schema::GeometrySample.createGeometrySample(builder, id, js::number(0));
                                                            }
                                        }
                        }
            }
            const js::any geometrySamplesOffset = builder->endVector();
            ../../../../Schema::Geometries.startTransformsVector(builder, js::number(1));
            ../../../../Schema::Transform.createTransform(builder, js::number(0), js::number(0), js::number(0), js::number(1), js::number(0), js::number(0), js::number(0), js::number(1), js::number(0));
            const js::any geometryTransformsOffset = builder->endVector();
            js::array<js::any> geomTransformsIds = js::array<js::any>{maxLocalID++};
            ../../../../Schema::Geometries.startWallsVector(builder, js::number(0));
            const js::any geometryWallsOffset = builder->endVector();
            ../../../../Schema::Geometries.startRepresentationsSamplesVector(builder, js::number(0));
            const js::any geomReprSampVec = builder->endVector();
            const js::any geomReprIdsOffset = ../../../../Schema::Geometries.createRepresentationIdsVector(builder, geomReprIds);
            const js::any geomSampleIdsOffset = ../../../../Schema::Geometries.createSampleIdsVector(builder, samplesIds);
            const js::any geomTransfomsIdsOffset = ../../../../Schema::Geometries.createRepresentationsSamplesVector(builder, geomTransformsIds);
            ../../../../Schema::Geometries.startGeometries(builder);
            ../../../../Schema::Geometries.addSamples(builder, geometrySamplesOffset);
            ../../../../Schema::Geometries.addSampleIds(builder, geomSampleIdsOffset);
            ../../../../Schema::Geometries.addRepresentations(builder, geomRepresentationsOffset);
            ../../../../Schema::Geometries.addRepresentationIds(builder, geomReprIdsOffset);
            ../../../../Schema::Geometries.addTransforms(builder, geometryTransformsOffset);
            ../../../../Schema::Geometries.addTransformIds(builder, geomTransfomsIdsOffset);
            ../../../../Schema::Geometries.addRepresentationsSamples(builder, geomReprSampVec);
            ../../../../Schema::Geometries.addLines(builder, linesVectorOffset);
            ../../../../Schema::Geometries.addWalls(builder, geometryWallsOffset);
            const js::any modelGeometries = ../../../../Schema::Geometries.endGeometries(builder);
            js::array<js::number> alignmentsOffsets = js::array<js::any>{};
            for (js::number i = js::number(0); (i < alignments.length()); i++) {
                        {
                                        const js::any absoluteCurves = absoluteCurvesMap->get(i);
                                        const js::any horizontalCurves = horizontalCurvesMap->get(i);
                                        const js::any verticalCurves = verticalCurvesMap->get(i);
                                        if (((absoluteCurves === js::undefined || horizontalCurves === js::undefined) || verticalCurves === js::undefined)) {
                                                            {
                                                                                    throw js::any(js::Error("Fragments: Malformed alignment definition"_S));
                                                            }
                                        }
                                        const js::any absolutes = ../../../../Schema::Alignment.createAbsoluteVector(builder, absoluteCurves);
                                        const js::any horizontal = ../../../../Schema::Alignment.createHorizontalVector(builder, horizontalCurves);
                                        const js::any vertical = ../../../../Schema::Alignment.createVerticalVector(builder, verticalCurves);
                                        const js::any alignmentOffset = ../../../../Schema::Alignment.createAlignment(builder, absolutes, horizontal, vertical);
                                        alignmentsOffsets.push(alignmentOffset);
                        }
            }
            const js::any modelAlignments = ../../../../Schema::Model.createAlignmentsVector(builder, alignmentsOffsets);
            return []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("modelMesh", modelMesh);
                  obj_temp_2.set("localIDs", localIDs);
                  obj_temp_2.set("maxLocalID", maxLocalID);
                  obj_temp_2.set("modelGeometries", modelGeometries);
                  obj_temp_2.set("modelAlignments", modelAlignments);
                  return js::any(obj_temp_2);
                }();
    }
}
