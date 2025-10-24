#include "index_generated.h"
#include "section-generator.h"

using namespace js;

auto SectionGenerator::createEdges(js::any data) {
    {
            auto _temp4872 = data;
            const auto meshes = _temp4872["meshes"];
            const auto posAttr = _temp4872["posAttr"];
            js::number index = js::number(0);
            posAttr->array->fill(js::number(0));
            js::array<js::number> indexes = js::array<js::any>{};
            js::number lastIndex = js::number(0);
            const std::shared_ptr<three::Mesh> tempMesh = std::make_shared<three::Mesh>();
            for (const auto& mesh : meshes) {
                        {
                                        if (!mesh["geometry"]) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        if (!mesh["geometry"]["boundsTree"]) {
                                                            {
                                                                                    mesh["geometry"]["computeBoundsTree"]();
                                                            }
                                        }
                                        if (!mesh["geometry"]["boundsTree"]) {
                                                            {
                                                                                    throw js::any(js::Error("Fragments: Bounds tree not found for edges generation."_S));
                                                            }
                                        }
                                        if (js::instanceof_op(mesh, "three::InstancedMesh")) {
                                                            {
                                                                                    if (mesh["count"] === js::number(0)) {
                                                                                                                {
                                                                                                                                                continue;
                                                                                                                }
                                                                                    }
                                                                                    const js::any instanced = mesh;
                                                                                    for (js::number i = js::number(0); (i < instanced["count"]); i++) {
                                                                                                                {
                                                                                                                                                tempMesh->geometry = mesh["geometry"];
                                                                                                                                                tempMesh->matrix->copy(mesh["matrix"]);
                                                                                                                                                const std::shared_ptr<three::Matrix4> tempMatrix = std::make_shared<three::Matrix4>();
                                                                                                                                                instanced["getMatrixAt"](i, tempMatrix);
                                                                                                                                                tempMesh->applyMatrix4(tempMatrix);
                                                                                                                                                tempMesh->applyMatrix4(mesh["matrixWorld"]);
                                                                                                                                                tempMesh->updateMatrix();
                                                                                                                                                tempMesh->updateMatrixWorld();
                                                                                                                                                this->_inverseMatrix.copy(tempMesh->matrixWorld).invert();
                                                                                                                                                this->_localPlane.copy(this->plane).applyMatrix4(this->_inverseMatrix);
                                                                                                                                                index = this->shapecast(tempMesh, posAttr, index);
                                                                                                                                                if (index !== lastIndex) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            indexes.push(index);
                                                                                                                                                                                                                            lastIndex = index;
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        } else {
                                                            {
                                                                                    this->_inverseMatrix.copy(mesh["matrixWorld"]).invert();
                                                                                    this->_localPlane.copy(this->plane).applyMatrix4(this->_inverseMatrix);
                                                                                    index = this->shapecast(mesh, posAttr, index);
                                                                                    if (index !== lastIndex) {
                                                                                                                {
                                                                                                                                                indexes.push(index);
                                                                                                                                                lastIndex = index;
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("indexes", indexes);
                  obj_temp_0.set("index", index);
                  return js::any(obj_temp_0);
                }();
    }
}

auto SectionGenerator::createFills(js::Float32Array buffer, js::array<js::number> trianglesIndices) {
    {
            this->updatePlane2DCoordinateSystem();
            js::array<js::number> allIndices = js::array<js::any>{};
            js::number currentTriangle = js::number(0);
            for (js::number i = js::number(0); (i < trianglesIndices.length()); i++) {
                        {
                                        const js::any nextTriangle = trianglesIndices->i;
                                        js::array<js::number> vertices = js::array<js::any>{};
                                        for (js::any j = currentTriangle; (j < nextTriangle); j += js::number(2)) {
                                                            {
                                                                                    vertices.push((j * js::number(3)));
                                                            }
                                        }
                                        const js::any indices = this->computeFill(vertices, buffer);
                                        js::number indexCounter = js::number(0);
                                        for (const auto& index : indices) {
                                                            {
                                                                                    allIndices.push(index);
                                                                                    indexCounter++;
                                                            }
                                        }
                                        currentTriangle = nextTriangle;
                        }
            }
            return allIndices;
    }
}

auto SectionGenerator::computeFill(js::array<js::number> vertices, js::Float32Array buffer) {
    {
            const std::shared_ptr<Map> indices = std::make_shared<Map>();
            const js::any all2DVertices = []() {
                  js::object obj_temp_1;
                  return js::any(obj_temp_1);
                }();
            const std::shared_ptr<Map> shapes = std::make_shared<Map>();
            js::number nextShapeID = js::number(0);
            const std::shared_ptr<Map> shapesEnds = std::make_shared<Map>();
            const std::shared_ptr<Map> shapesStarts = std::make_shared<Map>();
            const std::shared_ptr<Set> openShapes = std::make_shared<Set>();
            const js::any p = this->_precission;
            for (js::number i = js::number(0); (i < vertices.length()); i++) {
                        {
                                        const js::any startVertexIndex = vertices[i];
                                        js::number x1 = js::number(0);
                                        js::number y1 = js::number(0);
                                        js::number x2 = js::number(0);
                                        js::number y2 = js::number(0);
                                        const js::any globalX1 = buffer[startVertexIndex];
                                        const js::any globalY1 = buffer[(startVertexIndex + js::number(1))];
                                        const js::any globalZ1 = buffer[(startVertexIndex + js::number(2))];
                                        const js::any globalX2 = buffer[(startVertexIndex + js::number(3))];
                                        const js::any globalY2 = buffer[(startVertexIndex + js::number(4))];
                                        const js::any globalZ2 = buffer[(startVertexIndex + js::number(5))];
                                        this->_tempVector.set(globalX1, globalY1, globalZ1);
                                        this->_tempVector.applyMatrix4(this->_plane2DCoordinateSystem);
                                        x1 = (js::Math::trunc((this->_tempVector.x * p)) / p);
                                        y1 = (js::Math::trunc((this->_tempVector.y * p)) / p);
                                        this->_tempVector.set(globalX2, globalY2, globalZ2);
                                        this->_tempVector.applyMatrix4(this->_plane2DCoordinateSystem);
                                        x2 = (js::Math::trunc((this->_tempVector.x * p)) / p);
                                        y2 = (js::Math::trunc((this->_tempVector.y * p)) / p);
                                        if ((x1 === x2 && y1 === y2)) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        const js::any startCode = (js::toString(x1) + "|"_S + js::toString(y1));
                                        const js::any endCode = (js::toString(x2) + "|"_S + js::toString(y2));
                                        if (!indices["has"](startCode)) {
                                                            {
                                                                                    indices["set"](startCode, (startVertexIndex / js::number(3)));
                                                            }
                                        }
                                        if (!indices["has"](endCode)) {
                                                            {
                                                                                    indices["set"](endCode, ((startVertexIndex / js::number(3)) + js::number(1)));
                                                            }
                                        }
                                        const js::any start = indices["get"](startCode);
                                        const js::any end = indices["get"](endCode);
                                        all2DVertices->start = js::array<js::any>{x1, y1};
                                        all2DVertices->end = js::array<js::any>{x2, y2};
                                        const js::any startMatchesStart = shapesStarts->has(start);
                                        const js::any startMatchesEnd = shapesEnds->has(start);
                                        const js::any endMatchesStart = shapesStarts->has(end);
                                        const js::any endMatchesEnd = shapesEnds->has(end);
                                        const js::any noMatches = (((!startMatchesStart && !startMatchesEnd) && !endMatchesStart) && !endMatchesEnd);
                                        if (noMatches) {
                                                            {
                                                                                    shapesStarts->set(start, nextShapeID);
                                                                                    shapesEnds->set(end, nextShapeID);
                                                                                    openShapes->add(nextShapeID);
                                                                                    shapes["set"](nextShapeID, js::array<js::any>{start, end});
                                                                                    nextShapeID++;
                                                            }
                                        } else {
                                                            if ((startMatchesStart && endMatchesEnd)) {
                                                                                    {
                                                                                                                const js::any startIndex = shapesStarts->get(start);
                                                                                                                const js::any endIndex = shapesEnds->get(end);
                                                                                                                const js::any isShapeMerge = startIndex !== endIndex;
                                                                                                                if (isShapeMerge) {
                                                                                                                                                {
                                                                                                                                                                                    const js::any endShape = shapes["get"](endIndex);
                                                                                                                                                                                    const js::any startShape = shapes["get"](startIndex);
                                                                                                                                                                                    if ((!endShape || !startShape)) {
                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                        continue;
                                                                                                                                                                                                                            }
                                                                                                                                                                                    }
                                                                                                                                                                                    shapes["delete"](startIndex);
                                                                                                                                                                                    openShapes->delete(startIndex);
                                                                                                                                                                                    shapesEnds->set(startShape->(startShape.length() - js::number(1)), endIndex);
                                                                                                                                                                                    shapesEnds->delete(endShape->(endShape.length() - js::number(1)));
                                                                                                                                                                                    for (const auto& index : startShape) {
                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                        endShape.push(index);
                                                                                                                                                                                                                            }
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                } else {
                                                                                                                                                {
                                                                                                                                                                                    openShapes->delete(endIndex);
                                                                                                                                                }
                                                                                                                }
                                                                                                                shapesStarts->delete(start);
                                                                                                                shapesEnds->delete(end);
                                                                                    }
                                                            } else {
                                                                                    if ((startMatchesEnd && endMatchesStart)) {
                                                                                                                {
                                                                                                                                                const js::any startIndex = shapesStarts->get(end);
                                                                                                                                                const js::any endIndex = shapesEnds->get(start);
                                                                                                                                                const js::any isShapeMerge = startIndex !== endIndex;
                                                                                                                                                if (isShapeMerge) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            const js::any endShape = shapes["get"](endIndex);
                                                                                                                                                                                                                            const js::any startShape = shapes["get"](startIndex);
                                                                                                                                                                                                                            if ((!endShape || !startShape)) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        continue;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            shapes["delete"](startIndex);
                                                                                                                                                                                                                            openShapes->delete(startIndex);
                                                                                                                                                                                                                            shapesEnds->set(startShape->(startShape.length() - js::number(1)), endIndex);
                                                                                                                                                                                                                            shapesEnds->delete(endShape->(endShape.length() - js::number(1)));
                                                                                                                                                                                                                            for (const auto& index : startShape) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        endShape.push(index);
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                    }
                                                                                                                                                } else {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            openShapes->delete(endIndex);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                shapesStarts->delete(end);
                                                                                                                                                shapesEnds->delete(start);
                                                                                                                }
                                                                                    } else {
                                                                                                                if ((startMatchesStart && endMatchesStart)) {
                                                                                                                                                {
                                                                                                                                                                                    const js::any startIndex1 = shapesStarts->get(end);
                                                                                                                                                                                    const js::any startIndex2 = shapesStarts->get(start);
                                                                                                                                                                                    const js::any startShape2 = shapes["get"](startIndex2);
                                                                                                                                                                                    const js::any startShape1 = shapes["get"](startIndex1);
                                                                                                                                                                                    if ((!startShape2 || !startShape1)) {
                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                        continue;
                                                                                                                                                                                                                            }
                                                                                                                                                                                    }
                                                                                                                                                                                    shapes["delete"](startIndex1);
                                                                                                                                                                                    openShapes->delete(startIndex1);
                                                                                                                                                                                    shapesStarts->delete(startShape2->js::number(0));
                                                                                                                                                                                    shapesStarts->delete(startShape1->js::number(0));
                                                                                                                                                                                    shapesEnds->delete(startShape1->(startShape1.length() - js::number(1)));
                                                                                                                                                                                    shapesStarts->set(startShape1->(startShape1.length() - js::number(1)), startIndex2);
                                                                                                                                                                                    startShape1->reverse();
                                                                                                                                                                                    startShape2->splice(js::number(0), js::number(0), /* spread startShape1 */);
                                                                                                                                                }
                                                                                                                } else {
                                                                                                                                                if ((startMatchesEnd && endMatchesEnd)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            const js::any endIndex1 = shapesEnds->get(end);
                                                                                                                                                                                                                            const js::any endIndex2 = shapesEnds->get(start);
                                                                                                                                                                                                                            const js::any endShape2 = shapes["get"](endIndex2);
                                                                                                                                                                                                                            const js::any endShape1 = shapes["get"](endIndex1);
                                                                                                                                                                                                                            if ((!endShape2 || !endShape1)) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        continue;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            shapes["delete"](endIndex1);
                                                                                                                                                                                                                            openShapes->delete(endIndex1);
                                                                                                                                                                                                                            shapesEnds->delete(endShape2->(endShape2.length() - js::number(1)));
                                                                                                                                                                                                                            shapesEnds->delete(endShape1->(endShape1.length() - js::number(1)));
                                                                                                                                                                                                                            shapesStarts->delete(endShape1->js::number(0));
                                                                                                                                                                                                                            shapesEnds->set(endShape1->js::number(0), endIndex2);
                                                                                                                                                                                                                            endShape1->reverse();
                                                                                                                                                                                                                            endShape2.push(/* spread endShape1 */);
                                                                                                                                                                                    }
                                                                                                                                                } else {
                                                                                                                                                                                    if (startMatchesStart) {
                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                        const js::any shapeIndex = shapesStarts->get(start);
                                                                                                                                                                                                                                                                        const js::any shape = shapes["get"](shapeIndex);
                                                                                                                                                                                                                                                                        if (!shape) {
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                                                                            continue;
                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        shape->unshift(end);
                                                                                                                                                                                                                                                                        shapesStarts->delete(start);
                                                                                                                                                                                                                                                                        shapesStarts->set(end, shapeIndex);
                                                                                                                                                                                                                            }
                                                                                                                                                                                    } else {
                                                                                                                                                                                                                            if (startMatchesEnd) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        const js::any shapeIndex = shapesEnds->get(start);
                                                                                                                                                                                                                                                                                                                        const js::any shape = shapes["get"](shapeIndex);
                                                                                                                                                                                                                                                                                                                        if (!shape) {
                                                                                                                                                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                                                                                                                                                                                    continue;
                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                                                        shape.push(end);
                                                                                                                                                                                                                                                                                                                        shapesEnds->delete(start);
                                                                                                                                                                                                                                                                                                                        shapesEnds->set(end, shapeIndex);
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                        if (endMatchesStart) {
                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                                                                            const js::any shapeIndex = shapesStarts->get(end);
                                                                                                                                                                                                                                                                                                                                                                            const js::any shape = shapes["get"](shapeIndex);
                                                                                                                                                                                                                                                                                                                                                                            if (!shape) {
                                                                                                                                                                                                                                                                                                                                                                                                                                    {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                continue;
                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                                            shape->unshift(start);
                                                                                                                                                                                                                                                                                                                                                                            shapesStarts->delete(end);
                                                                                                                                                                                                                                                                                                                                                                            shapesStarts->set(start, shapeIndex);
                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                                                                        if (endMatchesEnd) {
                                                                                                                                                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                                                                                                                                                                                    const js::any shapeIndex = shapesEnds->get(end);
                                                                                                                                                                                                                                                                                                                                                                                                                                    const js::any shape = shapes["get"](shapeIndex);
                                                                                                                                                                                                                                                                                                                                                                                                                                    if (!shape) {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                continue;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                                                                                    shape.push(start);
                                                                                                                                                                                                                                                                                                                                                                                                                                    shapesEnds->delete(end);
                                                                                                                                                                                                                                                                                                                                                                                                                                    shapesEnds->set(start, shapeIndex);
                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            js::array<js::number> trueIndices = js::array<js::any>{};
            for (const auto& js::undefined : shapes) {
                        {
                                        if (openShapes->has(id)) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        js::array<js::number> vertices = js::array<js::any>{};
                                        const std::shared_ptr<Map> indexMap = std::make_shared<Map>();
                                        js::number counter = js::number(0);
                                        for (const auto& index : shape) {
                                                            {
                                                                                    const js::any vertex = all2DVertices->index;
                                                                                    vertices.push(vertex[js::number(0)], vertex[js::number(1)]);
                                                                                    indexMap->set(counter++, index);
                                                            }
                                        }
                                        const js::any result = earcut(vertices);
                                        for (const auto& index : result) {
                                                            {
                                                                                    const js::any trueIndex = indexMap->get(index);
                                                                                    if (trueIndex === js::undefined) {
                                                                                                                {
                                                                                                                                                throw js::any(js::Error("Fragments: Map error!"_S));
                                                                                                                }
                                                                                    }
                                                                                    trueIndices.push(trueIndex);
                                                            }
                                        }
                        }
            }
            return trueIndices;
    }
}

auto SectionGenerator::updatePlane2DCoordinateSystem() {
    {
            this->_plane2DCoordinateSystem = std::make_shared<three::Matrix4>();
            const js::any zAxis = this->plane.normal;
            const std::shared_ptr<three::Vector3> pos = std::make_shared<three::Vector3>();
            this->plane.coplanarPoint(pos);
            js::any xAxis;
            js::any yAxis;
            if ((js::Math::abs(zAxis->z) > js::number(0.99))) {
                        {
                                        xAxis = std::make_shared<three::Vector3>(js::number(1), js::number(0), js::number(0));
                                        yAxis = std::make_shared<three::Vector3>(js::number(0), js::number(1), js::number(0));
                        }
            } else {
                        if ((js::Math::abs(zAxis->x) > js::number(0.99))) {
                                        {
                                                            xAxis = std::make_shared<three::Vector3>(js::number(0), js::number(1), js::number(0));
                                                            yAxis = std::make_shared<three::Vector3>(js::number(0), js::number(0), js::number(1));
                                        }
                        } else {
                                        if ((js::Math::abs(zAxis->y) > js::number(0.99))) {
                                                            {
                                                                                    xAxis = std::make_shared<three::Vector3>(js::number(1), js::number(0), js::number(0));
                                                                                    yAxis = std::make_shared<three::Vector3>(js::number(0), js::number(0), js::number(1));
                                                            }
                                        } else {
                                                            {
                                                                                    const js::any tempVector = (js::null ? js::null : js::null);
                                                                                    xAxis = std::make_shared<three::Vector3>();
                                                                                    xAxis->crossVectors(tempVector, zAxis)->normalize();
                                                                                    yAxis = std::make_shared<three::Vector3>();
                                                                                    yAxis->crossVectors(zAxis, xAxis)->normalize();
                                                            }
                                        }
                        }
            }
            this->_plane2DCoordinateSystem.fromArray(js::array<js::number>{xAxis->x, xAxis->y, xAxis->z, js::number(0), yAxis->x, yAxis->y, yAxis->z, js::number(0), zAxis->x, zAxis->y, zAxis->z, js::number(0), pos["x"], pos["y"], pos["z"], js::number(1)});
            this->_plane2DCoordinateSystem.invert();
    }
}

auto SectionGenerator::shapecast(js::any mesh, js::any posAttr, js::number index) {
    {
            mesh["geometry"]["boundsTree"]["shapecast"]([]() {
                  js::object obj_temp_2;
                  obj_temp_2.set("intersectsBounds", [&](js::any box) -> auto { return this->_localPlane.intersectsBox(box); });
                  obj_temp_2.set("intersectsTriangle", [&](js::any tri) -> auto {
            js::number count = js::number(0);
            this->_tempLine.start.copy(tri["a"]);
            this->_tempLine.end.copy(tri["b"]);
            if (this->_localPlane.intersectLine(this->_tempLine, this->_tempVector)) {
                        {
                                        const js::any result = this->_tempVector.applyMatrix4(mesh["matrixWorld"]);
                                        posAttr->setXYZ(index, result->x, result->y, result->z);
                                        count++;
                                        index++;
                        }
            }
            this->_tempLine.start.copy(tri["b"]);
            this->_tempLine.end.copy(tri["c"]);
            if (this->_localPlane.intersectLine(this->_tempLine, this->_tempVector)) {
                        {
                                        const js::any result = this->_tempVector.applyMatrix4(mesh["matrixWorld"]);
                                        posAttr->setXYZ(index, result->x, result->y, result->z);
                                        count++;
                                        index++;
                        }
            }
            this->_tempLine.start.copy(tri["c"]);
            this->_tempLine.end.copy(tri["a"]);
            if (this->_localPlane.intersectLine(this->_tempLine, this->_tempVector)) {
                        {
                                        const js::any result = this->_tempVector.applyMatrix4(mesh["matrixWorld"]);
                                        posAttr->setXYZ(index, result->x, result->y, result->z);
                                        count++;
                                        index++;
                        }
            }
            if (count !== js::number(2)) {
                        {
                                        index -= count;
                        }
            }
            });
                  return js::any(obj_temp_2);
                }());
            return index;
    }
}
